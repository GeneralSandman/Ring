package main

import (
	"bufio"
	"fmt"
	"os"
	"os/exec"
	"path/filepath"
	"regexp"
	"strings"
	"sync"
	"time"

	"github.com/gosuri/uiprogress"
	"github.com/sergi/go-diff/diffmatchpatch"
)

//  Action:
//  对 ./test 所有的测试用例进行自动化测试,
//  执行 ring run xxx.ring 命令 运行, 得到输出结果 xxx.ring.result.tmp,
//  与预期结果 xxx.ring.result 进行比对
//  会输出 测试的详情和测试数量汇总

//  Usage:
//  1. 触发全部自动化测试
//     make testall
//     或者 bash ./test/automated-testing.sh
//  2. 测试的轮数
//     默认1轮, 可调整 TEST_LOOP_NUM
//  3. 控制测试的模块:
//     调整 TEST_MODELS
//  4. 控制不测试的case:
//     调整 NOT_TEST_FILES
//  5. 是否输出测试用例表:
//     调整 IS_EXPORT_TEST_DETAIL_SUMMARY
//     测试描述会从测试文件中导出, 匹配前缀 // TestDetail:
//     测试用例中导出测试失败的原因，匹配前缀 // Fatal:

var (
	TEST_MODELS = []string{
		"001-bool",
		"002-int",
		"002-int64",
		"003-double",
		"004-string",

		"001-basic-type",

		"002-operator",
		"002-operator/minus",
		"002-operator/string",

		"003-native-function",
		"004-derive-function",
		"004-derive-function/function-call",
		"004-derive-function/pass-argument",
		"004-derive-function/return-value",

		"006-variable",
		"007-array",
		"008-class",
		"010-main-entry",
		"011-global-variable",
		"012-local-variable",
		"013-gc",

		"020-array-bool",
		"021-array-int",
		"021-array-int64",
		"022-array-double",
		"023-array-string",
		"024-array-class",
		"025-array-closure",

		"030-if",
		"031-for",
		"032-do-for",
		"033-for-range",

		"040-closure",
		"041-defer",

		"050-coroutine",

		"060-std-package-debug",
		"061-std-package-fmt",
		"062-std-package-reflect",
		"063-std-package-os",
		"064-std-package-runtime",
		"065-std-package-io",
		"066-std-package-time",
		"067-std-package-math",
		"068-std-package-strings",
	}

	NOT_TEST_FILES = []string{
		"test/013-gc/gc-000.ring",

		"test/002-operator/arith-oper-002.ring",
		// double 数值比对, 存在bug

		"test/002-operator/arith-oper-003.ring",
		// 还没有支持括号运算符

		"test/060-std-package-debug/debug-000.ring",
		// 只用来测试 ring rdb

		"test/002-int64/default-value-003.ring",
		// 暂时还没啥用

		"test/065-std-package-io/000.ring",

		// "./test/062-std-package-reflect/reflect-001.ring"
		// 1. class-object数组，typeof获取不到正确的类型
		// 2. 针对多维数组，typeof获取不到正确的类型
		// 2023-01-31

		"test/050-coroutine/sleep-and-yield.ring",
		// 就是未来死循环验证协程切换, 可以暂时不用测试

		// 等 v0.3.0 重新设计垃圾回收算法之后，重新验证
		"test/064-std-package-runtime/gc-array.ring",
		"test/064-std-package-runtime/gc-array-string.ring",
		"test/064-std-package-runtime/gc-class-002.ring",

		// 临时测试文件
		"test/013-gc/gc-test-000.ring",
		"test/013-gc/gc-array-001.ring",
		"test/013-gc/test-array-copy.ring",
	}

	TEST_CASE_WORKFLOW_PATH = "/Users/bytedance/Desktop/Ring"

	// 测试的轮数, 用于多次执行
	TEST_LOOP_NUM                = 1
	notTestNum, succNum, failNum int
	// 测试的Ring可执行二进制文件
	TEST_RING_BIN = "./bin/ring"
	// ring 命令行 option
	TEST_RING_OPTION = "-O1"
	// 测试功能 ring run xxx.ring
	TEST_RING_COMMAND             = "run"
	IS_EXPORT_TEST_DETAIL_SUMMARY = 0
	TEST_DETAIL_SUMMARY           = "./test/ring-测试用例表.md.raw"
	TEST_PATH                     = "./test"
)

func main() {
	var wg sync.WaitGroup

	const maxConcurrent = 50                                   // 最大并发数
	maxConcurrentChannel := make(chan struct{}, maxConcurrent) // 创建信号量通道

	var testCaseResultMap sync.Map

	displayMode := false
	// flase 只有进度条
	// true 展示详细进度

	allTestCases := getAllTestCases()

	allNum := len(allTestCases) * TEST_LOOP_NUM

	progressBar := uiprogress.
		AddBar(allNum).
		AppendCompleted().
		PrependElapsed()
	progressBar.PrependFunc(func(b *uiprogress.Bar) string {
		return fmt.Sprintf("[Progress] (%d/%d)", b.Current(), allNum)
	})
	uiprogress.Start()

	startTime := time.Now()
	if displayMode {
		fmt.Printf("%-25s %-80s %-80s %s\n", "Model", "SourceCodeFile", "ResultFile", "Result")
	}

	for loop := 0; loop < TEST_LOOP_NUM; loop++ {
		for _, testCase := range allTestCases {
			go func(testCase RingTestCase) {
				defer func() {
					wg.Done()
					<-maxConcurrentChannel
					progressBar.Incr()
				}()

				wg.Add(1)
				maxConcurrentChannel <- struct{}{}

				testResult := autoTestAction(testCase, displayMode)
				testCaseResultMap.Store(testCase.FileName, testResult)
			}(testCase)
		}
	}

	wg.Wait()
	uiprogress.Stop()

	var failedResults []*RingTestResult
	testCaseResultMap.Range(func(key, value interface{}) bool {
		testResult := value.(*RingTestResult)
		if testResult.Status == Status_Failed {
			failNum++
			failedResults = append(failedResults, testResult)
		} else if testResult.Status == Status_Pass {
			succNum++
		}
		return true
	})

	fmt.Printf("\n")
	fmt.Printf("[TestInfo]:\n")
	fmt.Printf("TEST_LOOP_NUM     = %d\n", TEST_LOOP_NUM)
	fmt.Printf("TEST_RING_BIN     = %s\n", TEST_RING_BIN)
	fmt.Printf("TEST_RING_OPTION  = %s\n", TEST_RING_OPTION)
	fmt.Printf("TEST_RING_COMMAND = %s\n", TEST_RING_COMMAND)
	fmt.Printf("TEST_PATH         = %s\n", TEST_PATH)

	resultColor := "\033[32m"
	if failNum != 0 {
		resultColor = "\033[33m"
	}
	fmt.Printf("%s", resultColor)
	fmt.Printf("\n")
	fmt.Printf("[Result]:\n")
	fmt.Printf("Pass/All = %d/%d\n", succNum, allNum)
	fmt.Printf("NotTest  = %d\n", notTestNum)
	fmt.Printf("Fail     = %d\n", failNum)
	fmt.Printf("Usetime  = %dS\n", int(time.Since(startTime).Seconds()))
	fmt.Printf("%s", "\033[0m")

	if failNum != 0 {
		fmt.Printf("[Failed TestCase]\n")
		for _, testResult := range failedResults {
			fmt.Printf("******** FileName: %s********\n", testResult.RingTestCase.FileName)
			fmt.Printf("Output: %s\n", testResult.Detail)
			fmt.Printf("\n")
		}
	}
}

func autoTestAction(testCase RingTestCase, printDetail bool) *RingTestResult {
	model := testCase.Model
	sourceCodeFile := "./" + testCase.FileName
	expectResultFile := "./" + sourceCodeFile + ".result"
	runResultFileTmp := "./" + sourceCodeFile + ".result.tmp"
	diffTool := diffmatchpatch.New()

	expectOutput, err := os.ReadFile(expectResultFile)
	if err != nil {
		return &RingTestResult{
			RingTestCase: testCase,
			Status:       Status_Failed,
			Detail:       fmt.Sprintf("read expect result Error:%s", err.Error()),
		}
	}

	cmd := exec.Command(TEST_RING_BIN, TEST_RING_OPTION, TEST_RING_COMMAND, sourceCodeFile)
	output, err := cmd.CombinedOutput()
	if err != nil {
		return &RingTestResult{
			RingTestCase: testCase,
			Status:       Status_Failed,
			Detail:       fmt.Sprintf("run test case Error:%s Output:%s", err.Error(), string(output)),
		}
	}

	diffs := diffTool.DiffMain(string(expectOutput), string(output), false)
	diffResult := diffTool.DiffPrettyText(diffs)

	if string(diffResult) == string(expectOutput) {
		if printDetail {
			fmt.Printf("%-25s %-80s %-80s [%s]\n", model, sourceCodeFile, runResultFileTmp, Status_Pass)
		}
		return &RingTestResult{
			RingTestCase: testCase,
			Status:       Status_Pass,
			Detail:       "",
		}
	} else {
		if printDetail {
			fmt.Printf("%-25s %-80s %-80s [%s]\n", model, sourceCodeFile, runResultFileTmp, Status_Failed)
		}
		detail := fmt.Sprintf("<<<<<<<<<<<<<<<<<<<<\n%s<<<<<<<<<<<<<<<<<<<<\n>>>>>>>>>>>>>>>>>>>>\n%s>>>>>>>>>>>>>>>>>>>>\n====================\n%s====================\n", string(expectOutput), string(output), diffResult)

		return &RingTestResult{
			RingTestCase: testCase,
			Status:       Status_Failed,
			Detail:       fmt.Sprintf("diff expect and result Diff:\n%s", detail),
		}
	}

}

func getAllTestCases() []RingTestCase {
	var result []RingTestCase

	for _, model := range TEST_MODELS {

		sourceFilePath := filepath.Join(TEST_PATH, model)
		files, _ := os.ReadDir(sourceFilePath)

		for _, file := range files {

			if filepath.Ext(file.Name()) == ".ring" {

				filePath := filepath.Join(TEST_PATH, model, file.Name())
				if !isNotTestFile(filePath) {
					result = append(result,
						RingTestCase{
							Model:    model,
							FileName: filePath,
						})
				}
			}
		}
	}

	return result
}

func isNotTestFile(filePath string) bool {
	for _, notTestFile := range NOT_TEST_FILES {
		if filePath == notTestFile {
			return true
		}
	}
	return false
}

func exportTestCase(num int, model, sourceCodeFile, result string) {
	if num == 1 {
		os.WriteFile(TEST_DETAIL_SUMMARY, []byte("# Ring 测试用例表\n\n"), 0644)
		f, _ := os.OpenFile(TEST_DETAIL_SUMMARY, os.O_APPEND|os.O_WRONLY, 0644)
		fmt.Fprintf(f, "- 测试时间: %s\n\n", time.Now().Format("2006-01-02 15:04:05"))
		fmt.Fprintln(f, "|Num | 模块 | 文件                           | 测试内容 | 通过 |")
		fmt.Fprintln(f, "|--- | -----| ------------------------------| -------- | -- |")
		f.Close()
	}

	content, _ := os.ReadFile(sourceCodeFile)
	details := extractDetails(string(content))
	f, _ := os.OpenFile(TEST_DETAIL_SUMMARY, os.O_APPEND|os.O_WRONLY, 0644)
	fmt.Fprintf(f, "| %-4d | *%-20s | %-80s | %-80s | %-10s |\n", num, model, sourceCodeFile, details, result)
	f.Close()
}

func extractDetails(source string) string {
	re := regexp.MustCompile(`^// TestDetail: (.*)$`)
	var details []string
	scanner := bufio.NewScanner(strings.NewReader(source))
	for scanner.Scan() {
		match := re.FindStringSubmatch(scanner.Text())
		if match != nil {
			details = append(details, match[1])
		}
	}
	return strings.Join(details, "<br>")
}

type RingTestCase struct {
	Model    string
	FileName string
}

type RingTestResult struct {
	RingTestCase RingTestCase
	Status       RingTestResult_Status
	Detail       string
}

type RingTestResult_Status string

const (
	Status_Pass   RingTestResult_Status = "PASS"
	Status_Failed RingTestResult_Status = "FAILED"
)
