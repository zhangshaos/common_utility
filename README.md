# common_utility

## Disjoint Set

`class id` need to be increasing, and starting at 0.

## Better Assert

https://github.com/zhangshaos/better_assert

## 1D/2D Mean-Shift Clustering

modified mean-shift clustering algorithm moving original points when shifting.

> depends on Eigen3.

## 2D PCA

> depends on Eigen3.

## Auto Check Float Error (nan, inf)

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

