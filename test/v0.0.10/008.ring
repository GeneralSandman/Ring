
var int num;
num = 12345;

function funcWithParamlist1(var int a) {
    print(a);
    print("\n");
}
funcWithParamlist1(num);

num = 123;


function funcWithParamlist2(var int a) {
    print(a);
    print("\n");
}
funcWithParamlist2(num);
funcWithParamlist1(num);



function funcWithParamlist3(var int a, var int b) {
    print(a);
    print("\n");
    print(b);
    print("\n");
}
funcWithParamlist3(num,num);
