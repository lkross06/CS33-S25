/* 
 * CS:APP Data Lab 
 * 
 * Lucas Kalani Ross 506372478
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }


NOTES:
  1. Our checker requires that you do NOT define a variable after 
     a statement that does not define a variable.

     For example, this is NOT allowed:

     int illegal_function_for_this_lab(int x, int y) {
      // this statement doesn't define a variable
      x = x + y + 1;
      
      // The checker for this lab does NOT allow the following statement,
      // because this variable definition comes after a statement 
      // that doesn't define a variable
      int z;

      return 0;
     }
     
  2. VERY IMPORTANT: Use the dlc (data lab checker) compiler (described in the handout)
     to check the legality of your solutions.
  3. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  4. Use the btest to check your functions for correctness.
  5. The maximum number of ops for each function is given in the
     header comment for each function. 

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the btest to verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* Copyright (C) 1991-2012 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* We do support the IEC 559 math functionality, real and complex.  */
/* wchar_t uses ISO/IEC 10646 (2nd ed., published 2011-03-15) /
   Unicode 6.0.  */
/* We do not support C11 <threads.h>.  */
//1
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  /*
  We want to know if x = 0111 1111 1111 ... 1111

  ~x = 1000 0000 0000 ... 0000, which is also x + 1 (since the remainder 1 is carried all the way
  down to the MST). This is a unique property of Tmax which we can exploit to test any signed x.

  If the two binary numbers ~x and x + 1 are the same, then ~x ^ x + 1 = 0, and !(0) = 1. otherwise, !() returns 0.

  Also, for -1, overflow also occurs. Since x + 1 retuns 0 for x = -1 and Tmin for x = Tmax, we
  can use two ! operators to check for non-zero result from x + 1 as a safeguard against -1.
  Normally we could just >> 31 and check the sign bit, but the >> operator is banned
  */

  return !(~x ^ (x + 1)) & !!(x + 1);
}
//2
/* 
 * evenBits - return word with all even-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int evenBits(void) {
  /*
  We want to return 0101 0101 0101 0101 0101 0101 0101 0101 (32 bits or 4 bytes)
  The largest integer constant we can use with the 0101 pattern is 0x55 = 0101 0101 (one byte)

  So we add 0x55 to 0 and then left shift over b by one byte, and repeat this four times.
  Notice that 0x55 is really just 0000 0000 0000 0000 0000 0000 0101 0101, so its only affecting the newly-shifted
  byte of 0s.

  b should look like

  (1) 
    0000 0000 0000 0000 0000 0000 0101 0101
  (2)
    0000 0000 0000 0000 0101 0101 0000 0000
    0000 0000 0000 0000 0101 0101 0101 0101
  (3)
    0000 0000 0101 0101 0101 0101 0000 0000
    0000 0000 0101 0101 0101 0101 0101 0101
  (4)
    0101 0101 0101 0101 0101 0101 0000 0000
    0101 0101 0101 0101 0101 0101 0101 0101
  */

  int a = 0x55;
  int b = a; //(1)

  b = (b << 8) + a; //(2)
  b = (b << 8) + a; //(3)
  b = (b << 8) + a; //(4)

  return b;
}
//3
/* 
 * isEqual - return 1 if x == y, and 0 otherwise 
 *   Examples: isEqual(5,5) = 1, isEqual(4,5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int isEqual(int x, int y) {
  /*
  If all of the bits are the same, then x ^ y = 0. Otherwise, x ^ 1 is non-zero. We can use a !
  operator to both 1) switch our answer (its asking for isEqual, not isNotEqual) and 2) format
  as a 1 or 0.
  */

  return !(x ^ y);
}
//4
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  /*
  x can be represented as an n-bit two's complement integer IF the nth bit matches all other
  (32 - n) bits to the left (because all the 1s would cancel out to a 1 as the nth bit for 
  negative integers, and all the 0s wouldnt do anything for positive numbers).

  y extracts the nth bit by moving it all the way to the left then copying down every slot with
  arithematic right shift.

  z extracts the other (32 - n) bits, where the other n bits on the left are filled by whatever the
  sign bit is. it doesnt really matter. In C, trying to do x >> 32 is undefined behavior, so for
  safeguarding (since we know n <= 32) we first shift by n - 1, then shift once more. That way, we
  avoid undefined behavior and >> 32 is broken up into >> 31 and then >> 1.

  if y and z are equal, then the nth bit matches all other (32 - n) bits to the left, so y ^ z = 0
  and the function returns 1 due to !. otherwise, if there are any differences in the (32 - n) bits to the left,
  the function returns 0 due to !.
  */
  int y = (x << (32 + (~n + 1))) >> 31;
  int z = (x >> (n + (~1 + 1))) >> 1;
  return !(y ^ z);
}
//5
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  /*
  We want filter to be all 1s if x != 0, so that all of y gets copied and none of z gets copied,
  and we want filter to be all 0s if x == 0, so that all of z gets copied and none of y gets copied.

  !!x will become 1 if x != 0 and 0 if x == 0. We shift it left 31 times so the 1/0 becomes the sign
  bit, then right 31 times so the 1/0 gets copied into all 32 bits, creating a filter of either all
  1s or all 0s.
  */
  int filter = ((!(!x)) << 31) >> 31;
  return (y & filter) | (z & ~filter);
}
//6
/* 
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {
  /*
  We must consider two cases: one where both signs are the same, and one where both signs are
  different. We use same_sign to ignore one of the cases and only return the result of the other.
  We can see if x and y have the same signs by extracting/copying the sign bit with >> 31 and ^
  them against each other, which gives all 1s for different and all 0s for same. Then we ! to reverse
  the results.

  If the signs are different, then x > y so long as x is the positive integer and y is the negative
  integer.

  If the signs are the same, then we compute the difference as x - y using the property -y = ~y + 1.
  Then we check to make sure 1) the difference is non-negative (extract/copy sign bit) and 2) the
  difference is non-zero (! twice so its 0x1 or 0x0).
  */

  int x_sign = x >> 31;
  int y_sign = y >> 31;
  int same_sign = !(x_sign ^ y_sign); // 0 if different, 1 if same

  int diff = x + (~y + 1);
  int pos_diff = !((diff >> 31) & 1) & (!!diff); //1 for >0, 0 otherwise

  return (same_sign & pos_diff) | (!same_sign & !(x_sign));
}
//7
/*
 * multFiveEighths - multiplies by 5/8 rounding toward 0.
 *   Should exactly duplicate effect of C expression (x*5/8),
 *   including overflow behavior.
 *   Examples: multFiveEighths(77) = 48
 *             multFiveEighths(-22) = -13
 *             multFiveEighths(1073741824) = 13421728 (overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 3
 */
int multFiveEighths(int x) {
  /*
   (1) multiply by 5, which we can simplify to 4x + x or (x * 2^2) + x
   
   (2) since right shifting always floors (rounds towards negative infinity), we must +3 for any negative integers
   (and we could say +0 for positive integers). (x + 3) >> 2 is adjacent to (x >> 2) + 1 for negative integers.
   x >> 31 "extracts the sign bit", becoming all zeros (0) if positive or all ones (-1) if negative.
   then we & 7 so that, only if (x >> 31) is negative, it keeps the 111 at the end of 7. otherwise, the bias becomes all zeros.
   
   (3) divide by 8 (or x / 2^3) and floor.

   See that the solution is slightly different from lab 0 in that we & 9 instead of & 3 for the bias.
   This is so that the bias is always n - 1, where n is the denominator (in this case, 8. in lab 0, 4).
   We always want to add 1 to the pre-biased solution, and so we must add n - 1 so that if it would round
   perfectly, the floor if it still rounds down instead of rounding up by one.
   */
  int bias;

  x = (x << 2) + x; 
  bias = (x >> 31) & 7;
  x = (x + bias) >> 3;

  return x;
}
//8
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  /*
  One property of zero (and only zero) is that overflow causes -0 (or ~0 + 1)
  to be zero. That means that for zero, and zero only, the MST of x and ~x + 1 is
  zero. We can use an | to effectively combine x and -x, and >> 31 so that the sign bit
  is copied.

  Now, ((x | (~x + 1)) >> 31) stores all 0s if x = 0, and all 1s if x != 0. If we add 1
  to both of these values, it becomes 1 for all 0s and becomes 0 for all 1s due to overflow,
  which also accomplishes our goal of reversing the T/F interpretation of the bits.
  */
  return ((x | (~x + 1)) >> 31) + 1;
}
//9
/* 
 * twosComp2SignMag - Convert from two's complement to sign-magnitude 
 *   where the MSB is the sign bit
 *   You can assume that x > TMin
 *   Example: twosComp2SignMag(-5) = 0x80000005.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 4
 */
int twosComp2SignMag(int x) {
  /*
  We know that we can extract/copy the sign bit with x >> 31

  Determining the magnitude varies between positive/negative integers:
  - if positive, then just all bits after the last 0 to the left
  - if negative, then just all bits after the second-to-last 1 to the left

  If we ^ the integer with copies of its sign bit, it sets all of the ignorable "to the left"
  bits to 0. For negatives, we add 1 to get the last 1 bit back (since we stop after the
  second-to-last 1, not the last 1).

  Finally, we shift over the sign again so only the MST is 0/1, then add the magnitude into the
  remaining slots.
  */
  int sign = x >> 31;
  int magnitude = (x ^ sign) + (sign & 1);
  return (sign << 31) + magnitude;
}
//10
/*
 * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5) = 0, isPower2(8) = 1, isPower2(0) = 0
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int isPower2(int x) {
  /*
  "y" will be set to 1 if x is a power of two, and 0 if x is not a power of two. Notice that the
  return statement has & ~(x >> 31), which will always return 0 if x is negative, regardless of
  the value of y. This safety mechanism allows us to only focus on positive integers for x. 

  First, notice that x is only a power of two if it has only one 1 bit.

  When you add all 1s (or ~0) to x, it will cascade 0s down the number starting at the first
  1 in x (due to 1 + 1 = 10), until either reaching the 33rd bit (and getting cut off) or
  reaching another 1 bit in x. If it reaches another 1 bit in x, then 1 + 1 + 1 = 11, so a 1
  is placed at that spot, and the cascade keeps going.

  We want to see if there is another 1 bit after whatever the first 1 bit we find in x. If we
  take x & (x + ~0), it becomes all 0s for powers of two (since the only place where there is a 1
  bit in x is where the cascade of 0s starts), or not all 0s otherwise (since 1 + 1 + 1 == 11 happened
  somewhere after the first 1 bit). So we ! that to produce y=1 for powers of two and y=0 otherwise.

  Since x=0 also cascades to 0 (yet is not a power of two), we & !!x so that if x is zero,
  y becomes zero anyways. Otherwise, y is 0/1 (whatever we found it to be above.)
  */
  int y = !(x & (x + ~0)); 
  y = y & (!!x);
  return (y & ~(x >> 31));
}
