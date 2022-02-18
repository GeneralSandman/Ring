
var int int_value1;
var int int_value2;

int_value1 = 0;
int_value2 = 10;

do{
	print("int_value1=", int_value1, ", int_value2=", int_value2, "\n");
	int_value1 = int_value1+1;
	int_value2 = int_value2-1;
}while(false);


print("\n\n");
int_value1 = 0;
int_value2 = 10;

do{
	print("int_value1=", int_value1, ", int_value2=", int_value2, "\n");
	int_value1 = int_value1+1;
	int_value2 = int_value2-1;
}while(int_value1<10);