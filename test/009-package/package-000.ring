//
// File:    package-000.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2022-05-31
//

// function println_bool(var bool bool_value);
// function println_int(var int int_value);
// function println_double(var double double_value);
// function println_string(var string string_value);
// function debug_assert(var bool bool_value);
// function exit(var int int_value);

// -----------------------------


package main

import {
	fmt;
    strings;
    debug;
}

typedef class Job {
    field bool    Running;
    field int     JobID;
    field double  Score;

    @constructor
    method Job(var bool _Running, var int _JobID, var double _Score);

    method PrintInfo();
};

var Job job_0;