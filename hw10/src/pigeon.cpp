/**
 * @file pigeon.cpp
 * Approximate Pattern Matching using pigeonhole
 */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <vector>

#include "pigeon.h"

using namespace std;

/**
 * Takes a filename and reads in all the text from the file
 * Newline characters are also just characters in ASCII
 * 
 * @param filename The name of the file that will fill the string
 */
std::string file_to_string(const std::string& filename){
  std::ifstream text(filename);

  std::stringstream strStream;
  if (text.is_open()) {
    strStream << text.rdbuf();
  }
  return strStream.str();
}

/**
 * Takes an input text and transforms it to a vector of all the kmers in that text.
 * A kmer is a fixed length substring (watch your edge cases!)
 * @param T A reference variable storing the input text
 * @param k The size of the kmer
 */
kmerMap text_to_kmer_map(std::string & T, int k){
  kmerMap outMap;
  string key_s;

  // YOUR CODE HERE
  int t_size = T.size();

  for (int i = 0; i < t_size - k + 1; i ++ ) { //out bound
    key_s = T.substr(i, k);
    if (outMap.find(key_s) != outMap.end())
      outMap[key_s].push_back(i);
    else outMap[key_s] = {i};
  }
  return outMap;
}

/**
 * Takes an input pattern and number of partitions and returns a vector of type Seed
 * 
 * Seed is a pair<string, int> containing the string partition and its starting index in P
 * The partitions are non-overlapping strings
 *
 * If there are excess characters (division is not a whole number)
 * distribute the characters round-robin starting with the first partition.
 * Ex: ABCD partitioned into three partitions is AB, C, D (The extra char goes to first partition)
 *
 * @param P The input pattern
 * @param numPart The number of partitions
 */
std::vector<Seed> partitionPattern(std::string P, int numPart){
  std::vector<Seed> outVec;

  // YOUR CODE HERE
  const int p_size = P.size();
  unsigned int partition = p_size / numPart;
  unsigned int part_extend = p_size % numPart;
  string tmp = "";
  int index = 0; 

  for (int i = 0; i < p_size; i ++ ) {
    if (tmp.size() < partition) tmp += P[i];
    if (part_extend && tmp.size() == partition) { 
      i ++;
      tmp += P[i];
      part_extend --;
    }
    if (tmp.size() >= partition) {
      outVec.push_back({tmp, index});
      index += tmp.size();
      tmp = "";
    }
  }
  if(!tmp.empty()) outVec.push_back({tmp, index});

  return outVec;
}

/**
 * Performs inexact pattern matching between input text and pattern
 * Returns a vector<int> of match index positions and offsets
 * You can implement this using any method you want.
 * You are strongly encouraged to use the Seed values and kmerMap
 * @param fname The input text file being indexed and then searched over
 * @param P The input pattern being searched for
 * @param mm The number of mismatches (defaults to one but others will be tested)
 */
std::vector<int> approximate_search(const std::string & fname, std::string P, int mm){
  std::vector<int> outList;

  // your code here
  auto m_text = file_to_string(fname);
  const int t_size = m_text.size();
  const int p_size = P.size();
  auto m_seed = partitionPattern(P, (mm + 1));
  int k1 = p_size / (mm + 1);
  int k2 = p_size % (mm + 1);
  kmerMap outMap;
  set<int> m_set;
  int count = 0;
  
  if (k2) { // k2 != 0 
    outMap = text_to_kmer_map(m_text, k1);
    kmerMap outMap2 = text_to_kmer_map(m_text, k1 + 1);
    for (const auto & i : outMap2) outMap.insert(i);
  } else outMap = text_to_kmer_map(m_text, k1); // k2 = 0

  for (auto i : m_seed) { // seed is pattern
    auto data = outMap.find(i.first); // match text
    if (data == outMap.end()) continue;
    auto m_string = data->first;  // text string
    auto m_vector = data->second; // text index
    // m_outMap.insert({m_string, m_vector});
    for (auto j : m_vector) {
      auto index = j - i.second;
      // cout << "index = " << index << endl;
      if (index >= 0 && index + p_size <= t_size) m_set.insert(index);
    }
  }
  for (auto index : m_set) {
    count = 0;
    for (int i = 0; i < p_size; i ++ ) {
      if (P[i] != m_text[i + index]) count ++;
    }
    if (count <= mm) outList.push_back(index);
  }
  if (outList.empty()) outList.push_back(-1);
  return outList;
}