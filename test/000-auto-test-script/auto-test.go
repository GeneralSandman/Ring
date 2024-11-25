package main

import (
	"bufio"
	"fmt"
	"io/ioutil"
	"os"
	"os/exec"
	"path/filepath"
	"regexp"
	"strings"
	"sync"
	"time"

	"github.com/schollz/progressbar/v3"
)

var (
	TEST_LOOP_NUM                        = 2
	notTestNum, succNum, failNum, allNum int
	TEST_RING_BIN                        = "./bin/ring"
	TEST_RING_OPTION                     = "-O1"
	TEST_RING_COMMAND                    = "run"
	TEST_RESULT                          = "./automated-testing.sh.result"
	IS_EXPORT_TEST_DETAIL_SUMMARY        = 0
	TEST_DETAIL_SUMMARY                  = "./test/ring-测试用例表.md.raw"
	TEST_PATH                            = "./test"

	NOT_TEST_FILES = []string{
		"test/013-gc/gc-000.ring",
		"test/002-operator/arith-oper-002.ring",
		"test/002-operator/arith-oper-003.ring",
		"test/060-std-package-debug/debug-000.ring",
		"test/002-int64/default-value-003.ring",
		"test/065-std-package-io/000.ring",
	}

	TEST_MODELS = []string{
		"001-bool", "002-int", "002-int64", "003-double", "004-string",
		"001-basic-type", "002-operator", "002-operator/minus", "003-native-function",
		"004-derive-function", "004-derive-function/pass-argument", "004-derive-function/return-value",
		"006-variable", "007-array", "008-class", "010-main-entry", "011-global-variable",
		"012-local-variable", "013-gc", "020-array-bool", "021-array-int",
		"021-array-int64", "022-array-double", "023-array-string", "024-array-class",
		"030-if", "031-for", "032-do-for", "033-for-range", "040-closure", "041-defer",
		"050-coroutine", "060-std-package-debug", "061-std-package-fmt", "062-std-package-reflect",
		"063-std-package-os", "064-std-package-vm", "065-std-package-io", "066-std-package-time",
		"067-std-package-math",
	}
)

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
		ioutil.WriteFile(TEST_DETAIL_SUMMARY, []byte("# Ring 测试用例表\n\n"), 0644)
		f, _ := os.OpenFile(TEST_DETAIL_SUMMARY, os.O_APPEND|os.O_WRONLY, 0644)
		fmt.Fprintf(f, "- 测试时间: %s\n\n", time.Now().Format("2006-01-02 15:04:05"))
		fmt.Fprintln(f, "|Num | 模块 | 文件                           | 测试内容 | 通过 |")
		fmt.Fprintln(f, "|--- | -----| ------------------------------| -------- | -- |")
		f.Close()
	}

	content, _ := ioutil.ReadFile(sourceCodeFile)
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

func autoTestAction(model, sourceCodeFile string) {
	runResultFile := sourceCodeFile + ".result"
	runResultFileTmp := sourceCodeFile + ".result.tmp"

	if isNotTestFile(sourceCodeFile) {
		notTestNum++
		// fmt.Printf("%-4d %-25s %-80s %-80s [%s]\n", allNum, model, sourceCodeFile, runResultFile, "NOTTEST")
		return
	}

	allNum++

	cmd := exec.Command(TEST_RING_BIN, TEST_RING_OPTION, TEST_RING_COMMAND, sourceCodeFile)
	output, err := cmd.CombinedOutput()
	if err != nil {
		failNum++
		// fmt.Println(string(output))
		// fmt.Printf("%-4d %-25s %-80s %-80s [%s]\n", allNum, model, sourceCodeFile, runResultFile, "FAILED")
		appendToFile(TEST_RESULT, sourceCodeFile)
		return
	}

	err = ioutil.WriteFile(runResultFileTmp, output, 0644)
	if err != nil {
		return
	}

	originalOutput, _ := ioutil.ReadFile(runResultFile)
	if string(originalOutput) == string(output) {
		succNum++
		// fmt.Printf("%-4d %-25s %-80s %-80s [%s]\n", allNum, model, sourceCodeFile, runResultFile, "PASS")
	} else {
		failNum++
		// fmt.Printf("%-4d %-25s %-80s %-80s [%s]\n", allNum, model, sourceCodeFile, runResultFile, "FAILED")
		appendToFile(TEST_RESULT, sourceCodeFile)
	}

	os.Remove(runResultFileTmp)

	if IS_EXPORT_TEST_DETAIL_SUMMARY == 1 {
		exportTestCase(allNum, model, sourceCodeFile, "RESULT")
	}
}

func appendToFile(filename, content string) {
	f, _ := os.OpenFile(filename, os.O_APPEND|os.O_WRONLY|os.O_CREATE, 0644)
	defer f.Close()
	f.WriteString(content + "\n")
}

func printNotPassCase() {
	if _, err := os.Stat(TEST_RESULT); os.IsNotExist(err) {
		return
	}
	fmt.Println("[NotPassCase]")
	data, _ := ioutil.ReadFile(TEST_RESULT)
	counts := make(map[string]int)
	for _, line := range strings.Split(string(data), "\n") {
		counts[line]++
	}
	for k, v := range counts {
		fmt.Printf("%-60s %-60d\n", k, v)
	}
	os.Remove(TEST_RESULT)
}

func main() {
	var wg sync.WaitGroup
	bar := progressbar.Default(1000)

	const maxConcurrent = 10 // 最大并发数
    sem := make(chan struct{}, maxConcurrent) // 创建信号量通道

	startTime := time.Now()
	// fmt.Printf("%-4s %-25s %-80s %-80s %s\n", "Num", "Model", "SourceCodeFile", "ResultFile", "Result")

	for testLoop := 1; testLoop <= TEST_LOOP_NUM; testLoop++ {
		for _, model := range TEST_MODELS {
			sourceFilePath := filepath.Join(TEST_PATH, model)
			files, _ := ioutil.ReadDir(sourceFilePath)
			for _, file := range files {
				if filepath.Ext(file.Name()) == ".ring" {
					// fmt.Println(file.Name())
					// allNum++
					go func(model_, file_ string) {
						defer wg.Done()
						defer bar.Add(1)
						defer func() { <-sem }()

						wg.Add(1)
						sem <- struct{}{}
						autoTestAction(model_, file_)
					}(model, filepath.Join(sourceFilePath, file.Name()))
				}
			}
		}
	}

	wg.Wait()

	fmt.Println("\n[TestInfo]:")
	fmt.Printf("TEST_LOOP_NUM     = %d\n", TEST_LOOP_NUM)
	fmt.Printf("TEST_RING_BIN     = %s\n", TEST_RING_BIN)
	fmt.Printf("TEST_RING_OPTION  = %s\n", TEST_RING_OPTION)
	fmt.Printf("TEST_RING_COMMAND = %s\n", TEST_RING_COMMAND)
	fmt.Printf("TEST_PATH         = %s\n", TEST_PATH)

	resultColor := "\033[32m"
	if succNum < allNum {
		resultColor = "\033[33m"
	}
	fmt.Printf("%s[Result]:\n", resultColor)
	fmt.Printf("Pass/All = %d/%d\n", succNum, allNum)
	fmt.Printf("NotTest  = %d\n", notTestNum)
	fmt.Printf("Fail     = %d\n", failNum)
	fmt.Printf("Usetime  = %dS\n", int(time.Since(startTime).Seconds()))

	printNotPassCase()
}
