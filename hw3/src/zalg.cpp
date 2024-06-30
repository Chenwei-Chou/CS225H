/**
 * @file zalg.cpp
 * Code to create Z-array and use Z-algorithm for exact pattern matching.
 */

#include <iostream>
#include <cmath>
#include <cstdlib>

#include "zalg.h"

using namespace std;
using namespace cs225;

/**
 * Returns the number of individual character comparisons used by the Z-algorithm
 * Also modifies the input (empty) zArray to store the Z-value at each position i>0
 *
 * @param S A std::string object which holds the String being analyzed.
 * @param Z An int* that points to a length |S| int[] which holds the zArray.
 *
 * @return An integer counting the number of character comparisons needed to make the Z-array.
 */
int create_zarray(std::string S, int* Z) {
  // You need to track character comparisons. Here are two suggested ways: 
  int charComps = 0; //Count Directly! (Same as z-value assignment)
  cs225::zstring inS(S); //Use 'cs225::zstring' to automatically track comparisons
  const int s_size = inS.length();

  while (inS.i < s_size) {
    if (inS.i > inS.r) {  // page 32
      int x = 0;
      while (inS.i + x < s_size) { // page 4 [update]
        if (inS.charMatch(x, inS.i + x)) x ++ ;
        else break;
      }
      Z[inS.i] = x;
      if (x > 0 && inS.i + x - 1 > inS.r) inS.r = inS.i + x - 1;  // update r
      inS.l = inS.i;  // update l
    } else { // page 32
      const int beta = inS.r - inS.i + 1;
      const int k = inS.i - inS.l;
      if (Z[k] < beta) Z[inS.i] = Z[k];
      else if (Z[k] > beta) Z[inS.i] = beta;
      else {
        int x = 0;
        while (inS.i + x < s_size) {
          if (inS.charMatch(beta + x, inS.r + 1)) x ++, inS.r ++ ; // update r
          else break;
        }
        Z[inS.i] = Z[k] + x;
        inS.l = inS.i; // update l
      }
    }
    inS.i ++;
  }

  return inS.getCharComps();
}

/**
 * Returns the index positions of all exact matches of P in T.
 * If no match is found, returns a vector with one value '[-1]'
 * NOTE: We want the exact matches *in T* not string S.
 *
 * Search the Text string (T) for the Pattern string (P)
 * For example, if P = 'AAA' and T = 'BAAAT', will return 1
 *
 * @param P A std::string object which holds the Pattern string.
 * @param T A std::string object which holds the Text string.
 *
 * @return An std::vector<int> array containing ALL index matches.
 */
std::vector<int> zalg_search(std::string P, std::string T) {
  std::vector<int> outList;
  
  // NOTE: Z-algorithm search is NOT GRADED as part of a_zalg.cpp. 
  //       Once you have completed a_zval, the code should work for both.
  
  // NOTE: You should change this function as necessary to complete the assignment.
  //std::string S = "ZALG TAKES IN ONE STRING. HOW DO I USE ZALG FOR PATTERN MATCHING?";
  string S = P + "$" + T;
  const int s_size = S.size();
  const int p_size = P.size();
  int *zarr = new int[S.length()];

  int charComps = create_zarray(S, zarr);

  for (int i = 1; i < s_size; i ++ )
    if (zarr[i] == p_size) outList.push_back(i - (p_size + 1)); // because of P + "$"
  if (outList.empty()) outList.push_back(-1);

  delete[] zarr; // No memory leaks here!
  return outList;
}