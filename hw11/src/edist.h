/**
 * @file edist.h
 * Header file for edit distance based alignment
 */

#pragma once

#include <string>
#include <vector>
#include <map>


// Type definitions used in this assignment
typedef std::vector<std::vector<int>> eMatrix;

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
eMatrix buildEditMatrix(std::string x, std::string y);

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
 */
std::string buildEditString(std::string x, std::string y);