package main

import {
	fmt;
	os;
	debug;
}

typedef Job = class {
	var bool Bool;
	var int Int;
	var int64 Int64;
	var double Double;
	var string String;

	fn printInfo() {
		return fmt::sprintf("Job({}, {}, {}, {}, {})\n", self.Bool, self.Int, self.Int64, self.Double, self.String);
	}
}


fn main() {
	var Job job_value;
	job_value.printInfo();

}