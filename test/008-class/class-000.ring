//
// File:    class-000.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2023-04-11
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


typedef class Job {
    field bool    Running;
    field int     JobID;
    field double  Score;

    @constructor
    method Job(var bool _Running, var int _JobID, var double _Score);

    method PrintInfo();
};

var Job job_0;

println_string("\ntest case 1");
println_bool(job_0.Running);
println_int(job_0.JobID);
println_double(job_0.Score);
debug_assert(job_0.Running == false);
debug_assert(job_0.JobID == 0);
debug_assert(job_0.Score == 0.0);

println_string("\ntest case 2");
job_0.Running = true;
job_0.JobID = 1;
job_0.Score = 1.1;
println_bool(job_0.Running);
println_int(job_0.JobID);
println_double(job_0.Score);
debug_assert(job_0.Running == true);
debug_assert(job_0.JobID == 1);
debug_assert(job_0.Score == 1.1);



println_string("\ntest case 3");
var Job job_1;
job_1.Running = true;
job_1.JobID = 2;
job_1.Score = 2.2;
println_bool(job_1.Running);
println_int(job_1.JobID);
println_double(job_1.Score);
debug_assert(job_1.Running == true);
debug_assert(job_1.JobID == 2);
debug_assert(job_1.Score == 2.2);

println_string("\ntest case 4");
println_int(job_0.JobID + job_1.JobID);
debug_assert(job_0.JobID + job_1.JobID == 3);

println_string("\ntest case 5");
println_double(job_0.Score + job_1.Score);
debug_assert(job_0.Score + job_1.Score == 3.300000);
// 这里有bug