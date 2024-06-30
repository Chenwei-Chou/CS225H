/**
 * @file main.cpp
 * A simple C++ program for building an edit distance matrix
 * and returning an optimal edit string
 */

#include <string>
#include <iostream>
#include <vector>
#include <map>

#include "edist.h"

int main() {


  std::cout << "example 1" << std::endl;

  std::string X = "CAT";
  std::string Y = "CAAT";

  eMatrix out = buildEditMatrix(X,Y);

  std::cout << "{ ";
  for (size_t i = 0; i < out.size(); ++i){
    std::cout << "{ ";
    for(size_t j = 0; j < out[i].size()-1; ++j){
      std::cout << out[i][j] << ", ";
    }
    std::cout << out[i][out[i].size()-1] << "}, \\" << std::endl;
  }
  std::cout << "}" << std::endl;
  
  std::cout << buildEditString(X,Y) << std::endl;
  return 0;
}
