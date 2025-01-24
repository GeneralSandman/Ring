//
// File:    job.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2024-06-27
//

package main

import {
	fmt;
}

typedef Job1 = class {
    var bool    Bool;
    var int     Int;
    var double  Double;
    var string  String;

    fn printInfo() {
        fmt::printf("Job1({}, {}, {}, {})\n", self.Bool, self.Int, self.Double, self.String);
    }
}