//
// File:    int-000.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2022-05-19
//

function println_bool(var bool bool_value);
function println_int(var int int_value);
function println_double(var double double_value);
function println_string(var string string_value);
function debug_assert(var bool bool_value);
function exit(var int int_value);

// -----------------------------

var int int_value_1;
var int int_value_2;
var int int_value_3;
var int int_value_4;
var int int_value_5;
var int int_value_6;
var int int_value_7;
var int int_value_8;
var int int_value_9;
var int int_value_10;


var int count;
var int sum;

count = 0;
sum = 0;

for(int_value_1 = 1; int_value_1 <= 4; int_value_1++) {
	for(int_value_2 = 1; int_value_2 <= 4; int_value_2++) {
		for(int_value_3 = 1; int_value_3 <= 4; int_value_3++) {
			for(int_value_4 = 1; int_value_4 <= 4; int_value_4++) {
				for(int_value_5 = 1; int_value_5 <= 4; int_value_5++) {
					for(int_value_6 = 1; int_value_6 <= 4; int_value_6++) {
						for(int_value_7 = 1; int_value_7 <= 4; int_value_7++) {
							for(int_value_8 = 1; int_value_8 <= 4; int_value_8++) {
								for(int_value_9 = 1; int_value_9 <= 4; int_value_9++) {
									for(int_value_10 = 1; int_value_10 <= 4; int_value_10++) {
										count++;
										sum += int_value_1 + int_value_2 + int_value_3 + int_value_4 + int_value_5 + int_value_6 + int_value_7 + int_value_8 + int_value_9 + int_value_10;
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

						

println_string("finish for====");
println_int(count);
debug_assert(count == 1048576);
println_int(sum);
debug_assert(sum == 26214400);
println_string("finish for====");



//---------------
println_string("");
println_string("");



count = 0;
sum = 0;

for(int_value_1 = 1; int_value_1 <= 4; int_value_1++) {
	for(int_value_2 = 1; int_value_2 <= 4; int_value_2++) {
		for(int_value_3 = 1; int_value_3 <= 4; int_value_3++) {
			for(int_value_4 = 1; int_value_4 <= 4; int_value_4++) {
				for(int_value_5 = 1; int_value_5 <= 4; int_value_5++) {
					for(int_value_6 = 1; int_value_6 <= 4; int_value_6++) {
						for(int_value_7 = 1; int_value_7 <= 4; int_value_7++) {
							for(int_value_8 = 1; int_value_8 <= 4; int_value_8++) {
								for(int_value_9 = 1; int_value_9 <= 4; int_value_9++) {
									for(int_value_10 = 1; int_value_10 <= 4; int_value_10++) {
										sum++;
										if(int_value_1 == 4) {
											break 10;
										}
										count++;
										// sum += int_value_1 + int_value_2 + int_value_3 + int_value_4 + int_value_5 + int_value_6 + int_value_7 + int_value_8 + int_value_9 + int_value_10;
									}
								}
							}
						}
					}
				}
			}
		}
	}
}


println_string("finish for====");
println_int(count);
debug_assert(count == 786432);
println_int(sum);
debug_assert(sum == 786433);
println_string("finish for====");







//---------------
println_string("");
println_string("");



count = 0;
sum = 0;

for(int_value_1 = 1; int_value_1 <= 4; int_value_1++) {
	for(int_value_2 = 1; int_value_2 <= 4; int_value_2++) {
		for(int_value_3 = 1; int_value_3 <= 4; int_value_3++) {
			for(int_value_4 = 1; int_value_4 <= 4; int_value_4++) {
				for(int_value_5 = 1; int_value_5 <= 4; int_value_5++) {
					for(int_value_6 = 1; int_value_6 <= 4; int_value_6++) {
						for(int_value_7 = 1; int_value_7 <= 4; int_value_7++) {
							for(int_value_8 = 1; int_value_8 <= 4; int_value_8++) {
								for(int_value_9 = 1; int_value_9 <= 4; int_value_9++) {
									for(int_value_10 = 1; int_value_10 <= 4; int_value_10++) {
										if(int_value_10 == 1) {
											break 1;
										}
										count++;
									}
								}
							}
						}
					}
				}
			}
		}
	}
}


println_string("finish for====");
println_int(count);
debug_assert(count == 0);
println_int(sum);
debug_assert(sum == 0);
println_string("finish for====");


//---------------
println_string("");
println_string("");



count = 0;
sum = 0;

for(int_value_1 = 1; int_value_1 <= 4; int_value_1++) {
	for(int_value_2 = 1; int_value_2 <= 4; int_value_2++) {
		for(int_value_3 = 1; int_value_3 <= 4; int_value_3++) {
			for(int_value_4 = 1; int_value_4 <= 4; int_value_4++) {
				for(int_value_5 = 1; int_value_5 <= 4; int_value_5++) {
					for(int_value_6 = 1; int_value_6 <= 4; int_value_6++) {
						for(int_value_7 = 1; int_value_7 <= 4; int_value_7++) {
							for(int_value_8 = 1; int_value_8 <= 4; int_value_8++) {
								for(int_value_9 = 1; int_value_9 <= 4; int_value_9++) {
									for(int_value_10 = 1; int_value_10 <= 4; int_value_10++) {
										if(int_value_10 == 1) {
											break 10;
										}
										count++;
									}
								}
							}
						}
					}
				}
			}
		}
	}
}


println_string("finish for====");
println_int(count);
debug_assert(count == 0);
println_int(sum);
debug_assert(sum == 0);
println_string("finish for====");