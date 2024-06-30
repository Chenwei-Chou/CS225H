/**
 * @file fmi.cpp
 * Code to constructiong and searching a FM Index
 */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <map>
#include <algorithm>
#include <string>
#include "fmi.h"

using std::vector;
using std::string;
using std::cout;
using std::endl;

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
    std::rotate(T.begin(), T.begin() + 1, T.end());
  }
  return out;
}



/**
* FM Index constructor; Given T, creates:
* a Burrows Wheeler Transform (BWT)
* a suffix array (SA)
* an occurence table (OT)
* @param T The string being preprocessed into an FM Index
* @param alpha The alphabet we are building our index around
* @param sr The sample rate for the SA and OT (Optional)
*/
FMI::FMI(std::string T, std::string a, int sr){
  sampleRate = sr; //A purely optional protected variable
  alpha = a;

  // Alphabet is sorted to minimize debug difficulties
  // Also makes code easier
  std::sort(alpha.begin(), alpha.end()); 

  // Your code must implement all three of these
  // Autograder will check each individually
  BWT = buildBWT(T);
  SA = buildSA(T);
  OT = buildOT(BWT);
}


/*
* Destructor for FM Index
*/
FMI::~FMI()
{
    /* nothing unless you added more variables */
}

/**
 * Returns the SA of T as a vector of ints
 *
 * @param T A std::string object which holds the text being pre-processed.
 *
 * @return An std::vector<int> storing the suffix array
 */
std::vector<int> FMI::buildSA(std::string T){
  std::vector<int> sarray;

  std::vector<std::pair<std::string, int>> sufList;
  
  T = T + "$";
  size_t tlen = T.size();

  for (size_t i = 0; i < tlen; ++i){
    std::string t_suf = T.substr(i);
    sufList.push_back(make_pair(t_suf, i));
  }

  std::sort(sufList.begin(),sufList.end()); 

  for (size_t i = 0; i < tlen; ++i){
      sarray.push_back(sufList[i].second);
  }

  return sarray;
}


/**
 * Returns the BWT of T as a string
 *
 * @param T A std::string object which holds the text being pre-processed.
 *
 * @return An std::string storing the BWT
 */
std::string FMI::buildBWT(std::string T){

  // YOUR CODE HERE
  // Use last week's code here
  std::string bwt = "";
  vector<string> m_matrix = rotate(T + "$");
  sort(m_matrix.begin(), m_matrix.end());
  for (auto i: m_matrix) bwt += i.back();
  return bwt;
}


/**
 * Returns the Occurrence Table of a BWT (A 2D table of tsize x alphabet)
 *
 * @param T A std::string object which holds the text being pre-processed.
 *        T in this instance is *usually* the BWT. 
 *        Other strings may be tested by the autograder
 *
 * @return An std::vector<std::vector<int>> storing the cumulative count
 *         of each character 
 *
 *         rows are alphabet in length (one row per individual index positions)
 */
std::vector<std::vector<int>> FMI::buildOT(std::string T){
  //HINT: An easy solution increments at most one value per index in T
  //      You can do this using only a single row vector (and the given OT).
  //Your code here
  string build_BWT = T;
  const int a_size = alpha.size();
  const int b_size = build_BWT.size();
  std::vector<std::vector<int>> OT(b_size, vector<int>(a_size));

  for (int i = 0; i < b_size; i ++ ) {
    if (i > 0) OT[i] = OT[i - 1]; // copy whole row data
    for (int j = 0; j < a_size; j ++ ) {
      if (build_BWT[i] == '$') continue; 
      if (build_BWT[i] == alpha[j]) OT[i][j] += 1;
    }
  }
  return OT;
}

/**
* FM Index First Range Search
* Gives the index start and end position for the character 
* (and rank range) being searched
* 
* @param c The character being looked up
* @param s_rank The starting rank being searched 
* @param e_rank The ending rank being searched 
*
* HINT: You will have to reconstruct F from the BWT or the OT
*/
std::pair<int, int> FMI::get_frange(std::string c, int s_rank, int e_rank){
  //YOUR CODE HERE
  std::pair<int, int> out;
  string m_bwt = BWT;
  sort(m_bwt.begin(), m_bwt.end());
  const int b_size = BWT.size();
  vector<int> data;

  for (int i = 1, count = 0; i < b_size; i ++ ) {
    if (m_bwt[i] == c[0]) {
      if (count >= s_rank && count <= e_rank) data.push_back(i);
      count ++;
    }
  }
  out.first = data.front();
  out.second = data.back();
  return out;
}

/**
* FM Index Last Range Search
* Gives the number of occurrences of character *before* s_index (s_rank)
* and the number of occurrences of character at the e_index 
* 
* @param c The character being looked up
* @param s_index The starting index being searched 
* @param e_index The ending index being searched 
*
* HINT: L is the BWT, s_index *cannot* be 0. Why?
*/
std::pair<int, int> FMI::get_lrange(std::string c, int s_index, int e_index){
  std::pair<int, int> out;

  // YOUR CODE HERE
  int index = alpha.find(c);
  out.first = OT[s_index - 1][index];
  out.second = OT[e_index][index];
  return out;
}


/**
 * Performs exact pattern matching on the FM Index for input P
 *
 * @param P A std::string object which holds the pattern being searched.
 *
 * @return An std::vector<int> storing the index positions of matches
 *         or returns {-1} if there is no match
 */
std::vector<int> FMI::search(std::string P){
  std::vector<int> outList;

  std::string c = P.substr(P.size()-1,1);

  int letter = alpha.find(c);
  
  // If letter not in alphabet, stop searching
  if (letter == -1){
    outList.push_back(-1);
    return outList;
  }
  
  // F column can be represented by the occurrence # of each character
  std::vector<int> F = OT.back();

  // Our first occurrence of char c has rank 0
  // Our last occurrence of char c has rank # occurrences - 1
  // @TODO: REPLACE THESE VALUES WITH THE APPROPRIATE STARTING VALUES
  // int s_rank = -1;  
  // int e_rank = -1; //HINT: How do I know the # occurrences?
  int s_rank = 0;             // check
  int e_rank = F[letter] - 1; // check

  // If my last occurrence has rank -1, it means I never saw the character at all.
  if (e_rank == -1){
    outList.push_back(-1);
    return outList;
  }

  // Get the initial F range to search (Index start - Index end)
  // You will have to code get_frange to match this code
  std::pair<int,int> frange = get_frange(c, s_rank, e_rank);

  // FMI logic finds range of occurrences (using L), then finds FM index range to search (in F)
  // In other words:
  // lrange outputs # of occurrences before start index and at end index
  // These occurrence numbers determine the range start and end values, used by frange.
  //
  // frange outputs index start and end
  // These index positions are used by lrange directly
  // 
  // The final frange (index start and end) tells us which suffix array values to look up
  for(int i = P.size()-2; i >= 0; i--){
    c = P.substr(i,1);

    letter = alpha.find(c);

    //Gets the start and end rank values for c_{i-1} based on index start and end for c_{i}
    // (Recall that we are starting from i = size()-1)
    // You will have to code get_lrange to match this code
    std::pair<int,int> lrange = get_lrange(c, frange.first, frange.second);

    // @TODO: REPLACE THIS VALUE WITH THE APPROPRIATE VALUES
    int numMatches =  lrange.second - lrange.first;  // check

    // If lrange returns the same value start to end, we have no characters in range.
    if(numMatches <= 0){
      outList.push_back(-1);
      return outList;
    }

    // Given our range values we want the index values
    // Recall that lrange outputs occurrences not ranges
    // The occurrence # before our first index is our first rank -- why?
    // The occurrence # at our last position MINUS 1 is our last rank -- why?
    frange = get_frange(c, lrange.first, lrange.second - 1);

    if( frange.first == -1 || frange.second == -1){
      outList.push_back(-1);
      return outList;
    }
  }

  // @TODO: WRITE CODE TO ADD ALL MATCHES TO outList
  for (int i = frange.first; i <= frange.second; i ++ ) // check
    outList.push_back(SA[i]);                           // check
  return outList;
}