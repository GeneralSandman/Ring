var int num1;
num1 = 1;

var int num2;
num2 = 2;

function funcWithParamlist3(var int a, var int b) {
    print(a);
    print("\n");
    print(b);
    print("\n");
}

funcWithParamlist3(num1, num2);
print("\n");

funcWithParamlist3(num2, num1);
print("\n");

funcWithParamlist3(num1, num2);
print("\n");


funcWithParamlist3(123, 456);
print("\n");
funcWithParamlist3(456, 123);
print("\n");


funcWithParamlist3(123*124, 456*457);
print("\n");
funcWithParamlist3(456-176, 123+999);
print("\n");