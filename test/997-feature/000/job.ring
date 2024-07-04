//
// File:    job.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2024-06-27
//

package main

import {
	fmt;
}

typedef class Job1 {
    field bool    Bool;
    field int     Int;
    field double  Double;
    field string  String;

    method printInfo() {
        fmt::printf("Job1({}, {}, {}, {})\n", self.Bool, self.Int, self.Double, self.String);
    }
}