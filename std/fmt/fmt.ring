//
// File:    fmt.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2023-04-14
//

package fmt

import {

}

function println_bool(var bool bool_value);
function println_int(var int int_value);
function println_double(var double double_value);
function println_string(var string string_value);
function debug_assert(var bool bool_value);
function exit(var int int_value);

typedef class Fmt {
    field bool    Running;
    field int     JobID;
    field double  Score;

    @constructor
    method Fmt(var bool _Running, var int _JobID, var double _Score);

    method PrintInfo();
};