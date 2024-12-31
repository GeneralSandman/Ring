//
// File:    buildin.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2024-07-01
//

package buildin

import {

}

@native
fn len(var any array) -> (int);

@native
fn capacity(var any array) -> (int);


@native
fn push(var any array, var any value);

@native
fn pop(var any array) -> (any);


@native
fn to_string(var any value) -> (string);

@native
fn to_int64(var any value) -> (int64);


