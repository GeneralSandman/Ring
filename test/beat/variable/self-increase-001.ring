var int int_value_1;
var int int_value_2;



print("test self-increase-suffix\n");

print("\n");
int_value_1++;
print("int_value_1=", int_value_1, "\n");
print("int_value_2=", int_value_2, "\n");

print("\n");
int_value_2 = int_value_1++;
print("int_value_1=", int_value_1, "\n");
print("int_value_2=", int_value_2, "\n");

print("\n");
int_value_2 = int_value_1++;
print("int_value_1=", int_value_1, "\n");
print("int_value_2=", int_value_2, "\n");


print("\n");
int_value_2 = int_value_1++;
print("int_value_1=", int_value_1, "\n");
print("int_value_2=", int_value_2, "\n");





print("test self-increase-prefix\n");

print("\n");
++int_value_1;
print("int_value_1=", int_value_1, "\n");
print("int_value_2=", int_value_2, "\n");

print("\n");
int_value_2 = ++int_value_1;
print("int_value_1=", int_value_1, "\n");
print("int_value_2=", int_value_2, "\n");

print("\n");
int_value_2 = ++int_value_1;
print("int_value_1=", int_value_1, "\n");
print("int_value_2=", int_value_2, "\n");

print("\n");
int_value_2 = ++int_value_1;
print("int_value_1=", int_value_1, "\n");
print("int_value_2=", int_value_2, "\n");








print("test self-decrease-suffix\n");

print("\n");
int_value_1--;
print("int_value_1=", int_value_1, "\n");
print("int_value_2=", int_value_2, "\n");

print("\n");
int_value_2 = int_value_1--;
print("int_value_1=", int_value_1, "\n");
print("int_value_2=", int_value_2, "\n");

print("\n");
int_value_2 = int_value_1--;
print("int_value_1=", int_value_1, "\n");
print("int_value_2=", int_value_2, "\n");


print("\n");
int_value_2 = int_value_1--;
print("int_value_1=", int_value_1, "\n");
print("int_value_2=", int_value_2, "\n");





print("test self-decrease-prefix\n");

print("\n");
int_value_1--;
print("int_value_1=", int_value_1, "\n");
print("int_value_2=", int_value_2, "\n");

print("\n");
int_value_2 = --int_value_1;
print("int_value_1=", int_value_1, "\n");
print("int_value_2=", int_value_2, "\n");

print("\n");
int_value_2 = --int_value_1;
print("int_value_1=", int_value_1, "\n");
print("int_value_2=", int_value_2, "\n");


print("\n");
int_value_2 = --int_value_1;
print("int_value_1=", int_value_1, "\n");
print("int_value_2=", int_value_2, "\n");
// int_value = -2;
// print(int_value, "\n");

// int_value++;
// print(int_value, "\n");

// int_value++;
// print(int_value, "\n");

// int_value++;
// print(int_value, "\n");

// int_value = int_value++; // FIXME: bug
// print(int_value, "\n");

// int_value++;

// function assert(var int except, var int result) {
// 	print("assert\t");
// 	print("except(", except, "),\t");
// 	print("result(", result, ")\t");
// 	if(except == result) {
// 		print("\t[pass]\n");
// 	} else {
// 		print("\t[error]\n");
// 	}
// }


// assert(1+1+1+1, 2*2+1);
// assert(1+1+1+1, 2*2);

// var int int_value_1;
// var int int_value_2;
// var int int_value_3;

// int_value_1, int_value2 = 1, 2;

// print("int_value_1=", int_value_1, "\n");
// print("int_value_2=", int_value_2, "\n");
// print("int_value_3=", int_value_3, "\n");