var a




; 实现 a = 1 + 2
push 1
push 2
add
pop a

push a
println a=%d



; 实现 a = 1 - 2
push 1
push 2
sub
pop a

push a
println a=%d



; 实现 a = 2 * 2
push 2
push 2
mul
pop a

push a
println a=%d





; 实现 a = 2 / 2
push 2
push 2
div
pop a

push a
println a=%d



; 实现 a = 2+3*4/2-6
push 2
push 3
push 4
mul
push 2
div
add
push 6
sub
pop a

push a
println a=%d



; 实现 (1+2)*3+7-5*6-2*2+1*2*3*4*5
push 1
push 2
add
push 3
mul
push 7
add
push 5
push 6
mul
sub
push 2
push 2
mul
sub
push 1
push 2
mul
push 3
mul
push 4
mul
push 5
mul
add
pop a

push a
println a=%d
