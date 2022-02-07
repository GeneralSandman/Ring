

function funcWithParamlistReturnlist1() (int) {
    return 1;
}

function funcWithParamlistReturnlist2(var int a) (int) {
    return 2;
}

function funcWithParamlistReturnlist3(var int a) (int) {
    return a;
}

function funcWithParamlistReturnlist4(var int a, var int b) (int) {
    return 2*2;
}

function funcWithParamlistReturnlist5(var int a, var int b) (int) {
    return 1+1+1+1+1;
}

function funcWithParamlistReturnlist6(var int a, var int b) (int) {
    return a + b;
}
 
var int result;

result = funcWithParamlistReturnlist1();
print(result);
print("\n");


result = funcWithParamlistReturnlist2(1);
print(result);
print("\n");

result = funcWithParamlistReturnlist3(3);
print(result);
print("\n");

result = funcWithParamlistReturnlist4(1, 2);
print(result);
print("\n");

result = funcWithParamlistReturnlist5(2, 3);
print(result);
print("\n");

result = funcWithParamlistReturnlist6(3, 3);
print(result);
print("\n");