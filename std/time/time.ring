//
// File:    time.ring
// Author:  GeneralSandman - generalsandman@163.com
// CDate:   2024-08-05
// UDate:   2024-08-05
//

package time

import {

}

// 返回 纳秒时间戳
@native
fn time() -> (int64);


// 参数为 ns
@native
fn sleep(var int64 ns);