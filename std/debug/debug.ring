//
// File:    debug.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2023-04-14
//

package debug

import {

}

@native
fn assert(var bool bool_value);


@native
fn print_call_stack();

@native
fn var_dump(var any... any_value);