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


fn main(var string[] args) {

    fmt::println(len(args));
    fmt::println(cap(args));

    fmt::println(args);

    var string arg;
    for(arg = range args) {
        fmt::println(arg);
    }
}
