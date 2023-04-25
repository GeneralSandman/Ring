
package main

import {
	fmt;
	debug;
}



function get_level_by_score(var int score) -> (int) {
	if(0<=score and score<=100) {
		return score/10;
	} else {
		return 0;
	}
}

@main
function main() {

var int sum;
var int score;
var int level;

sum = 0;
for(score = -9; score<=110; score+=1) {
	level = get_level_by_score(score);
	sum += level;
}
fmt::println_int(sum);
debug::debug_assert(sum == 460);


sum = 0;
for(score = -9; score<=110; score+=1) {
	sum += get_level_by_score(score); 
}
fmt::println_int(sum);
debug::debug_assert(sum == 460);

}