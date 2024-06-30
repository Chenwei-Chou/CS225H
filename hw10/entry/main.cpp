/**
 * @file main.cpp
 * A simple C++ program for exploring the pigeonhole principle
 */

#include <string>
#include <iostream>
#include <vector>
#include <map>

#include "pigeon.h"

int main() {

  // std::string fname = "../tests/data/pub1.txt";
  std::string fname = "../tests/data/pub2.txt";
  // std::string fname = "../tests/data/pub3.txt";
  // std::string fname = "../tests/data/five_sonnets.txt";
  // std::string fname = "../tests/data/single_sentence.txt";
  // std::string P = "ABBA";
  std::string P = "duck";
  int mm = 1;

  // std::string T = "ABCDEFG";
  std::string T = file_to_string(fname);
  kmerMap outMap = text_to_kmer_map(T, P.size() / (mm + 1)); // mm
  std::cout << "text_to_kmer_map:" << std::endl;
  for(kmerMap::iterator it = outMap.begin(); it != outMap.end(); ++it){
    std::cout << it->first << " : { ";
    std::vector<int> indList = it->second;
    for(size_t i = 0; i < indList.size(); ++i){
      std::cout << indList[i] << " ";
    }
    std::cout << "}" << std::endl;
  }
  // ***
  // kmerMap outMap2 = text_to_kmer_map(T, P.size() / (mm + 1) + 1); // mm
  // std::cout << "text_to_kmer_map:" << std::endl;
  // for(kmerMap::iterator it = outMap2.begin(); it != outMap2.end(); ++it){
  //   std::cout << it->first << " : { ";
  //   std::vector<int> indList = it->second;
  //   for(size_t i = 0; i < indList.size(); ++i){
  //     std::cout << indList[i] << " ";
  //   }
  //   std::cout << "}" << std::endl;
  // }
  // ***
  std::vector<Seed> outPart = partitionPattern(P, (mm + 1)); // mm + 1
  std::cout << "Partition List:" << std::endl;
  for(size_t i = 0; i < outPart.size(); ++i){
    std::cout << "{ " << outPart[i].first << ", " << outPart[i].second << " }" << std::endl;
  }

  std::vector<int> output = approximate_search(fname, P, mm);

  std::cout << "Search results: " << std::endl;
  std::cout << "{ ";
  for(size_t i = 0; i < output.size(); ++i){
    std::cout  << output[i] << ", ";
  }
  std::cout << "}" << std::endl;

  


  return 0;
}
