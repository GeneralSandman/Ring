package main

import {
    fmt;
    debug;
    runtime;
	reflect;
}


fn main() {
	// test_invalid_break_num();
	// test_for_range_continue();
}


fn test_invalid_break_num() {
	var int index = 0;
	for(index = 0; index < 10; index++) {
		if(index == 5) {
			break 2;
		}
	}
}

fn test_invalid_break() {
	break;
}

fn test_contine_break() {
	continue;
}

fn test_invalid_break_num() {
	var int index = 0;
	for(index = 0; index < 10; index++) {
		if(index == 5) {
			continue;
		}
	}
}