//
// File:    int-013.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2022-05-09
//

function println_bool(var bool bool_value);
function println_int(var int int_value);
function println_double(var double double_value);


var int int_value;

int_value = 0;
println_int(int_value);

int_value = 1;
println_int(int_value);

int_value = 255;
println_int(int_value);

int_value = 256;
println_int(int_value);

int_value = 257;
println_int(int_value);

int_value = 65535;
println_int(int_value);

int_value = 65536;
println_int(int_value);

int_value = 65537;
println_int(int_value);

int_value = 65538;
println_int(int_value);

int_value = 2147483647; // INT_MAX
println_int(int_value);


int_value = -2147483648; // INT_MIN
println_int(int_value);

int_value = -2147483647;
println_int(int_value);

int_value = -1;
println_int(int_value);

int_value = -0;
println_int(int_value);


//-----------------


int_value = 0 + 1;
println_int(int_value);

int_value = 1 + 2;
println_int(int_value);

int_value = 2 + 3;
println_int(int_value);


int_value = 1 + 2 * 3 + 4 * 5 + 9 / 1;
println_int(int_value);


//-----------------
int_value = 1;
println_int(int_value);

int_value += 1;
println_int(int_value);

int_value += 1;
println_int(int_value);

int_value += 1;
println_int(int_value);


int_value += 2;
println_int(int_value);

int_value += 2;
println_int(int_value);

int_value += 2;
println_int(int_value);

int_value += 2;
println_int(int_value);



//-----------------
int_value = 10;
println_int(int_value);

int_value -= 1;
println_int(int_value);

int_value -= 1;
println_int(int_value);

int_value -= 1;
println_int(int_value);


int_value -= 2;
println_int(int_value);

int_value -= 2;
println_int(int_value);

int_value -= 2;
println_int(int_value);

int_value -= 2;
println_int(int_value);


//-----------------
int_value = 1;
println_int(int_value);

int_value *= 1;
println_int(int_value);

int_value *= 1;
println_int(int_value);

int_value *= 1;
println_int(int_value);


int_value *= 2;
println_int(int_value);

int_value *= 2;
println_int(int_value);

int_value *= 2;
println_int(int_value);

int_value *= 2;
println_int(int_value);


//-----------------
int_value = 100;
println_int(int_value);

int_value /= 1;
println_int(int_value);

int_value /= 1;
println_int(int_value);

int_value /= 1;
println_int(int_value);


int_value /= 2;
println_int(int_value);

int_value /= 2;
println_int(int_value);

int_value /= 2;
println_int(int_value);

int_value /= 2;
println_int(int_value);


int_value /= 3;
println_int(int_value);

int_value /= 3;
println_int(int_value);

int_value /= 3;
println_int(int_value);

int_value /= 3;
println_int(int_value);
