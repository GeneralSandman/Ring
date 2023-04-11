//
// File:    class-001.ring
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

/*
method Job::Init(var bool _Running, var int _JobID, var double _Score) {
    self.Running = _Running;
    self.JobID   = _JobID;
    self.Score   = _Score;
}
*/

/*
method Job::PrintInfo() {
    println_bool(self.Running);
    println_int(self.JobID);
    println_double(self.Score);
}
*/

/*
println_string("\ntest case 1");
var bool    Running;
var int     JobID;
var double  Score;
println_bool(Running);
println_int(JobID);
println_double(Score);


println_string("\ntest case 2");
*/



var Job job_0; // = Job(true, 1, 1.1);

// println_bool(job_0.Running);
// println_int(job_0.JobID);
// println_double(job_0.Score);

job_0.Running = true;
job_0.JobID = 1;
job_0.Score = 1.1;
println_bool(job_0.Running);
println_int(job_0.JobID);
println_double(job_0.Score);
