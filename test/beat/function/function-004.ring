var int int_value1;
var int int_value2;
var int int_value3;
var int int_value4;
var int int_value5;

int_value1 = 0;
int_value2 = 0;
int_value3 = 0;
int_value4 = 0;
int_value5 = 0;



function doit()->(int, int, int, int, int) {
    print("I'm function doit\n");
	return 1, 2, 3, 4, 5;
}

int_value1, int_value2, int_value3, int_value4, int_value5 = doit();
print("int_value1=", int_value1, "\n");
print("int_value2=", int_value2, "\n");
print("int_value3=", int_value3, "\n");
print("int_value4=", int_value4, "\n");
print("int_value5=", int_value5, "\n");
print("\n");
