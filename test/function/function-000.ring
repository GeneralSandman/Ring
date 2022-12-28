

print("[test-case 001]\n");
function doit1() {
    print("I'm function doit1, go go go!\n");
}
doit1();
print("\n\n");



print("[test-case 002]\n");
function doit2(var int arguement1) {
    print("I'm function doit2, arguement1=", arguement1, "\n");
}
doit2(1);
print("\n\n");



print("[test-case 003]\n");
function doit3(var int arguement1, var int arguement2) {
    print("I'm function doit3, ", "arguement1=", arguement1, ", arguement2=", arguement2, "\n");
}
doit3(1, 2);
print("\n\n");



print("[test-case 004]\n");
function doit4(var int arguement1, var int arguement2, var double arguement3) {
    print("I'm function doit4, ", "arguement1=", arguement1, ", arguement2=", arguement2, ", arguement3=", arguement3, "\n");
}
doit4(1, 2, 3.1);
print("\n\n");



var int return_int_value;


print("[test-case 005]\n");
function doit5()->(int) {
    print("I'm function doit5, go go go!\n");
	return 5;
}
return_int_value = doit5();
print("function:doit5 return value = ", return_int_value, "\n");
print("\n\n");




print("[test-case 006]\n");
function doit6(var int arguement1)->(int) {
    print("I'm function doit6, arguement1=", arguement1, "\n");
	return arguement1;
}
return_int_value = doit6(6);
print("function:doit6 return value = ", return_int_value, "\n");
print("\n\n");



print("[test-case 007]\n");
function doit7(var int arguement1, var int arguement2)->(int) {
    print("I'm function doit7, ", "arguement1=", arguement1, ", arguement2=", arguement2, "\n");
	return arguement1 + arguement2;
}
return_int_value = doit7(2, 5);
print("function:doit6 return value = ", return_int_value, "\n");
print("\n\n");


// FIXME: test/beat/bug-list/001.ring
// print("[test-case 008]\n");
// function doit8(var int arguement1, var int arguement2, var double arguement3) (int) {
//     print("I'm function doit8, ", "arguement1=", arguement1, ", arguement2=", arguement2, ", arguement3=", arguement3, "\n");
// 	return arguement1 + arguement2 + int(arguement3);
// }

// return_int_value = doit8(1, 2, 3.1);
// print("function:doit8 return value = ", return_int_value, "\n");
// print("\n\n");
