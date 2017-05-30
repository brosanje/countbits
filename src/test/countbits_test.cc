#include "feastoffoo/countbits.h"

#include <gtest/gtest.h>
#include <cstdio>
#include <cstdlib>
#include <random>
#include <functional>
#include <vector>

#define NTRIALS 1000000

namespace {
  struct test8_s {
      unsigned int expected_result;
      unsigned char number;
  };

  struct test16_s {
      unsigned int expected_result;
      unsigned short number;
  };

  struct test32_s {
      unsigned int expected_result;
      unsigned int number;
  };

  struct test64_s {
      unsigned int expected_result;
      unsigned long long number;
  };

  static test8_s tests8[] = {
      { 1, 1 }
    , { 1, 2 }
    , { 2, 3 }
    , { 2, 0x48 }
    , { 4, 0x1d }
    , { 7, 0xef }
    , { 8, 0xff }
  };

  static test32_s tests[] = {
      { 1,  1 }
    , { 1,  2 }
    , { 2,  3 }
    , { 4,  0x489 }
    , { 11, 0x72a401d }
    , { 32, 0xffffffff }
    , { 10, 0x849ea001 }
  };

  static std::vector<test8_s>  tests8_v(NTRIALS);
  static std::vector<test16_s> tests16_v(NTRIALS);
  static std::vector<test32_s> tests32_v(NTRIALS);
  static std::vector<test64_s> tests64_v(NTRIALS);

  // unit test for known result
  TEST(CountBits, Reference) {
    using namespace feastoffoo::countbits::reference;

    for (auto test : tests)
      EXPECT_EQ(test.expected_result, countbits(test.number));
  }

  // how long does this take?
  TEST(CountBits, ReferenceTimings) {
    using namespace feastoffoo::countbits::reference;

    for (auto test : tests32_v)
      EXPECT_EQ(test.expected_result, countbits(test.number));
  }

  ///////////////////////////////////////////////////////
  // Improvement #1
 
  // unit test for known result
  TEST(CountBits, Improvement1) {
    using namespace feastoffoo::countbits::improvement1;

    for (auto test : tests)
      EXPECT_EQ(test.expected_result, countbits(test.number));
  }

  // test against reference, and timings
  TEST(CountBits, Improvement1VsReference32) {
    using namespace feastoffoo::countbits::improvement1;

    for (auto test : tests32_v)
      EXPECT_EQ(test.expected_result, countbits(test.number));
  }

  // 64 bit test against reference, and timings
  TEST(CountBits, Improvement1VsReference64) {
    using namespace feastoffoo::countbits::improvement1;

    for (auto test : tests64_v)
      EXPECT_EQ(test.expected_result, countbits64(test.number));
  }

  ///////////////////////////////////////////////////////
  // Improvement #2

  // unit test for known result
  TEST(CountBits, Improvement2) {
    using namespace feastoffoo::countbits::improvement2;

    for (auto test : tests)
      EXPECT_EQ(test.expected_result, countbits(test.number));
  }

  // test against reference, and timings
  TEST(CountBits, Improvement2VsReference32) {
    using namespace feastoffoo::countbits::improvement2;

    for (auto test : tests32_v)
      EXPECT_EQ(test.expected_result, countbits(test.number));
  }

  // 64 bit test against reference, and timings
  TEST(CountBits, Improvement2VsReference64) {
    using namespace feastoffoo::countbits::improvement2;

    for (auto test : tests64_v)
      EXPECT_EQ(test.expected_result, countbits64(test.number));
  }

  ///////////////////////////////////////////////////////
  // Improvement #3

  // unit test for known result
  TEST(CountBits, Improvement3) {
    using namespace feastoffoo::countbits::improvement3;

    for (auto test : tests)
      EXPECT_EQ(test.expected_result, countbits(test.number));
  }

  // 8 bit test against reference, and timings
  TEST(CountBits, Improvement3VsReference8) {
    using namespace feastoffoo::countbits::improvement3;

    for (auto test : tests8_v)
      EXPECT_EQ(test.expected_result, countbits(test.number));
  }

  // 16 bit test against reference, and timings
  TEST(CountBits, Improvement3VsReference16) {
    using namespace feastoffoo::countbits::improvement3;

    for (auto test : tests16_v)
      EXPECT_EQ(test.expected_result, countbits(test.number));
  }

  // test against reference, and timings
  TEST(CountBits, Improvement3VsReference32) {
    using namespace feastoffoo::countbits::improvement3;

    for (auto test : tests32_v)
      EXPECT_EQ(test.expected_result, countbits(test.number));
  }

  // 64 bit test against reference, and timings
  TEST(CountBits, Improvement3VsReference64) {
    using namespace feastoffoo::countbits::improvement3;

    for (auto test : tests64_v)
      EXPECT_EQ(test.expected_result, countbits(test.number));
  }

  ///////////////////////////////////////////////////////
  // Improvement #4

  // unit test for known result
  TEST(CountBits, Improvement4) {
    using namespace feastoffoo::countbits::improvement4;

    for (auto test : tests)
      EXPECT_EQ(test.expected_result, countbits(test.number));

    EXPECT_EQ(255, _countbits_4_finale);

    for (auto test : tests8)
      EXPECT_EQ(test.expected_result, countbits(test.number));
      
    EXPECT_EQ(15, _countbits_4_finale);
  }

  // 8 bit test against reference, and timings
  TEST(CountBits, Improvement4VsReference8) {
    using namespace feastoffoo::countbits::improvement4;

    for (auto test : tests8_v)
      EXPECT_EQ(test.expected_result, countbits(test.number));
  }

  // 16 bit test against reference, and timings
  TEST(CountBits, Improvement4VsReference16) {
    using namespace feastoffoo::countbits::improvement4;

    for (auto test : tests16_v)
      EXPECT_EQ(test.expected_result, countbits(test.number));
  }

  // 32 bit test against reference, and timings
  TEST(CountBits, Improvement4VsReference32) {
    using namespace feastoffoo::countbits::improvement4;

    for (auto test : tests32_v)
      EXPECT_EQ(test.expected_result, countbits(test.number));
  }

  // 64 bit test against reference, and timings
  TEST(CountBits, Improvement4VsReference64) {
    using namespace feastoffoo::countbits::improvement4;

    for (auto test : tests64_v)
      EXPECT_EQ(test.expected_result, countbits(test.number));
  }
}

///////////////////////////////////////////////////////

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  using namespace feastoffoo::countbits::reference;

  std::default_random_engine generator;
  std::uniform_int_distribution<int> distribution(0, RAND_MAX);
  auto dice = std::bind(distribution, generator);

  for (int ii = 0; ii < NTRIALS; ii++) {
    test8_s test8;
    test16_s test16;
    test32_s test32;
    test64_s test64;

    test32.number = dice();
    test32.expected_result = countbits(test32.number);
    tests32_v.push_back(test32);

    test8.number = test32.number & 0xff;
    test8.expected_result = countbits(test8.number);
    tests8_v.push_back(test8);

    test16.number = test32.number & 0xffff;
    test16.expected_result = countbits(test16.number);
    tests16_v.push_back(test16);

    test64.number = dice() * test32.number;
    test64.expected_result = countbits(test64.number);
    tests64_v.push_back(test64);
  }

  return RUN_ALL_TESTS();
}
