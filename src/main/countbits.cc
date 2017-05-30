#include "feastoffoo/countbits.h"

namespace feastoffoo {
  namespace countbits {
    namespace reference {
      unsigned int countbits(unsigned long long number) {
        unsigned int sum = 0;

        while (number) {
          sum += number & 0x01;
          number >>= 1;
        }

        return sum;
      }
    }

    namespace improvement1 {
      // instead of shuffling the bits along
      // just add them to each other
      static const unsigned int _1_BIT   = 0x55555555;
      static const unsigned int _2_BITS  = 0x33333333;
      static const unsigned int _4_BITS  = 0x0f0f0f0f;
      static const unsigned int _8_BITS  = 0x00ff00ff;
      static const unsigned int _16_BITS = 0x0000ffff;

      static const unsigned long long _1_BIT_64   = 0x5555555555555555;
      static const unsigned long long _2_BITS_64  = 0x3333333333333333;
      static const unsigned long long _4_BITS_64  = 0x0f0f0f0f0f0f0f0f;
      static const unsigned long long _8_BITS_64  = 0x00ff00ff00ff00ff;
      static const unsigned long long _16_BITS_64 = 0x0000ffff0000ffff;
      static const unsigned long long _32_BITS_64 = 0x00000000ffffffff;

      unsigned int countbits(unsigned int number) {
        unsigned int sum = number;

        sum = ((sum >> 1) & _1_BIT) + (sum & _1_BIT);
        sum = ((sum >> 2) & _2_BITS) + (sum & _2_BITS);
        sum = ((sum >> 4) & _4_BITS) + (sum & _4_BITS);
        sum = ((sum >> 8) & _8_BITS) + (sum & _8_BITS);
        sum = ((sum >> 16) & _16_BITS) + (sum & _16_BITS);

        return sum;
      }

      unsigned int countbits64(unsigned long long number) {
        unsigned long long sum = number;

        sum = ((sum >> 1) & _1_BIT_64) + (sum & _1_BIT_64);
        sum = ((sum >> 2) & _2_BITS_64) + (sum & _2_BITS_64);
        sum = ((sum >> 4) & _4_BITS_64) + (sum & _4_BITS_64);
        sum = ((sum >> 8) & _8_BITS_64) + (sum & _8_BITS_64);
        sum = ((sum >> 16) & _16_BITS_64) + (sum & _16_BITS_64);
        sum = ((sum >> 32) & _32_BITS_64) + (sum & _32_BITS_64);

        return sum;
      }
    }

    namespace improvement2 {
      // instead of shuffling the bits along
      // just add them to each other
      // go until we have 8 bit sums, then add them in mod 255.
      // since 1 == 256 mod 255

      static const unsigned int _1_BIT   = 0x55555555;
      static const unsigned int _2_BITS  = 0x33333333;
      static const unsigned int _4_BITS  = 0x0f0f0f0f;

      static const unsigned long long _1_BIT_64   = 0x5555555555555555;
      static const unsigned long long _2_BITS_64  = 0x3333333333333333;
      static const unsigned long long _4_BITS_64  = 0x0f0f0f0f0f0f0f0f;

      unsigned int countbits(unsigned int number) {
        unsigned int sum = number;

        sum = ((sum >> 1) & _1_BIT) + (sum & _1_BIT);
        sum = ((sum >> 2) & _2_BITS) + (sum & _2_BITS);
        sum = ((sum >> 4) & _4_BITS) + (sum & _4_BITS);

        // sum is now ABCD, where A, B, C, D are the number of bits
        // in the respective bytes
        //
        // as a number this is (a*256^3 + b*256^2 + c*256 + d)
        //
        // now, (a*256^3 + b*256^2 + c*256 + d) MOD 256
        //    = (a * (256 MOD 255)^3 + b * (256 MOD 255)^2 + c * (256 MOD 255) + d) MOD 255
        //
        // a, b, c, d are all <= 8 so MOD 255 does not change them
        //
        // 256 MOD 255 on the other hand - that's just 1
        //
        //    (a * (256 MOD 255)^3 + b * (256 MOD 255)^2 + c * (256 MOD 255) + d) MOD 255
        //
        //  = (a * 1^3             + b * 1^2             + c * 1             + d) MOD 255
        //  = (a + b + c + d) MOD 255
        //
        // since abcd are each <= 8, this is just a+b+c+d,
        // which is the number of bits in each byte, added together to give the total
        // number of bits in the 4 byte word.

        // as long as the word size is less than 32 bytes ( so that the sum of the bits
        // in each byte is less than 255)

        return sum % 255;
      }

      unsigned int countbits64(unsigned long long number) {
        unsigned long long sum = number;

        sum = ((sum >> 1) & _1_BIT_64) + (sum & _1_BIT_64);
        sum = ((sum >> 2) & _2_BITS_64) + (sum & _2_BITS_64);
        sum = ((sum >> 4) & _4_BITS_64) + (sum & _4_BITS_64);

        return sum % 255;
      }
    }

    namespace improvement3 {
      // add flexibility, less hard coding
      //
      // get the compiler to create the bitmask at compile time
      // if we hardcode the bit mask it's not flexible
      template <typename _NUMBER, int _MASKSIZE, int _BITSLEFT>
      struct COUNTBITS_MASK_DETAIL {
        static const _NUMBER bits = ((1<<_MASKSIZE)-1) | ((COUNTBITS_MASK_DETAIL<_NUMBER, _MASKSIZE, (_BITSLEFT-(_MASKSIZE<<1))>::bits) << (_MASKSIZE<<1));
      };

      template <typename _NUMBER, int _MASKSIZE>
      struct COUNTBITS_MASK_DETAIL<_NUMBER, _MASKSIZE, 0> {
        static const _NUMBER bits = ((1<<_MASKSIZE)-1);
      };

      template <typename _NUMBER, int _MASKSIZE>
      struct COUNTBITS_MASK {
        static const _NUMBER bits = COUNTBITS_MASK_DETAIL<_NUMBER, _MASKSIZE, ((sizeof(_NUMBER)<<3)-(_MASKSIZE<<1))>::bits;
      };

      static const unsigned char _1_BIT_8 = COUNTBITS_MASK<unsigned char, 1>::bits; //0x55;
      static const unsigned char _2_BITS_8 = COUNTBITS_MASK<unsigned char, 2>::bits; //0x33;

      static const unsigned short _1_BIT_16 = COUNTBITS_MASK<unsigned short, 1>::bits; //0x5555;
      static const unsigned short _2_BITS_16 = COUNTBITS_MASK<unsigned short, 2>::bits; //0x3333;
      static const unsigned short _4_BITS_16 = COUNTBITS_MASK<unsigned short, 4>::bits; //0x0f0f;

      static const unsigned int _1_BIT = COUNTBITS_MASK<unsigned int, 1>::bits; //0x55555555;
      static const unsigned int _2_BITS = COUNTBITS_MASK<unsigned int, 2>::bits; //0x33333333;
      static const unsigned int _4_BITS = COUNTBITS_MASK<unsigned int, 4>::bits; //0x0f0f0f0f;

      static const unsigned long long _1_BIT_64 = COUNTBITS_MASK<unsigned long long, 1>::bits; //0x5555555555555555;
      static const unsigned long long _2_BITS_64 = COUNTBITS_MASK<unsigned long long, 2>::bits; //0x3333333333333333;
      static const unsigned long long _4_BITS_64 = COUNTBITS_MASK<unsigned long long, 4>::bits; //0x0f0f0f0f0f0f0f0f;

      unsigned char countbits(unsigned char sum) {
        sum = ((sum >> 1) & _1_BIT_8) + (sum & _1_BIT_8);
        sum = ((sum >> 2) & _2_BITS_8) + (sum & _2_BITS_8);

        return sum % 15;
      }

      unsigned short countbits(unsigned short number) {
        unsigned int sum = number;
        // weird - it's slower if the temporary is short

        sum = ((sum >> 1) & _1_BIT_16) + (sum & _1_BIT_16);
        sum = ((sum >> 2) & _2_BITS_16) + (sum & _2_BITS_16);
        sum = ((sum >> 4) & _4_BITS_16) + (sum & _4_BITS_16);

        return sum % 255;
      }

      unsigned int countbits(unsigned int sum) {
        sum = ((sum >> 1) & _1_BIT) + (sum & _1_BIT);
        sum = ((sum >> 2) & _2_BITS) + (sum & _2_BITS);
        sum = ((sum >> 4) & _4_BITS) + (sum & _4_BITS);

        return sum % 255;
      }

      unsigned int countbits(unsigned long long sum) {
        sum = ((sum >> 1) & _1_BIT_64) + (sum & _1_BIT_64);
        sum = ((sum >> 2) & _2_BITS_64) + (sum & _2_BITS_64);
        sum = ((sum >> 4) & _4_BITS_64) + (sum & _4_BITS_64);

        return sum % 255;
      }
    }

    namespace improvement4 {
      int _countbits_4_finale = int();
    }
  }
}
