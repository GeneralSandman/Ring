//
// File:    function-019.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2022-05-31
//

function println_bool(var bool bool_value);
function println_int(var int int_value);
function println_double(var double double_value);
function println_string(var string string_value);
function debug_assert(var bool bool_value);
function exit(var int int_value);
function print(var any value) -> (int);
function println(var any value) -> (int);
function printf(var string format, var any value)   -> (int);
function printfln(var string format, var any value) -> (int);


// -----------------------------


function get_level_by_score(var int score) -> (int) {
	if(0<=score and score<=100) {
		return score/10;
	} else {
		return 0;
	}
}

var int sum;
var int score;
var int level;

sum = 0;
for(score = -9; score<=110; score+=1) {
	level = get_level_by_score(score);
	sum += level;
}
println_int(sum);
debug_assert(sum == 460);


sum = 0;
for(score = -9; score<=110; score+=1) {
	sum += get_level_by_score(score); 
}
println_int(sum);
debug_assert(sum == 460);

