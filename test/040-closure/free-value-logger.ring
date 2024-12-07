//
// File:    std-debug-000.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2023-04-24
//

package main

import {
	os;
	debug;
	fmt;
}

typedef function(string) FuncType1;

// TestDetail: 测试见的FreeValue , 不支持逃逸
@main
function main() {

	// test_log();
	// return;

	var FuncType1 job_logger;
	var FuncType1 workflow_logger;

	job_logger = get_logger("INFO", "Job");
	workflow_logger = get_logger("INFO", "Workflow");

	fmt::println("------------");
	job_logger("start");
	job_logger("running");
	job_logger("done");


	fmt::println("------------");
	workflow_logger("lock");
	workflow_logger("unlock");

}

function get_logger(var string level, var string prefix) -> (FuncType1) {

	return function(var string message) {
		fmt::printf("[{}]{} {}\n", level, prefix, message);
	};
}



function test_log() {
	fmt::println("------------");
	log("INFO", "Job", "start");
	log("INFO", "Job", "running");
	log("INFO", "Job", "done");

	fmt::println("------------");
	log("INFO", "Workflow", "lock");
	log("INFO", "Workflow", "unlock");
	
}

function log(var string level, var string prefix, var string message) {
	fmt::printf("[{}]{} {}\n", level, prefix, message);
}

