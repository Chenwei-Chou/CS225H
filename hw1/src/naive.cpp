/**
 * @file naive.cpp
 * Intro to strings, pattern matching, and prefix/suffixes .
 */

#include <iostream>
#include <cmath>
#include <cstdlib>
//
#include <algorithm> 
//

#include "naive.h"

using std::string;

/**
 * Returns the index position of the first exact match of P in T.
 * If no match is found, returns the value '-1'
 *
 * Search the Text string (T) for the Pattern string (P)
 * For example, if P = 'AAA' and T = 'BAAAT', will return 1
 *
 * @param P A std::string object which holds the Pattern string.
 * @param T A std::string object which holds the Text string.
 *
 * @return An integer.
 */
int naive_search(std::string P, std::string T) {
  const int size_t_ = T.size();
  const int size_p_ = P.size();

  if (T == P) return 0;
  for (int i = 0; i < size_t_ - size_p_; i ++ )
    if (T[i] == P[0] && P == T.substr(i, size_p_)) return i;
  return -1;
}

/**
 * Returns the string corresponding to the longest common prefix between P and T
 * If there is no common prefix, returns an empty string.
 *
 * @param P A std::string object which holds the Pattern string.
 * @param T A std::string object which holds the Text string.
 *
 * @return An std::string.
 */
std::string longest_common_prefix(std::string P, std::string T) {
  std::string lcp;
  const int size_t_ = T.size();

  for (int i = 0; i < size_t_; i ++ ) {
    if (T[i] != P[i]) break;
    lcp.push_back(T[i]);
  }
  
  return lcp;
}

/**
 * Returns the string corresponding to the longest common suffix between P and T
 * If there is no common suffix, returns an empty string.
 *
 * @param P A std::string object which holds the Pattern string.
 * @param T A std::string object which holds the Text string.
 *
 * @return An std::string.
 */
std::string longest_common_suffix(std::string P, std::string T) {
  std::string lcs;
  reverse(T.begin(), T.end()); 
  reverse(P.begin(), P.end()); 
  lcs = longest_common_prefix(P, T);
  reverse(lcs.begin(), lcs.end());

  return lcs;
}


