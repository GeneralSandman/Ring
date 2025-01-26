//
// File:    runtime.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2025-01-26
//

package runtime

import {

}

@native
fn heap_size() -> (int64);

@native
fn gc();

@native
fn print_call_stack();
