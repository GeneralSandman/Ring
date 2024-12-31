# ```Ring``` 控制语句 defer

## for条件控制语句的语法：


```ring

var int int_value;

for(int_value=1; int_value<5; int_value=int_value+1) {
    defer print("int_value=", int_value, "\n");
}

```



```ring

defer fn() {
    print("---\n");
}();

```