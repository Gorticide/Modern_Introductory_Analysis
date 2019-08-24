/*
 Copyright (c) 2011, Louis-Philippe Lessard
 All rights reserved.
 Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 unsigned gcd( unsigned a, unsigned b );
 unsigned gcd_arr(unsigned * n, unsigned size);
 unsigned lcm(unsigned a, unsigned b);
 unsigned lcm_arr(unsigned * n, unsigned size);
 int main()
 {
      unsigned test1[] = {8, 9, 12, 13, 39, 7, 16, 24, 26, 15};
      unsigned test2[] = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048};
      unsigned result;
      result = gcd_arr(test1, sizeof(test1) / sizeof(test1[0]));
      result = gcd_arr(test2, sizeof(test2) / sizeof(test2[0]));
      result = lcm_arr(test1, sizeof(test1) / sizeof(test1[0]));
      result = lcm_arr(test2, sizeof(test2) / sizeof(test2[0]));
      return result;
 }
 /**
  * Find the greatest common divisor of 2 numbers
  * See http://en.wikipedia.org/wiki/Greatest_common_divisor
  *
  * @param[in] a First number
  * @param[in] b Second number
  * @return greatest common divisor
  */
 unsigned gcd( unsigned a, unsigned b )
 {
  unsigned c;
  while ( a != 0 )
  {
    c = a;
    a = b%a;
    b = c;
  }
  return b;
 }
 /**
  * Find the least common multiple of 2 numbers
  * See http://en.wikipedia.org/wiki/Least_common_multiple
  *
  * @param[in] a First number
  * @param[in] b Second number
  * @return least common multiple
  */
 unsigned lcm(unsigned a, unsigned b)
 {
   return (b / gcd(a, b) ) * a;
 }
 /**
  * Find the greatest common divisor of an array of numbers
  * See http://en.wikipedia.org/wiki/Greatest_common_divisor
  *
  * @param[in] n Pointer to an array of number
  * @param[in] size Size of the array
  * @return greatest common divisor
  */
 unsigned gcd_arr(unsigned * n, unsigned size)
 {
      unsigned last_gcd, i;
      if(size < 2) return 0;
      last_gcd = gcd(n[0], n[1]);
      for(i=2; i < size; i++)
      {
           last_gcd = gcd(last_gcd, n[i]);
      }
      return last_gcd;
 }
 /**
  * Find the least common multiple of an array of numbers
  * See http://en.wikipedia.org/wiki/Least_common_multiple
  *
  * @param[in] n Pointer to an array of number
  * @param[in] size Size of the array
  * @return least common multiple
  */
 unsigned lcm_arr(unsigned * n, unsigned size)
 {
      unsigned last_lcm, i;
      if(size < 2) return 0;
      last_lcm = lcm(n[0], n[1]);
      for(i=2; i < size; i++)
      {
           last_lcm = lcm(last_lcm, n[i]);
      }
      return last_lcm;  
