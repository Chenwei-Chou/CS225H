/**
 * @file sarray.cpp
 * Code to using suffix arrays for exact pattern matching.
 */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <map>
#include <algorithm>

#include "sarray.h"

using namespace std;

/**
 * Returns the suffix array of T as an int vector.
 *
 * @param T A std::string object which holds the text being pre-processed.
 *
 * @return An std::vector<int> storing the suffix array
 */
std::vector<int> build_sarray(std::string T){
  std::vector<int> sarray;
  vector<string> m_string;
  const int t_size = T.size();

  for (int i = 0, index = t_size; i < t_size + 1; i ++ , index -- )
    m_string.push_back(T.substr(index, i) + "$");

  sort(m_string.begin(), m_string.end());

  for (auto i: m_string) sarray.push_back(t_size + 1 - i.size());

  return sarray;
}


/**
 * Returns a vector of indices containing all exact pattern match locations
 *
 * @param P A std::string object which holds the pattern being searched
 * @param T A std::string object which holds the text the SA is built on [excluding '$']
 * @param sarray A std::vector<int> which holds the suffix array
 *
 * @return An std::vector<int> storing all matching index positions
 * NOTE: For full credit, you must use the suffix array
 */
std::vector<int> sarray_search(std::string P, std::string T, std::vector<int> sarray){
  std::vector<int> outList;

  // To avoid confusion, the input T will be the same for both functions.
  T = T+"$"; 

  // YOUR CODE HERE
  const int s_size = sarray.size();
  const int p_size = P.size();
  const int t_size = T.size();

  for (int i = 0; i < s_size; i ++ ) {
    if (sarray.at(i) > t_size - p_size) continue;
    auto tmp = T.substr(sarray.at(i), p_size);
    if (P == tmp) outList.push_back(sarray.at(i));
  }
  if (outList.empty()) outList.push_back(-1);
  return outList; 
}


int getSmallest(std::string P, std::string T, std::vector<int> sarray){

  // YOUR CODE HERE (if you think it helpful)
  return 0;
}

int getLargest(std::string P, std::string T, std::vector<int> sarray){

  // YOUR CODE HERE (if you think it helpful)
  return 0;
}
