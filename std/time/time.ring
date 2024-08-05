//
// File:    time.ring
// Author:  GeneralSandman - generalsandman@163.com
// CDate:   2024-08-05
// UDate:   2024-08-05
//

package time

import {

}

// unix 10位秒时间戳
@native
function time() -> (int64);


// 参数为 ns
@native
function sleep(var int64 ns);