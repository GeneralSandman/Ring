//
// File:    fmt.ring
// Author:  GeneralSandman - generalsandman@163.com
// CDate:   2023-04-14
// UDate:   2023-04-19
//

package fmt

import {

}

@native
fn println_bool(var bool bool_value);

@native
fn println_int(var int int_value);

@native
fn println_int64(var int64 int64_value);

@native
fn println_double(var double double_value);

@native
fn println_string(var string string_value);

@native
fn println_pointer(var any any_value);

@native
fn println(var any... any_value);

@native
fn printf(var string format, var any... any_value);

@native
fn sprintf(var string format, var any... any_value) -> (string);