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
fn exit(var int int_value);

@native
fn remove(var string name);

@native
fn getenv(var string name) -> (string);

@native
fn setenv(var string name, var string value);
