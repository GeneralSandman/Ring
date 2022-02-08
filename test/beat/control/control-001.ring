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
