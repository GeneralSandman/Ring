
var int int_value;
var double double_value;


int_value = 2 + int(1.1);
print(int_value, "\n");

double_value = 1.1;
int_value = 2 + int(double_value);
print(int_value, "\n");

// FIXME: bug line:10
// 强制类型转换后和别的类型相互组合