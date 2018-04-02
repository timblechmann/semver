// semver c++11 test
//
// Licensed under the MIT License <http://opensource.org/licenses/MIT>.
// Copyright (c) 2018 Daniil Goncharov <neargye@gmail.com>.
//
// Permission is hereby  granted, free of charge, to any  person obtaining a copy
// of this software and associated  documentation files (the "Software"), to deal
// in the Software  without restriction, including without  limitation the rights
// to  use, copy,  modify, merge,  publish, distribute,  sublicense, and/or  sell
// copies  of  the Software,  and  to  permit persons  to  whom  the Software  is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE  IS PROVIDED "AS  IS", WITHOUT WARRANTY  OF ANY KIND,  EXPRESS OR
// IMPLIED,  INCLUDING BUT  NOT  LIMITED TO  THE  WARRANTIES OF  MERCHANTABILITY,
// FITNESS FOR  A PARTICULAR PURPOSE AND  NONINFRINGEMENT. IN NO EVENT  SHALL THE
// AUTHORS  OR COPYRIGHT  HOLDERS  BE  LIABLE FOR  ANY  CLAIM,  DAMAGES OR  OTHER
// LIABILITY, WHETHER IN AN ACTION OF  CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE  OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <semver.hpp>
#include <cstring>
#include <string>
#include <sstream>

using namespace semver;

TEST_CASE("constructors") {
  SECTION("default") {
    constexpr Version v;
    static_assert(v.major == 0 &&
                  v.minor == 1 &&
                  v.patch == 0 &&
                  v.pre_release_type == Version::PreReleaseType::kNone &&
                  v.pre_release_version == 0, "");

    REQUIRE((v.major == 0 &&
             v.minor == 1 &&
             v.patch == 0 &&
             v.pre_release_type == Version::PreReleaseType::kNone &&
             v.pre_release_version == 0));
  }
  SECTION("constructor") {
    constexpr Version v(1, 2, 3, Version::PreReleaseType::kReleaseCandidate, 4);
    static_assert(v.major == 1 &&
                  v.minor == 2 &&
                  v.patch == 3 &&
                  v.pre_release_type == Version::PreReleaseType::kReleaseCandidate &&
                  v.pre_release_version == 4, "");

    REQUIRE((v.major == 1 &&
             v.minor == 2 &&
             v.patch == 3 &&
             v.pre_release_type == Version::PreReleaseType::kReleaseCandidate &&
             v.pre_release_version == 4));
  }
}

TEST_CASE("operators") {
  SECTION("operator ==") {
    constexpr Version v1(1, 2, 3, Version::PreReleaseType::kReleaseCandidate, 4);
    constexpr Version v2(1, 2, 3, Version::PreReleaseType::kReleaseCandidate, 4);

    static_assert(v1 == v2, "");
    REQUIRE(v1 == v2);
  }
  SECTION("operator !=") {
    constexpr Version v1(1, 0, 0, Version::PreReleaseType::kAlpha, 0);
    constexpr Version v2(1, 1, 0, Version::PreReleaseType::kAlpha, 0);
    constexpr Version v3(1, 0, 1, Version::PreReleaseType::kAlpha, 0);
    constexpr Version v4(1, 0, 0, Version::PreReleaseType::kAlpha, 1);
    constexpr Version v5(1, 0, 0, Version::PreReleaseType::kNone, 0);
    constexpr Version v6(2, 0, 0, Version::PreReleaseType::kNone, 0);

    static_assert(v1 != v2, "");
    REQUIRE(v1 != v2);
    static_assert(v1 != v3, "");
    REQUIRE(v1 != v3);
    static_assert(v1 != v4, "");
    REQUIRE(v1 != v4);
    static_assert(v1 != v5, "");
    REQUIRE(v1 != v5);
    static_assert(v1 != v6, "");
    REQUIRE(v1 != v6);
  }

  SECTION("operator >") {
    constexpr Version v1(1, 0, 0, Version::PreReleaseType::kAlpha, 0);
    constexpr Version v2(1, 1, 0, Version::PreReleaseType::kAlpha, 0);
    constexpr Version v3(1, 0, 1, Version::PreReleaseType::kAlpha, 0);
    constexpr Version v4(1, 0, 0, Version::PreReleaseType::kAlpha, 1);
    constexpr Version v5(1, 0, 0, Version::PreReleaseType::kNone, 0);
    constexpr Version v6(2, 0, 0, Version::PreReleaseType::kNone, 0);

    static_assert(v2 > v1, "");
    REQUIRE(v2 > v1);
    static_assert(v3 > v1, "");
    REQUIRE(v3 > v1);
    static_assert(v4 > v1, "");
    REQUIRE(v4 > v1);
    static_assert(v5 > v1, "");
    REQUIRE(v5 > v1);
    static_assert(v6 > v1, "");
    REQUIRE(v6 > v1);
  }

  SECTION("operator >=") {
    constexpr Version v1(1, 0, 0, Version::PreReleaseType::kNone, 0);
    constexpr Version v2(1, 0, 0, Version::PreReleaseType::kNone, 0);
    constexpr Version v3(2, 0, 0, Version::PreReleaseType::kNone, 0);

    static_assert(v2 >= v1, "");
    REQUIRE(v2 >= v1);
    static_assert(v3 >= v1, "");
    REQUIRE(v3 >= v1);
  }

  SECTION("operator <") {
    constexpr Version v1(1, 0, 0, Version::PreReleaseType::kAlpha, 0);
    constexpr Version v2(1, 1, 0, Version::PreReleaseType::kAlpha, 0);
    constexpr Version v3(1, 0, 1, Version::PreReleaseType::kAlpha, 0);
    constexpr Version v4(1, 0, 0, Version::PreReleaseType::kAlpha, 1);
    constexpr Version v5(1, 0, 0, Version::PreReleaseType::kNone, 0);
    constexpr Version v6(2, 0, 0, Version::PreReleaseType::kNone, 0);

    static_assert(v1 < v2, "");
    REQUIRE(v1 < v2);
    static_assert(v1 < v3, "");
    REQUIRE(v1 < v3);
    static_assert(v1 < v4, "");
    REQUIRE(v1 < v4);
    static_assert(v1 < v5, "");
    REQUIRE(v1 < v5);
    static_assert(v1 < v6, "");
    REQUIRE(v1 < v6);
  }

  SECTION("operator <=") {
    constexpr Version v1(1, 0, 0, Version::PreReleaseType::kNone, 0);
    constexpr Version v2(1, 0, 0, Version::PreReleaseType::kNone, 0);
    constexpr Version v3(2, 0, 0, Version::PreReleaseType::kNone, 0);

    static_assert(v1 <= v2, "");
    REQUIRE(v1 <= v2);
    static_assert(v1 <= v3, "");
    REQUIRE(v1 <= v3);
  }

  SECTION("operator <<") {
    constexpr Version v(1, 2, 3, Version::PreReleaseType::kReleaseCandidate, 4);

    std::stringstream os;
    os << v;
    REQUIRE(std::strcmp(os.str().c_str(), "1.2.3-rc.4") == 0);
  }

  SECTION("operator >>") {
    constexpr Version v(1, 2, 3, Version::PreReleaseType::kReleaseCandidate, 4);
    std::stringstream is("1.2.3-rc.4");

    Version vi;
    is >> vi;
    REQUIRE(v == vi);
  }
}

TEST_CASE("ToString")
{
  SECTION("std::string")
  {
    Version v(1, 2, 3, Version::PreReleaseType::kReleaseCandidate, 4);

    std::string s = v.ToString();
    REQUIRE(std::strcmp(s.c_str(), "1.2.3-rc.4") == 0);
  }

  SECTION("char*")
  {
    Version v(1, 2, 3, Version::PreReleaseType::kReleaseCandidate, 4);

    char s1[kVersionStringLength];
    v.ToString(s1);
    REQUIRE(std::strcmp(s1, "1.2.3-rc.4") == 0);

    char s2[11];
    v.ToString(s2);
    REQUIRE(std::strcmp(s2, "1.2.3-rc.4") == 0);
  }
}

TEST_CASE("FromString") {
  constexpr Version v(1, 2, 3, Version::PreReleaseType::kReleaseCandidate, 4);

  SECTION("std::string")
  {
    const std::string s("1.2.3-rc.4");

    Version v1(s);
    REQUIRE(v == v1);

    Version v2;
    v2.FromString(s);
    REQUIRE(v == v2);

    Version v3;
    FromString(&v3, s);
    REQUIRE(v == v3);
  }

  SECTION("char*")
  {
    const char s[] = "1.2.3-rc.4";

    Version v1(s);
    REQUIRE(v == v1);

    Version v2;
    v2.FromString(s);
    REQUIRE(v == v2);

    Version v3;
    FromString(&v3, s);
    REQUIRE(v == v3);
  }
}
