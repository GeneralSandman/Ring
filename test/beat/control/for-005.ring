var int int_value;

int_value = -1;

print("before for int_value=", int_value, "\n");

for(int_value = 0;int_value < 20; int_value=int_value+1) {
	print("for int_value=", int_value, "\n");
	if(int_value > 10) {
		print("continue here\n");
		continue;
	}
	print("--end for\n");
}

print("after for int_value=", int_value, "\n");


