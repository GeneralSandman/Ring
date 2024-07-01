//
// File:    buildin.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2024-07-01
//

package buildin

import {

}

@native
function len(var any array) -> (int);

@native
function capacity(var any array) -> (int);


@native
function push(var any array, var any value);

@native
function pop(var any array) -> (any);


@native
function to_string(var any value) -> (string);

@native
function to_int64(var any value) -> (int64);


