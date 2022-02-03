
var int num;
num = 1;

print(num);
print("\n");


function useGlobalVariable() {
    num = 2;
}
useGlobalVariable();
print(num);
print("\n");


function useLocalVariable() {
    var int num;
    num = 3;
}
useLocalVariable();
print(num);
print("\n");
