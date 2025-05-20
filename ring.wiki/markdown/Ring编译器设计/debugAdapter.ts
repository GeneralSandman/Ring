// src/debugAdapter.ts
import * as vscode from 'vscode';
import { DebugSession, InitializedEvent, TerminatedEvent, StoppedEvent, OutputEvent, 
         Thread, StackFrame, Scope, Source, Handles } from 'vscode-debugadapter';
import { DebugProtocol } from 'vscode-debugprotocol';
import { spawn, ChildProcess } from 'child_process';

export class GDBDebugSession extends DebugSession {
    private gdbProcess: ChildProcess | undefined;
    private variableHandles = new Handles<string>();
    
    public initializeRequest(response: DebugProtocol.InitializeResponse, args: DebugProtocol.InitializeRequestArguments): void {
        // 设置调试器能力
        response.body = {
            supportsConfigurationDoneRequest: true,
            supportsFunctionBreakpoints: true,
            supportsConditionalBreakpoints: true,
            supportsEvaluateForHints: true,
            exceptionBreakpointFilters: [],
            supportsStepBack: false,
            supportsSetVariable: true,
            supportsRestartFrame: false,
            supportsGotoTargetsRequest: false,
            supportsStepInTargetsRequest: false,
            supportsCompletionsRequest: false,
            supportsModulesRequest: false,
            supportsRestartRequest: false,
            supportsTerminateRequest: true
        };
        this.sendResponse(response);
    }

    public async launchRequest(response: DebugProtocol.LaunchResponse, args: any): Promise<void> {
        // 启动GDB进程
        this.gdbProcess = spawn('gdb', ['--interpreter=mi2', args.program]);
        
        this.gdbProcess.stdout?.on('data', (data) => {
            this.handleGDBNotification(data.toString());
        });
        
        this.gdbProcess.stderr?.on('data', (data) => {
            this.sendEvent(new OutputEvent(data.toString(), 'stderr'));
        });
        
        this.gdbProcess.on('exit', () => {
            this.sendEvent(new TerminatedEvent());
        });
        
        // 发送初始化完成事件
        this.sendEvent(new InitializedEvent());
        this.sendResponse(response);
    }

    private handleGDBNotification(data: string): void {
        // 解析GDB/MI输出并转换为VSCode调试协议事件
        // 这里需要实现GDB/MI协议的解析
    }

    public setBreakPointsRequest(response: DebugProtocol.SetBreakpointsResponse, args: DebugProtocol.SetBreakpointsArguments): void {
        // 设置断点
        const path = args.source.path as string;
        const breakpoints: DebugProtocol.Breakpoint[] = [];
        
        if (args.breakpoints) {
            for (const bp of args.breakpoints) {
                const line = bp.line;
                this.sendCommand(`-break-insert ${path}:${line}`).then(() => {
                    breakpoints.push({
                        verified: true,
                        line: line
                    });
                });
            }
        }
        
        response.body = {
            breakpoints: breakpoints
        };
        this.sendResponse(response);
    }

    public threadsRequest(response: DebugProtocol.ThreadsResponse): void {
        // 返回线程信息
        response.body = {
            threads: [
                new Thread(1, "thread 1")
            ]
        };
        this.sendResponse(response);
    }

    public stackTraceRequest(response: DebugProtocol.StackTraceResponse, args: DebugProtocol.StackTraceArguments): void {
        // 获取调用栈
        this.sendCommand(`-stack-list-frames`).then((result) => {
            const frames: StackFrame[] = [];
            // 解析GDB输出并构建栈帧
            response.body = {
                stackFrames: frames,
                totalFrames: frames.length
            };
            this.sendResponse(response);
        });
    }

    public scopesRequest(response: DebugProtocol.ScopesResponse, args: DebugProtocol.ScopesArguments): void {
        // 获取变量作用域
        response.body = {
            scopes: [
                new Scope("Local", this.variableHandles.create("local"), false),
                new Scope("Global", this.variableHandles.create("global"), false)
            ]
        };
        this.sendResponse(response);
    }

    public variablesRequest(response: DebugProtocol.VariablesResponse, args: DebugProtocol.VariablesArguments): void {
        // 获取变量值
        const variables: DebugProtocol.Variable[] = [];
        const handle = this.variableHandles.get(args.variablesReference);
        
        if (handle === "local") {
            this.sendCommand(`-stack-list-variables --simple-values`).then((result) => {
                // 解析变量并添加到variables数组
                response.body = {
                    variables: variables
                };
                this.sendResponse(response);
            });
        }
    }

    public continueRequest(response: DebugProtocol.ContinueResponse, args: DebugProtocol.ContinueArguments): void {
        this.sendCommand("-exec-continue").then(() => {
            this.sendResponse(response);
        });
    }

    public nextRequest(response: DebugProtocol.NextResponse, args: DebugProtocol.NextArguments): void {
        this.sendCommand("-exec-next").then(() => {
            this.sendResponse(response);
        });
    }

    public stepInRequest(response: DebugProtocol.StepInResponse, args: DebugProtocol.StepInArguments): void {
        this.sendCommand("-exec-step").then(() => {
            this.sendResponse(response);
        });
    }

    public stepOutRequest(response: DebugProtocol.StepOutResponse, args: DebugProtocol.StepOutArguments): void {
        this.sendCommand("-exec-finish").then(() => {
            this.sendResponse(response);
        });
    }

    public pauseRequest(response: DebugProtocol.PauseResponse, args: DebugProtocol.PauseArguments): void {
        this.sendCommand("-exec-interrupt").then(() => {
            this.sendResponse(response);
        });
    }

    private sendCommand(command: string): Promise<string> {
        return new Promise((resolve, reject) => {
            if (!this.gdbProcess) {
                reject("GDB process not running");
                return;
            }
            
            this.gdbProcess.stdin?.write(`${command}\n`);
            // 需要实现命令响应处理
        });
    }
}