
// function a() {
// 	print("function a\n");
// }

// function b() {
// 	print("function b\n");
// }

var int int_value_1;

int_value_1 = 101;
print("int_value_1=", int_value_1, "\n");

int_value_1 = true ? 2 : 1; 
print("int_value_1=", int_value_1, "\n");

int_value_1 = false ? 2 : 1; 
print("int_value_1=", int_value_1, "\n");


int_value_1 = true ? 1+1-1*2*3*4 : 2*2*2*2 ;
print("int_value_1=", int_value_1, "\n");

int_value_1 = false ? 1+1-1*2*3*4 : 2*2*2*2 ;
print("int_value_1=", int_value_1, "\n");


print("-----\n");

var int int_value_2;
var int a;
var int b;

a = 10;
b = 9;


if(a > b) {
	int_value_2 = a;
} else {
	int_value_2 = b;
}
print("int_value_2=", int_value_2, "\n");



int_value_2 = a > b ? a : b ;
print("int_value_2=", int_value_2, "\n");
