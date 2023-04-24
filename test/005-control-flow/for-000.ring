
package main

import {
	fmt;
	debug;
}

@main
function main() {
    

var int int_value;
var int sum;


// -----------
fmt::println_string("[Test Case 1]");

sum = 0;
for(int_value = 1; int_value <= 100; int_value = int_value + 1) {
    sum = sum + int_value;
}

fmt::println_int(sum);


// -----------
fmt::println_string("[Test Case 2]");

sum = 0;
for(int_value = 1; int_value <= 100; int_value++) {
    sum += int_value;
}

fmt::println_int(sum);


// -----------
fmt::println_string("[Test Case 3]");

sum = 0;
int_value = 1;
for(; int_value <= 100; int_value+=1) {
    sum += int_value;
}

fmt::println_int(sum);


// -----------
fmt::println_string("[Test Case 4]");

sum = 0;
int_value = 1;
for(; int_value <= 100;) {
    sum += int_value;
    int_value += 1;
}


fmt::println_int(sum);




// -----------
fmt::println_string("[Test Case 5]");

sum = 0;
for(int_value = 1; int_value <= 200; int_value = int_value + 1) {
    sum = sum + int_value;
}

fmt::println_int(sum);


// ------------
fmt::println_string("[Test Case 6]");

sum = 1;
for(int_value = 1; int_value <= 10; int_value = int_value + 1) {
    sum = sum * int_value;
}

fmt::println_int(sum);

}
