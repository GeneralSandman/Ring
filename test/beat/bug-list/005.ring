var int int_value = 0;

function add_one(var int a) -> (int) {
	a++;
	return a++;
}

int_value = add_one(int_value);
print("int_value=", int_value, "\n");
print("\n");

// FIXME: return a++;