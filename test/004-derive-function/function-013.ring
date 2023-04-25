
package main

import {
	fmt;
	debug;
}




function get_level_by_score(var int score) -> (int) {
	if(0<=score and score<10) {
		fmt::println_string("level 0");
	} elseif(10<=score and score<20) {
		fmt::println_string("level 1");
	} elseif(20<=score and score<30) {
		fmt::println_string("level 2");
	} elseif(30<=score and score<40) {
		fmt::println_string("level 3");
	} elseif(40<=score and score<50) {
		fmt::println_string("level 4");
	} elseif(50<=score and score<60) {
		fmt::println_string("level 5");
	} elseif(60<=score and score<70) {
		fmt::println_string("level 6");
	} elseif(70<=score and score<80) {
		fmt::println_string("level 7");
	} elseif(80<=score and score<90) {
		fmt::println_string("level 8");
	} elseif(90<=score and score<=100) {
		fmt::println_string("level 9");
	} elseif(score == 100) {
		fmt::println_string("level 10");
	} else {
		fmt::println_string("score invalid");
		return 0;
	}

	return score/10;
}


@main
function main() {

var int score;
var int level;

for(score = -9; score<=110; score+=10) {
	level = get_level_by_score(score);

	fmt::println_string("=====");
	fmt::println_int(score);
	fmt::println_int(level);
	fmt::println_string("=====");

	fmt::println_string("");
}

}

