
package main

import {
	fmt;
	debug;
}

@main
function main() {
	

var int int_value_1;
var int int_value_2;
var int int_value_3;
var int int_value_4;
var int int_value_5;
var int int_value_6;
var int int_value_7;
var int int_value_8;
var int int_value_9;
var int int_value_10;


var int count;
var int sum;

count = 0;
sum = 0;

for(int_value_1 = 1; int_value_1 <= 4; int_value_1++) {
	for(int_value_2 = 1; int_value_2 <= 4; int_value_2++) {
		for(int_value_3 = 1; int_value_3 <= 4; int_value_3++) {
			for(int_value_4 = 1; int_value_4 <= 4; int_value_4++) {
				for(int_value_5 = 1; int_value_5 <= 4; int_value_5++) {
					for(int_value_6 = 1; int_value_6 <= 4; int_value_6++) {
						for(int_value_7 = 1; int_value_7 <= 4; int_value_7++) {
							for(int_value_8 = 1; int_value_8 <= 4; int_value_8++) {
								for(int_value_9 = 1; int_value_9 <= 4; int_value_9++) {
									for(int_value_10 = 1; int_value_10 <= 4; int_value_10++) {
										count++;
										sum += int_value_1 + int_value_2 + int_value_3 + int_value_4 + int_value_5 + int_value_6 + int_value_7 + int_value_8 + int_value_9 + int_value_10;
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

						

debug::debug_assert(count == 1048576);
fmt::println_int(count);

debug::debug_assert(sum == 26214400);
fmt::println_int(sum);

}
