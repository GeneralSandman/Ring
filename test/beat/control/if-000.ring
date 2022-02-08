//
// Created by Zhenhu Li on 2022/2/8.
//


var bool bool_value;

bool_value = true;
print("set bool_value = true\n");
if(bool_value) {
	print("bool_value is true\n");
} else {
	print("bool_value is false\n");
}

print("\n");

bool_value = false;
print("set bool_value = false\n");
if(bool_value) {
	print("bool_value is true\n");
} else {
	print("bool_value is false\n");
}


print("\n");
if(true) {
	print("check true pass\n");
} else {
	print("check true failed\n");
}

print("\n");
if(false) {
	print("check false failed\n");
} else {
	print("check false pass\n");
}


print("\n");
if(not false) {
	print("check not false pass\n");
} else {
	print("check not false failed\n");
}


print("\n");
if(not true) {
	print("check not true failed\n");
} else {
	print("check not true pass\n");
}

print("\n");
if(2>1) {
	print("check 2>1 pass\n");
} else {
	print("check 2>1 failed\n");
}


print("\n");
if(2<1) {
	print("check 2<1 failed\n");
} else {
	print("check 2<1 pass\n");
}


print("\n");
if(true or true) {
	print("check (true or true) pass\n");
} else {
	print("check (true or true) failed\n");
}

print("\n");
if(false or true) {
	print("check (false or true) pass\n");
} else {
	print("check (false or true) failed\n");
}

print("\n");
if(true or false) {
	print("check (true or false) pass\n");
} else {
	print("check (true or false) failed\n");
}

print("\n");
if(false or false) {
	print("check (false or false) failed\n");
} else {
	print("check (false or false) pass\n");
}


print("\n");
print("\n");


print("\n");
if(true and true) {
	print("check (true and true) pass\n");
} else {
	print("check (true and true) failed\n");
}


print("\n");
if(true and false) {
	print("check (true and false) failed\n");
} else {
	print("check (true and false) pass\n");
}

print("\n");
if(false and true) {
	print("check (false and true) failed\n");
} else {
	print("check (false and true) pass\n");
}

print("\n");
if(false and false) {
	print("check (false and false) failed\n");
} else {
	print("check (false and false) pass\n");
}




