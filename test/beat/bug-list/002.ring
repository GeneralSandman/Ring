
var int int_value;

int_value = 1;

function testRecursion() {
    print("testRecursion ", int_value, "\n");
    int_value = int_value + 1;
    testRecursion();
}

testRecursion();

// FIXME: 递归有问题，内存溢出