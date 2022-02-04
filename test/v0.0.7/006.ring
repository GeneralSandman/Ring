
var int num;
num = 1;
print(num);
print("\n");


function useGlobalVariable() {
    num = 2;
    print(num);
    print("\n");
}
useGlobalVariable();
print(num);
print("\n");


function useLocalVariable() {
    var int num;
    num = 3;
    print(num);
    print("\n");
}
useLocalVariable();
print(num);
print("\n");
