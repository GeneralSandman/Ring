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


@main
function main(var string[] args) {

    fmt::println(len(args));
    fmt::println(capacity(args));

    fmt::println(args);

    var string arg;
    for(arg in range args) {
        fmt::println(arg);
    }
}
