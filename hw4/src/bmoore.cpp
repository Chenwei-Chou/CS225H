/**
 * @file bmoore.cpp
 * Code to Boyer-Moore solution for exact pattern matching.
 * Uses strong bad character rule only
 */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <map>

#include "bmoore.h"

using std::string;
using std::vector;

/**
 * Takes in two strings (P and the alphabet) 
 * Returns a 2D array containing the skip values for bad character rule
 *
 * @param P A std::string object which holds the pattern being pre-processed.
 * @param alpha An std::string object which holds all characters in the alphabet of P and T.
 *
 * @return An std::vector<std::vector<int>> (a 2D array of integers) storing the bad character array
 * BC_array rows correspond to the alphabet and the columns correspond to positions along the pattern.
 */
std::vector<std::vector<int>> prep_bc_array(std::string P, std::string alpha){
  std::vector<std::vector<int>> bc_array;
  const int p_size = P.size();
  const int a_siez = alpha.size();
  
  for (int i = 0; i < a_siez; i ++ ) {
    vector<int> tmp = {0};
    for (int j = 1; j < p_size; j ++ )
      tmp.push_back(j - P.substr(0,j).rfind(alpha[i]) - 1);
    bc_array.push_back(tmp);
  }
  return bc_array;
}

/**
 * Returns the index positions of first instance of c in alpha.
 * If no match is found, returns the value '-1'
 *
 * A potentually useful helper function for relating characters to integers
 * As a fun fact, this was a valid solution to naive_search (Week 1)
 *
 * NOTE: This is not actually an efficient solution but we are handwaving it here.
 *
 * @param alpha A std::string object which holds the alphabet string.
 * @param c A char object which holds the character being searched for
 *
 * @return An integer containing the index position of c in alpha
 */
int findChar(std::string alpha, char c){
  //return alpha.find(c);
  if (alpha.find(c) == string::npos) return -1;
  return alpha.find(c);
}

/**
 * Returns the number of alignments skipped by Boyer-Moore
 * In this instance, Boyer-Moore is *only* the strong bad character rule [and right-to-left scanning]
 *
 * Also modifies the outlist vector to contain the index positions of all exact matches of P in T.
 * If no match is found, modifies the vector to contain one value '[-1]'
 *
 * @param P A std::string object which holds the Pattern string.
 * @param T A std::string object which holds the Text string.
 * @param alpha A std::string object which holds the Alphabet string.
 * @param outList An std::vector<int> array (by reference) that can be modified to contain all matches
 *
 * @return An int counting the number of skipped alignments using bad character.
 */
int bmoore_search(std::string P, std::string T, std::string alpha, std::vector<int> & outList){
  int skip = 0;
  std::vector<std::vector<int>> bc_array = prep_bc_array(P, alpha);
  const int p_size = P.size(); // Pre-compute BC array
  const int t_size = T.size(); // Your solution must use this array.

  for (int i = p_size - 1, m_skip; i < t_size; i ++ ) {
    bool skip_check = true;
    for (int j = p_size - 1, index = i; j >= 0 && skip_check; index --, j -- ) {
      if (P[j] != T[index]) {
        skip_check = false;
        m_skip = bc_array[findChar(alpha, T[index])][j];  // table find skip
        i += m_skip;
        if (i >= t_size - 1) skip += m_skip - (i - (t_size - 1)); // out of range
        else skip += m_skip;  // in range
      }
    }
    if (skip_check) outList.push_back(i - (p_size - 1));
  }
  if (outList.empty()) outList.push_back(-1);
  return skip;
}