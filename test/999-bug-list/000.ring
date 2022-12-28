
function doit5() (int) {
	return 5;
}

var int return_int_value;
return_int_value = doit5();
print("function:doit5 return value = ", return_int_value, "\n");
print("function:doit5 return value = ", doit5(), "\n");

// FIXME: bug line:9
// print 参数传递 函数会有问题