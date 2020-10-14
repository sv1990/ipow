# A fairly fast integral power function

## Introduction and Usage

When passing an integral exponent to [`std::pow`](https://en.cppreference.com/w/cpp/numeric/math/pow) it will cast the exponent to a floating point type and proceed with the same algorithm as for floating point exponents. In principle it should be possible to calculate the power by only doing some multiplications. However, none of the exisitng ipow implementations on the internet seemed to achieve that.

### Variable Exponent

For variable exponents the usage is analogous to `std::pow`

```c++
double x = ...;
int n = ...;
auto res = ipow::ipow(x, n);
```

This function performs simply [Exponentiation by squaring](https://en.wikipedia.org/wiki/Exponentiation_by_squaring). The only *trick* that this implementation does is that it avoid having branches inside the main loop by using a technique from this [paper](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2020/p2187r3.pdf). The idea is to replace a `if` statement like the following

```c++
double x = ...;
double y = ...;
if (b) {
  x *= y;
}
```

by an array acces

```c++
double arr[] = {1, y};
x *= arr[b];
```
to eliminate a branch.
### Fixed Exponent

When the exponent is known at compile a time different variant can be used

```c++
double x = ...;
constexpr int n = ...;
auto res = ipow::ipow<n>(n);
```

## Benchmarks

The benchmarks were performed with gcc 10.2.0 and clang 10.0.1. Only the version with variable exponent was benchmarked. `std::pow` uses constant time except when raising to the zeroth power. `ipow::ipow` shows logarithmic time increase but is much faster than `std::pow`.

![gcc](https://raw.githubusercontent.com/sv1990/ipow/main/extras/gcc.png)

![clang](https://raw.githubusercontent.com/sv1990/ipow/main/extras/clang.png)

