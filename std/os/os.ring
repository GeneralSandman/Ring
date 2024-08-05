//
// File:    os.ring
// Author:  GeneralSandman - generalsandman@163.com
// CDate:   2023-10-08
// UDate:   2023-10-08
//

package os

import {

}

global {

}

@native
function exit(var int int_value);

@native
function remove(var string name);

@native
function getenv(var string name) -> (string);

@native
function setenv(var string name, var string value);
