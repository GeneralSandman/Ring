//
// File:    class-000.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2023-04-11
//

fn println_bool(var bool bool_value);
fn println_int(var int int_value);
fn println_double(var double double_value);
fn println_string(var string string_value);
fn debug_assert(var bool bool_value);
fn exit(var int int_value);
fn print(var any value) -> (int);
fn println(var any value) -> (int);
fn printf(var string format, var any value)   -> (int);
fn printfln(var string format, var any value) -> (int);

// -----------------------------


var double double_value_1 = 1.1;
var double double_value_2 = 1.1;

debug_assert(double_value_1 == 1.1);
debug_assert(double_value_2 == 1.1);
debug_assert(double_value_1 + double_value_2 == 2.2);



typedef Job = class {
    var double  Score;
};

var Job job_0;
var Job job_1;

job_0.Score = 1.1;
job_1.Score = 2.2;
debug_assert(job_0.Score + job_1.Score == 3.3); // 这里存在bug
