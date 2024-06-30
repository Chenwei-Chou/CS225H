/**
 * @file bwt.cpp
 * Code to encoding and decoding a text using the BWT
 */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <map>
#include <algorithm>

#include "bwt.h"

using namespace std;

/**
 * Returns a vector of strings containing all rotations of a text
 *
 * @param T A std::string object which holds the text being pre-processed.
 *
 * @return An std::vector<std::string> storing all rotations
 */
std::vector<std::string> rotate(std::string T){

  // Your code here (if you think it will help)
  std::vector<std::string> out;
  const int t_size = T.size();

  for (int i = 0; i < t_size; i ++) {
    out.push_back(T);
    rotate(T.begin(), T.begin() + 1, T.end()); // std::rotate
  }
  return out;
}


/**
 * Returns the BWT of T as a string
 *
 * @param T A std::string object which holds the text being pre-processed.
 *
 * @return An std::string storing the BWT
 */
std::string encode_bwt(std::string T){

  // Your code here
  string m_bwt;

  vector<string> m_matrix = rotate(T + "$");
  sort(m_matrix.begin(), m_matrix.end());
  for (auto i: m_matrix) m_bwt += i.back();
  return m_bwt;
}

/**
 * Returns the BWT of T as a string
 *
 * @param T A std::string object which holds the text being pre-processed.
 *
 * @return An std::string storing the BWT
 */

std::string decode_bwt(std::string bwt){

  // YOUR CODE HERE
  const int b_size = bwt.size();
  string m_bwt;

  vector<string> m_matrix(b_size);
  for (int i = 0; i < b_size; i ++ ) {
    for (int j = 0; j < b_size; j ++ )
      m_matrix.at(j) = bwt.at(j) + m_matrix.at(j);
    sort(m_matrix.begin(), m_matrix.end());
  }
  for (auto i: m_matrix)
    if (i.front() == '$') m_bwt = i.substr(1);
  return m_bwt;
}
