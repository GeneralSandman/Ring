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




typedef class Job {
    var bool    Running;
    var int     JobID;
    var double  Score;
};


var Job compiler_job_0;

println_bool(compiler_job_0.Running);
println_int(compiler_job_0.JobID);
println_double(compiler_job_0.Score);
