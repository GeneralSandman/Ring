var int int_value = 0;

function add_one(var int a) -> (int) {
	a++;
	return a;
}

function add_two(var int a) -> (int) {
	a+=2;
	return a;
}

int_value = add_one(add_one(add_one(add_one(add_one(add_one(int_value))))));
print("int_value=", int_value, "\n");

int_value = add_two(add_two(add_two(add_two(add_two(add_two(int_value))))));
print("int_value=", int_value, "\n");