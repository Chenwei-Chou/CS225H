/**
 * @file zval.cpp
 * Code to create Z-array and use Z-values for exact pattern matching.
 */

#include <iostream>
#include <cmath>
#include <cstdlib>

#include "zval.h"
//
#include <algorithm>
#include <utility>
using namespace std;
//
/**
 * Returns the number of character comparisons required to find the first mismatch
 * or to completely match strings X and Y.
 *
 * @param X A std::string object which holds the first string being matched
 * @param Y An std::string object which holds the second string being matched
 *
 * @return An std::pair<int, int>. 
 *         The first value is the number of individual character comparisons needed.
 *         The second value is the longest common prefix length (match length)
 */

 std::pair<int,int> lr_scan(std::string X, std::string Y){
  int charComps = 0;

  // The std::pair object is defined with two variable types (in this case both int)
  std::pair<int, int> out;
  if (X.size() < Y.size()) swap(X, Y);
  const int pattern_size = Y.size();

  for (int i = 0; i < pattern_size ; i ++ ) {
    if (X[i] != Y[i]) break;
    charComps ++ ;
  }
  out = (pattern_size == charComps) ? make_pair(charComps, charComps) : make_pair(charComps + 1, charComps);
  return out;
 }


/**
 * Returns an array which stores the Z-value at each position i<0
 * The 0th position (i=0) should store the total number of 
 * Also modifies the input (empty) zArray to store the Z-value at each position i<0
 *
 * @param S A std::string object which holds the String being analyzed.
 * @param Z An int* that points to a length |S| int[] which holds the zArray.
 *
 * @return An integer counting the number of character comparisons needed to make the Z-array.
 */
int create_zarray(std::string S, int* Z) {
  int charComps = 0; //the number of character comparisons needed to make the Z-array
  int tmp = S.find("$");
  string P = S.substr(0, tmp);
  const int s_size = S.size();
  const int p_size = P.size();
  
  for (int i = 0; i < s_size; i ++ ) Z[i] = 0;
  for (int i = 1; i < s_size; i ++ ) {
    for (int j = 0; j < p_size; j ++ ) {
      if (i + j < s_size) {
        if (P[j] != S[i + j]) break;
        Z[i] ++;
      }
    }
    pair<int,int> result = lr_scan(S, S.substr(i, s_size - i));
    charComps += result.first;
  }

  return charComps;
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
std::vector<int> zval_search(std::string P, std::string T) {
  std::vector<int> outList;
  string S = P + "$" + T;
  const int s_size = S.size();
  const int p_size = P.size();
  int *Z = new int[s_size];
  create_zarray(S, Z);

  for (int i = 1; i < s_size; i ++ )
    if (Z[i] == p_size) outList.push_back(i - (p_size + 1)); // because of P + "$"
  if (outList.empty()) outList.push_back(-1);

  return outList;
}
