var int int_value;

for(int_value=0;int_value<100;int_value=int_value+1) {
	testIf(int_value);
}


function testIf(var int int_value) {
	if(int_value < 10) {
		print("      ", int_value, " < 10\n");
	} elseif(int_value < 20) {
		print("10 <= ", int_value, " < 20\n");
	} elseif(int_value < 30) {
		print("20 <= ", int_value, " < 30\n");
	} elseif(int_value < 40) {
		print("30 <= ", int_value, " < 40\n");
	} elseif(int_value < 50) {
		print("40 <= ", int_value, " < 50\n");
	} elseif(int_value < 60) {
		print("50 <= ", int_value, " < 60\n");
	} elseif(int_value < 70) {
		print("60 <= ", int_value, " < 70\n");
	} elseif(int_value < 80) {
		print("70 <= ", int_value, " < 80\n");
	} elseif(int_value < 90) {
		print("80 <= ", int_value, " < 90\n");
	} else {
		print("90 <= ", int_value, "\n");
	}
}