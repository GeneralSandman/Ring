
```
#include <stdio.h>

int main() {
  double a = 10.1;
  int b = 2;
  int int_value = a % b;
  printf("%d\n", int_value);
  return 0;
}
```

test.c:6:21: error: invalid operands to binary expression ('double' and 'double')
  int int_value = a % b;
                  ~ ^ ~
1 error generated.

