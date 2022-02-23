; int a, b;
var a

; a = 2 + 3 * 4 - 3 * 4 - 2;
push 2
push 3
push 4
mul
add
push 3
push 4
mul
sub
push 2
sub
pop a


; print("a = %d, b = %d", a, b);
push a
print "a = %d"

; exit 1