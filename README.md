# `multi_span`: A multi-dimensional view over contiguous data.

[![Standardisation](https://img.shields.io/badge/C%2B%2B-14-BLUE)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization)
[![License](https://img.shields.io/badge/license-MIT-BLUE)](https://opensource.org/licenses/MIT)
[![Build status](https://travis-ci.com/nitronoid/multi_span.svg?branch=master)](https://travis-ci.com/nitronoid/multi_span)

`multi_span` is a single-file header-only library for multi-dimensional views over arrays of contiguous data.
This repository was created to host and maintain the implementation of `multi_span` provided in the Microsoft GSL, which has been deprecated.
The ISO-C++ proposal P0009 will add support for non-owning multi-dimensional array references to the C++ standard library. 
This repository does not conform to the proposal, but implements many useful extensions.


## Using `multi_span`
```cpp
#include <stdex/multi_span>
#include <vector>
#include <iostream>
#include <string>
#include <numeric>


int main()
{
  using namespace std;
  /*
   * Print a vector as a 2D matrix
   */

  // Define a vector
  vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

  // Create a 2D-view over the vector
  stdex::multi_span<int, 3, 4> my_view(arr);

  // Print all elements of the vector, via the view
  printf("2D view:\n");
  for (int r = 0; r < my_view.extent<0>(); ++r)
  {
    for (int c = 0; c < my_view.extent<1>(); ++c)
    {
      printf("%d ", my_view(r, c));
    }
    printf("\n");
  }
  printf("\n");


  /*
   * Sum the elements within a sliding 2D sub-view
   */

  // Define the size of the sub-view
  auto const wsize = 2;
  // Obtain the bounds of our 2D-view
  auto const range = my_view.bounds();

  // Use static_bounds as counting iterators
  using counting_iter = stdex::static_bounds<stdex::dynamic_range, stdex::dynamic_range>;
  // Create a lazy 2D iterable sequence
  counting_iter bnds({range[0] - wsize + 1, range[1] - wsize + 1});

  // Iterate through the sequence, obtaining a 2D-coordinate
  for_each(begin(bnds), end(bnds), [&](auto idx) {
    // Obtain a sub-view of our main view
    auto const section = my_view.section(idx, {wsize, wsize});
    // Print all elements in the sub-view
    copy(begin(section), end(section), ostream_iterator<int>(cout, " "));
    // Iterate over the sub-view and sum the elements within
    auto const total = accumulate(begin(section), end(section), 0);
    // Print the total
    printf(": sums to %d.\n", total);
  });
  printf("\n");

  return 0;
}
```

The output of running this example is:
```
2D view:
1 2 3 4
5 6 7 8
9 10 11 12

1 2 5 6 : sums to 14.
2 3 6 7 : sums to 18.
3 4 7 8 : sums to 22.
5 6 9 10 : sums to 30.
6 7 10 11 : sums to 34.
7 8 11 12 : sums to 38.
```

## Testing `multi_span`
This repository contains multiple tests from the original Microsoft repository.
The primary build system is now `bazel`.

To run all tests:
```
bazel test //...
```

To run specific tests:
```
bazel test //test:multi_span_tests
```


