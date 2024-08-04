
package main

import {
	fmt;
	debug;
}

enum int AccessMode {
    O_RDONLY  = 0;
    O_WRONLY  = 1;
    // O_RDWR    = 2;
    // O_ACCMODE = 3;
}

@main
function main() {
	fmt::println(AccessMode::O_RDONLY);
}

enum string Region {
	Dev        = "dev";
	Test       = "test";
	PreProduct = "preproduct";
	Product    = "product";
}