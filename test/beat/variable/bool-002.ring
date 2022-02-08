var bool bool_value;

bool_value = false;
print("false=", bool_value, "\n");

bool_value = true;
print("true=", bool_value, "\n");

bool_value = not false;
print("not false=", bool_value, "\n");

bool_value = not true;
print("not true=", bool_value, "\n");

print("\n");
bool_value = false;
print("bool_value=", bool_value, "\n");
bool_value = not bool_value;
print("not bool_value=", bool_value, "\n");

print("\n");
bool_value = true;
print("bool_value=", bool_value, "\n");
bool_value = not bool_value;
print("not bool_value=", bool_value, "\n");

print("--------\n");

bool_value = 1 and 2;
print("1 and 2 is ", bool_value, "\n");

bool_value = 1 or 2;
print("1 or 2 is ", bool_value, "\n");



bool_value = 0 and 1;
print("0 and 1 is ", bool_value, "\n");

bool_value = 0 or 1;
print("0 or 1 is ", bool_value, "\n");


print("--------\n");

bool_value = 1 and 2 and 0;
print("1 and 2 and 0 is ", bool_value, "\n");

bool_value = 1 and 2 or 0;
print("1 and 2 or 0 is ", bool_value, "\n");

bool_value = 0 or 1 and 1;
print("0 or 1 and 1 is ", bool_value, "\n");

// TODO: update test case

print("--------\n");


bool_value = 1>2 and 2>3;
print("1>2 and 2>3 is ", bool_value, "\n");

bool_value = 1>2 or 2>3;
print("1>2 or 2>3 is ", bool_value, "\n");


bool_value = 1<2 and 2>3;
print("1<2 and 2>3 is ", bool_value, "\n");

bool_value = 1<2 or 2>3;
print("1<2 or 2>3 is ", bool_value, "\n");


bool_value = 1<2 and 2<3;
print("1<2 and 2<3 is ", bool_value, "\n");

bool_value = 1<2 or 2<3;
print("1<2 or 2<3 is ", bool_value, "\n");


bool_value = 1>2 and 2<3;
print("1>2 and 2<3 is ", bool_value, "\n");

bool_value = 1>2 or 2<3;
print("1>2 or 2<3 is ", bool_value, "\n");



