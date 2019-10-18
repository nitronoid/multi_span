///////////////////////////////////////////////////////////////////////////////
//
// Maintained by Jack Diver.
//
// Copyright (c) 2019 Jack Diver
//
// Modified from :-
//
// github.com/microsoft/GSL
//
// Copyright (c) 2015 Microsoft Corporation. All rights reserved.
//
//
// This code is licensed under the MIT License (MIT).
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
///////////////////////////////////////////////////////////////////////////////

#ifdef _MSC_VER
// blanket turn off warnings from CppCoreCheck from catch
// so people aren't annoyed by them when running the tool.
#pragma warning(disable : 26440 26426) // from catch
#endif

#include <catch2/catch.hpp>
// for multi_span, contiguous_span_iterator, dim
#include <stdex/multi_span>

#include <cstddef> // for ptrdiff_t, size_t

using namespace std;
using namespace stdex;

namespace
{
void use(std::ptrdiff_t&) {}
} // namespace

TEST_CASE("basic_bounds")
{
  for (auto point : static_bounds<dynamic_range, 3, 4>{2})
  {
    for (decltype(point)::size_type j = 0;
         j < static_cast<decltype(point)::size_type>(decltype(point)::rank);
         j++)
    {
      use(j);
      use(point[static_cast<std::size_t>(j)]);
    }
  }
}

TEST_CASE("bounds_basic")
{
  static_bounds<3, 4, 5> b;
  auto z = std::begin(b);
  z += 2;
  const auto a = b.slice();
  (void)a;
  static_bounds<4, dynamic_range, 2> x{4};
  x.slice().slice();
}

TEST_CASE("bounds_iterator")
{
  static_bounds<2, 3> v;
  using iterator = decltype(v)::iterator;
  using value_type = iterator::value_type;

  // Pre-increment
  {
    auto a = std::begin(v);
    for (int i = 0; i < v.extent<0>(); ++i)
      for (int j = 0; j < v.extent<1>(); ++j)
      {
        CHECK(*a == value_type{i, j});
        ++a;
      }
  }
  {
    auto a = std::begin(v);
    for (int i = 0; i < v.size() - 1; ++i)
    {
      auto r = i / v.extent<1>();
      auto c = i % v.extent<1>();
      CHECK((++a) == (std::begin(v) + r * 3 + c + 1));
    }
  }
  // Post-increment
  {
    auto a = std::begin(v);
    for (int i = 0; i < v.extent<0>(); ++i)
      for (int j = 0; j < v.extent<1>(); ++j)
      {
        CHECK(*(a++) == value_type{i, j});
      }
  }
  {
    auto a = std::begin(v);
    for (int i = 0; i < v.extent<0>(); ++i)
      for (int j = 0; j < v.extent<1>(); ++j)
      {
        CHECK((a++) == (std::begin(v) + i * 3 + j));
      }
  }
  // Pre-decrement
  {
    auto a = std::end(v);
    for (int i = v.extent<0>() - 1; i >= 0; --i)
      for (int j = v.extent<1>() - 1; j >= 0; --j)
      {
        CHECK(*(--a) == value_type{i, j});
      }
  }
  {
    auto a = std::end(v);
    for (int i = v.extent<0>() - 1; i >= 0; --i)
      for (int j = v.extent<1>() - 1; j >= 0; --j)
      {
        CHECK((--a) == (std::begin(v) + i * 3 + j));
      }
  }
  // Post-decrement
  {
    auto a = std::end(v) - 1;
    for (int i = v.size() - 1; i > 0; --i)
    {
      auto r = i / v.extent<1>();
      auto c = i % v.extent<1>();
      CHECK(*(a--) == value_type{r, c});
    }
  }
  {
    auto a = std::end(v) - 1;
    for (int i = v.size() - 1; i > 0; --i)
    {
      auto r = i / v.extent<1>();
      auto c = i % v.extent<1>();
      CHECK((a--) == (std::begin(v) + r * 3 + c));
    }
  }
}

TEST_CASE("arrayview_iterator")
{
  static_bounds<4, dynamic_range, 2> bounds{3};

  const auto itr = bounds.begin();
  (void)itr;
#ifdef CONFIRM_COMPILATION_ERRORS
  multi_span<int, 4, dynamic_range, 2> av(nullptr, bounds);

  auto itr2 = av.cbegin();

  for (auto& v : av)
  {
    v = 4;
  }
  fill(av.begin(), av.end(), 0);
#endif
}

TEST_CASE("bounds_convertible")
{
  static_bounds<7, 4, 2> b1;
  static_bounds<7, dynamic_range, 2> b2 = b1;
  (void)b2;
#ifdef CONFIRM_COMPILATION_ERRORS
  static_bounds<7, dynamic_range, 1> b4 = b2;
#endif

  static_bounds<dynamic_range, dynamic_range, dynamic_range> b3 = b1;
  static_bounds<7, 4, 2> b4 = b3;
  (void)b4;

  static_bounds<dynamic_range> b11;

  static_bounds<dynamic_range> b5;
  static_bounds<34> b6;

  b5 = static_bounds<20>();
  CHECK_THROWS_AS(b6 = b5, std::logic_error);
  b5 = static_bounds<34>();
  b6 = b5;

  CHECK(b5 == b6);
  CHECK(b5.size() == b6.size());
}

#ifdef CONFIRM_COMPILATION_ERRORS
copy(src_span_static, dst_span_static);
#endif
