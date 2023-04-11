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

    method PrintInfo() {
        println_string("invoke Job::PrintInfo");
    }

    method GetStatus() {
        println_string("invoke Job::GetStatus");
    }

    method GetJobID() {
        println_string("invoke Job::GetJobID");
    }

    method GetScore() {
        println_string("invoke Job::GetScore");
    }
};

println_string("\ntest case 1");

var Job job_0;
job_0.PrintInfo();
job_0.GetStatus();
job_0.GetJobID();
job_0.GetScore();

println_string("\ntest case 2");

var Job job_1;
job_1.PrintInfo();
job_1.GetStatus();
job_1.GetJobID();
job_1.GetScore();
