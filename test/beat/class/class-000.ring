//
// File:    class-000.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2022-07-22
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


typedef class Student {

	var string name;

    @public 
    var string name;

    @private
    var string name;

    @public
    @private
    @delete
    var string name;





};

	
// 	// function Student(var string name, var int age, var int score);
	
// 	function print() {
// 		print("Student::print\n");
// 	}
// 	function getInfo()->(string, int, int) {
// 		// return self.name, self.age, self.score;
// 	}

// 	function getInfo2()->(string, int, int);
// 	function getInfo3()->(string, int, int);

