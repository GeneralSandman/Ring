var int x;
var int y;
var int z;

var int num;

num = 0;

for(x=0; x<3; x=x+1) {
	for(y=0; y<3; y=y+1) {
		for(z=0; z<3; z=z+1) {
			print("x=",x, ",y=",y, ",z=", z, "\n");
			num = num + 1;
		}
	}
}

print("num=", num, "\n");



num = 0;

for(x=0; x<11; x=x+1) {
	for(y=0; y<120; y=y+1) {
		for(z=0; z<13; z=z+1) {
			num = num + 1;
		}
	}
}

print("num=", num, "\n");