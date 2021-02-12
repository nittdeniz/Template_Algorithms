# Template_Algorithms
A header only library for template algorithms with std::size_t... parameter packs.

## Minimal Working Example

```C++
#define $CLASSNAME Base /* mandatory definition _before_ you include the library, must match your class name */
#include "template_algorithms.hpp"

template<std::size_t... n>
struct Base
{
  using type = Base<n...>; /* mandatory addition to your class */
};
```

## Dummy Classes
There are three dummy classes, which will serve als rage indicator for several other functions. `Pos<n>` indicates the element at the 0-indexed position `n`, i.e. `Pos<3>` denotes ot the fourth element in the parameter pack. `First<n>` Is a range from the first element to to element at `n`-th position (including). Likewise, `Last<n>` is a range from the last but `n`-th element to the last element (again including).


## Examples of Supported Functions

### Concatenation

```C++
using namespace Template_Algorithms;
concat<Base<1,2,3>, Base<4,5,6>> T; // T is of type Base<1,2,3,4,5,6>
```

### Extraction

```C++
using namespace Template_Algorithms;
get<First<3>, Base<1,2,3,4,5,6>> T; // T is of type Base<1,2,3>
get<Last<3>, Base<1,2,3,4,5,6>> U; // U is of type Base<4,5,6>
get<Pos<3> Base<1,2,3,4,5,6>> V; // V is of type Base<4>
```


### Removal

```C++
using namespace Template_Algorithms;
del<First<3>, Base<1,2,3,4,5,6>> T; // T is of type Base<4,5,6>
del<Last<3>, Base<1,2,3,4,5,6>> U; // U is of type Base<1,2,3>
del<Pos<3> Base<1,2,3,4,5,6>> V; // V is of type Base<1,2,3,5,6>
```

### Slicing (including)

```C++
using namespace Template_Algorithms;
islice<Pos<1>, Pos<4>, Base<1,2,3,4,5,6>> T; // T is of type Base<2,3,4,5>
```

### Slicing (excluding)

```C++
using namespace Template_Algorithms;
xslice<Pos<1>, Pos<4>, Base<1,2,3,4,5,6>> T; // T is of type Base<3,4>
```

### Swapping 

```C++
using namespace Template_Algorithms;
swap<Pos<1>, Pos<4>, Base<1,2,3,4,5,6>> T; // T is of type Base<1,5,3,4,2,6>
```
