
var int num;
num = 0;

print(num);
print("\n");

num = num + 1;

print(num);
print("\n");


function userFunc() {
    num = num + 1;
    print("userFunc:");
    print(num);
    print("\n");
}

userFunc();