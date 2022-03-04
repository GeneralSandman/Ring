var int int_value_1 = 0;
print("int_value_1(0)=", int_value_1, "\n");
int_value_1 = -int_value_1;
print("int_value_1(0)=", int_value_1, "\n");

print("\n\n");

var int int_value_2 = 1;
print("int_value_2(1)=", int_value_2, "\n");
int_value_2 = -int_value_2;
print("int_value_2(-1)=", int_value_2, "\n");


print("\n\n");

var int int_value_3 = 2147483648;
print("int_value_3(2147483648)=", int_value_3, "\n");
int_value_3 = -int_value_3;
print("int_value_3(-2147483648)=", int_value_3, "\n");

print("\n\n");


var int int_value_4 = -2147483648;
print("int_value_4(-2147483648)=", int_value_4, "\n");
int_value_4 = -int_value_4;
print("int_value_4(-2147483648)=", int_value_4, "\n");


print("\n\n");

var int int_value_5 = 0-2147483648;
print("int_value_5(0-2147483648)=", int_value_5, "\n");
int_value_5 = -int_value_5;
print("int_value_5(-2147483648)=", int_value_5, "\n");

