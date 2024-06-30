/**
 * @file edist.cpp
 * Code to build an edit distance matrix
 * and return an optimal edit string
 */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <map>
#include <algorithm>

#include "edist.h"

using namespace std;

int min(int a, int b, int c) {
    return min(a, min(b, c));
}

/**
 * Returns an edit distance matrix between strings X and Y [Dimensions (|X|+1) x |Y|+1)]
 *
 * @param X A std::string object holding the X string (edits with respect to X)
 * @param Y A std::string object holding the Y string (edits turn X into Y)
 *
 * @return An std::vector<std::vector<int>> (typedef eMatrix) storing the optimal edit
 *         distance between a length i substring of X and a length j substring of Y
 *         at position eMatrix[i][j].
 */
eMatrix buildEditMatrix(std::string x, std::string y){
  eMatrix outM;

  // YOUR CODE HERE
  // Some loose guidelines:
  // Dont forget that the first row / column are gaps
  // (You may need to adjust index or add a gap character)
  // Build an empty matrix of appropriate size
  // What entries can you calculate immediately?
  // Write a dynamic program to fill in the rest
    const int x_size = x.size() + 1;
    const int y_size = y.size() + 1;
    outM = vector<vector<int>>(x_size , vector<int> (y_size)); ;
    
    for (int i = 0; i < x_size; i ++ )
        for (int j = 0; j < y_size; j ++ ) {
            if (!i) outM[i][j] = j;
            else if (!j) outM[i][j] = i;
            else {
                if (x[i - 1] != y[j - 1] && i != j )
                    outM[i][j] = min(outM[i - 1][j] + 1 , outM[i][j - 1] + 1 , outM[i - 1][j - 1] + 1);
                if (x[i - 1] != y[j - 1] && i == j) 
                    outM[i][j] = min(outM[i - 1][j] + 1 , outM[i][j - 1] + 1 , outM[i - 1][j - 1] + 1);
                if (x[i - 1] == y[j - 1] && i != j)
                    outM[i][j] = min(outM[i - 1][j] + 1 , outM[i][j - 1] + 1 , outM[i - 1][j - 1]);
                if (x[i - 1] == y[j - 1] && i == j)
                    outM[i][j] = min(outM[i - 1][j] + 1 , outM[i][j - 1] + 1 , outM[i - 1][j - 1]);
            }
        }
  return outM;
}

/**
 * Returns the edit string between strings X and Y
 *
 * @param X A std::string object holding the X string (edits with respect to X)
 * @param Y A std::string object holding the Y string (edits turn X into Y)
 *
 * @return An std::string storing an optimal edit string
 *
 * WARNING: There are often multiple possible optimal strings. You MUST use the provided 
 *          'greedy' logic to produce the same optimal string as the autograder.
 *
 *          That is to say, you must prioritize M/R, followed by D, followed by I when
 *          there are multiple possible edit strings. (Remember you build backwards)
 */
std::string buildEditString(std::string x, std::string y){
  eMatrix myM = buildEditMatrix(x,y);
  std::string es = "";

  // your code here
  int x_ = x.size();
  int y_ = y.size();

  while (x_ != 0 && y_ != 0) {
    int min_ = min(myM[x_ - 1][y_], myM[x_][y_ - 1], myM[x_ - 1][y_ - 1]);
    if (myM[x_ - 1][y_ - 1] == min_ || x[x_ - 1] == y[y_ - 1]) {
      if (myM[x_][y_] != myM[x_ - 1][y_ - 1]) 
        es = 'R' + es;
      else es = 'M' + es;
      x_ -= 1;
      y_ -= 1;
    } else if (myM[x_ - 1][y_] == min_) {
      es = 'D' + es;
      x_ -= 1;
    } else if (myM[x_][y_ - 1] == min_){
      es = 'I' + es;
      y_ -= 1;
    }
  }
  while (x_ --) es = 'D' + es;
  while (y_ --) es = 'I' + es;

  return es;
}