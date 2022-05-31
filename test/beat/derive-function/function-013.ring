//
// File:    function-013.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2022-05-31
//

function println_bool(var bool bool_value);
function println_int(var int int_value);
function println_double(var double double_value);
function println_string(var string string_value);
function debug_assert(var bool bool_value);
function exit(var int int_value);

// -----------------------------



function get_level_by_score(var int score) -> (int) {
	if(0<=score and score<10) {
		println_string("level 0");
	} elseif(10<=score and score<20) {
		println_string("level 1");
	} elseif(20<=score and score<30) {
		println_string("level 2");
	} elseif(30<=score and score<40) {
		println_string("level 3");
	} elseif(40<=score and score<50) {
		println_string("level 4");
	} elseif(50<=score and score<60) {
		println_string("level 5");
	} elseif(60<=score and score<70) {
		println_string("level 6");
	} elseif(70<=score and score<80) {
		println_string("level 7");
	} elseif(80<=score and score<90) {
		println_string("level 8");
	} elseif(90<=score and score<=100) {
		println_string("level 9");
	} elseif(score == 100) {
		println_string("level 10");
	} else {
		println_string("score invalid");
		return 0;
	}

	return score/10;
}


var int score;
var int level;

for(score = -9; score<=110; score+=10) {
	level = get_level_by_score(score);

	println_string("=====");
	println_int(score);
	println_int(level);
	println_string("=====");

	println_string("");
}



