# common_utility

all codes are saving in the repository https://github.com/zhangshaos/Explorer
 (private now !)

## disjoint set

`class id` need to be increasing, and starting at 0.

## better assert

modified from https://github.com/amallia/better_assert

## 1D/2D mean-shift clustering

modified mean-shift clustering algorithm moving original points when shifting.

## 2D pca

## auto check float error (nan, inf)

replace built-in types like float and double to Float detecting nan and inf.

### Usage

- In CMakeLists.txt:

```cmake
set(ENABLE_CHECK_FLOAT_ERROR OFF) #打开此项检查浮点数错误
if(NOT ${ENABLE_CHECK_FLOAT_ERROR})
    target_compile_definitions(tgt
            PRIVATE
            N_SELF_CHECK_FLOAT)
endif()
```

- In .cpp:

```cpp
#include "self_check_float.h"

int main(){
 double a = -1, b = 0;
 double res = ((F64) a / (F64) b);
 res = sqrt((F64) a);
 return 0;
}
```

