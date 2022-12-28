var int int_value1;
var int int_value2;
var int int_value3;

int_value1 = 0;
int_value2 = 0;
int_value3 = 0;



function doit()->(int, int) {
    print("I'm function doit\n");
	return 1, 2;
}

int_value1, int_value2 = doit();
print("int_value1=", int_value1, "\n");
print("int_value2=", int_value2, "\n");
print("int_value3=", int_value3, "\n");
print("\n");


int_value1, int_value2, int_value3 = doit(), 3;
print("int_value1=", int_value1, "\n");
print("int_value2=", int_value2, "\n");
print("int_value3=", int_value3, "\n");
print("\n");

int_value1, int_value2, int_value3 = 1, doit();
print("int_value1=", int_value1, "\n");
print("int_value2=", int_value2, "\n");
print("int_value3=", int_value3, "\n");
print("\n");

int_value1, int_value2, int_value3 = 1, doit();
print("int_value1=", int_value1, "\n");
print("int_value2=", int_value2, "\n");
print("int_value3=", int_value3, "\n");
print("\n");

// 这种情况要考虑到
// int_value1, int_value2, int_value3 = doit(), 123; // 语义分析的时候要严格检查