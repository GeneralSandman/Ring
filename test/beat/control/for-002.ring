var int int_value;

int_value = -1;

print("before for int_value=", int_value, "\n");

for(;;) {
	print("for int_value=", int_value, "\n");
	int_value = int_value + 1;

	break;
}

print("after for int_value=", int_value, "\n");


