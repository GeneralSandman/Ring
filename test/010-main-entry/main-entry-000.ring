//
// File:    main-entry-000.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2023-04-11
//

package job

import {
    fmt;
    debug;
}

fn test(var int int_value_1, var int int_value_2) -> (int,int,int,int) {
	var int int_value_3;
	var int int_value_4;

    int_value_3 = 3;
    int_value_4 = 4;

    return int_value_1, int_value_2, int_value_3, int_value_4;
}

@main
fn main() {
    fmt::println_string("entry main");
    
    var int local_int_value_1;
    var int local_int_value_2;
    var int local_int_value_3;
    var int local_int_value_4;
        
    local_int_value_1, local_int_value_2, local_int_value_3, local_int_value_4 = test(1, 2);
    
    debug::assert(local_int_value_1 == 1);
    debug::assert(local_int_value_2 == 2);
    debug::assert(local_int_value_3 == 3);
    debug::assert(local_int_value_4 == 4);
    
    local_int_value_1+=1;
    debug::assert(local_int_value_1 == 2);
}
