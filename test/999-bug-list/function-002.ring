
package main

import {
	fmt;
	debug;
}

@main
fn main() {


// 先简单写，后改成 rust的方式
printf("_, _, _, _\n", true, 123, 456.123456, "hello world");

printf("_, _\n", true, false);
printf("_, _\n", 123, 234);
printf("_, _\n", 123.456, 654.321);
printf("_, _\n", "hello world", "hello world");

}