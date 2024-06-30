#include <catch2/catch_test_macros.hpp>

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include "edist.h"

/*
* Helper functions for basic tests
*/

using namespace std;

void matchString(std::string output, std::string ans){

  REQUIRE(output.size() == ans.size());

  for(size_t i = 0; i < ans.size(); ++i){
    if(output[i]!=ans[i]){ 
      INFO("At index value: " + std::to_string(i) + " your string was incorrect.");
      REQUIRE(output[i] == ans[i]);
    }
  }
}

void matchSarray(std::vector<int> output, std::vector<int> ans){

  REQUIRE(output.size() == ans.size());

  for(size_t i = 0; i < ans.size(); ++i){
    if(output[i]!=ans[i]){ 
      INFO("At index value: " + std::to_string(i) + " your array was incorrect.");
      REQUIRE(output[i] == ans[i]);
    }
  }
}

void matchSortArray(std::vector<int> output, std::vector<int> ans){
  std::sort(output.begin(),output.end()); 
  std::sort(ans.begin(),ans.end()); 

  REQUIRE(output.size() == ans.size());

  for(size_t i = 0; i < ans.size(); ++i){
    if(output[i]!=ans[i]){ 
      INFO("At index value: " + std::to_string(i) + " your array (when sorted) was incorrect.");
      REQUIRE(output[i] == ans[i]);
    }
  }
}

void match_2D_Array(std::vector<std::vector<int>> output, std::vector<std::vector<int>> ans){
  REQUIRE(output.size() == ans.size());

  for(int i = 0; i < (int) ans.size(); ++i){
    REQUIRE(output[i].size() == ans[i].size());

    for(int j = 0; j < (int) ans[i].size(); ++j){
      if(output[i][j]!=ans[i][j]){ 
        INFO("At vector[" + std::to_string(i) + "]["+ std::to_string(j) +"] your value was incorrect.");
        REQUIRE(output[i][j] == ans[i][j]);
      }
    }
  }
}

/*
* Public test cases for editMatrix (Total 25 points / weight 25)
*/

TEST_CASE("editMatrix Public 1", "[weight=5]") {
  std::string X = "BABAAAB";
  std::string Y = "BBAABAB";
  eMatrix ans { { 0, 1, 2, 3, 4, 5, 6, 7}, \
{ 1, 0, 1, 2, 3, 4, 5, 6}, \
{ 2, 1, 1, 1, 2, 3, 4, 5}, \
{ 3, 2, 1, 2, 2, 2, 3, 4}, \
{ 4, 3, 2, 1, 2, 3, 2, 3}, \
{ 5, 4, 3, 2, 1, 2, 3, 3}, \
{ 6, 5, 4, 3, 2, 2, 2, 3}, \
{ 7, 6, 5, 4, 3, 2, 3, 2} };

  eMatrix outM = buildEditMatrix(X,Y);

  match_2D_Array(outM,ans);

}

TEST_CASE("editMatrix Public 2", "[weight=5]") {
  std::string X = "these strings can be anything";
  std::string Y = "including small things";
  eMatrix ans { { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22}, \
{ 1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 16, 17, 18, 19, 20, 21}, \
{ 2, 2, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 16, 17, 18, 19, 20}, \
{ 3, 3, 3, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 17, 17, 18, 19, 20}, \
{ 4, 4, 4, 4, 4, 5, 6, 7, 8, 9, 10, 10, 11, 12, 13, 14, 15, 16, 17, 18, 18, 19, 19}, \
{ 5, 5, 5, 5, 5, 5, 6, 7, 8, 9, 10, 11, 11, 12, 13, 14, 15, 16, 17, 18, 19, 19, 20}, \
{ 6, 6, 6, 6, 6, 6, 6, 7, 8, 9, 9, 10, 11, 12, 13, 14, 14, 15, 16, 17, 18, 19, 20}, \
{ 7, 7, 7, 7, 7, 7, 7, 7, 8, 9, 10, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 19}, \
{ 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 10, 10, 10, 11, 12, 13, 14, 14, 15, 16, 17, 18, 19}, \
{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 10, 11, 11, 11, 12, 13, 14, 15, 15, 16, 17, 18, 19}, \
{ 10, 9, 10, 10, 10, 10, 10, 9, 10, 10, 10, 11, 12, 12, 12, 13, 14, 15, 16, 15, 16, 17, 18}, \
{ 11, 10, 9, 10, 11, 11, 11, 10, 9, 10, 11, 11, 12, 13, 13, 13, 14, 15, 16, 16, 15, 16, 17}, \
{ 12, 11, 10, 10, 11, 12, 12, 11, 10, 9, 10, 11, 12, 13, 14, 14, 14, 15, 16, 17, 16, 15, 16}, \
{ 13, 12, 11, 11, 11, 12, 13, 12, 11, 10, 10, 10, 11, 12, 13, 14, 15, 15, 16, 17, 17, 16, 15}, \
{ 14, 13, 12, 12, 12, 12, 13, 13, 12, 11, 10, 11, 11, 12, 13, 14, 14, 15, 16, 17, 18, 17, 16}, \
{ 15, 14, 13, 12, 13, 13, 13, 14, 13, 12, 11, 11, 12, 12, 13, 14, 15, 15, 16, 17, 18, 18, 17}, \
{ 16, 15, 14, 13, 13, 14, 14, 14, 14, 13, 12, 12, 12, 12, 13, 14, 15, 16, 16, 17, 18, 19, 18}, \
{ 17, 16, 15, 14, 14, 14, 15, 15, 14, 14, 13, 13, 13, 13, 13, 14, 15, 16, 17, 17, 17, 18, 19}, \
{ 18, 17, 16, 15, 15, 15, 15, 16, 15, 15, 14, 14, 14, 14, 14, 14, 14, 15, 16, 17, 18, 18, 19}, \
{ 19, 18, 17, 16, 16, 16, 16, 16, 16, 16, 15, 15, 15, 15, 15, 15, 15, 15, 16, 17, 18, 19, 19}, \
{ 20, 19, 18, 17, 17, 17, 17, 17, 17, 17, 16, 16, 16, 16, 16, 16, 16, 16, 16, 17, 18, 19, 20}, \
{ 21, 20, 19, 18, 18, 18, 18, 18, 18, 18, 17, 17, 17, 17, 17, 17, 16, 17, 17, 17, 18, 19, 20}, \
{ 22, 21, 20, 19, 19, 19, 19, 19, 19, 19, 18, 18, 18, 17, 18, 18, 17, 17, 18, 18, 18, 19, 20}, \
{ 23, 22, 21, 20, 20, 20, 20, 20, 19, 20, 19, 19, 19, 18, 18, 19, 18, 18, 18, 19, 18, 19, 20}, \
{ 24, 23, 22, 21, 21, 21, 21, 21, 20, 20, 20, 20, 20, 19, 19, 19, 19, 19, 19, 19, 19, 19, 20}, \
{ 25, 24, 23, 22, 22, 22, 22, 22, 21, 21, 21, 21, 21, 20, 20, 20, 20, 19, 20, 20, 20, 20, 20}, \
{ 26, 25, 24, 23, 23, 23, 23, 23, 22, 22, 22, 22, 22, 21, 21, 21, 21, 20, 19, 20, 21, 21, 21}, \
{ 27, 26, 25, 24, 24, 24, 24, 23, 23, 23, 23, 23, 23, 22, 22, 22, 22, 21, 20, 19, 20, 21, 22}, \
{ 28, 27, 26, 25, 25, 25, 25, 24, 23, 24, 24, 24, 24, 23, 23, 23, 23, 22, 21, 20, 19, 20, 21}, \
{ 29, 28, 27, 26, 26, 26, 26, 25, 24, 23, 24, 25, 25, 24, 24, 24, 24, 23, 22, 21, 20, 19, 20} };

  eMatrix outM = buildEditMatrix(X,Y);

  match_2D_Array(outM,ans);

}

TEST_CASE("editMatrix Public 3", "[weight=5]") {
  std::string X = "tinyX";
  std::string Y = "biiiiiiiiiitinyXiiiiigY";
  eMatrix ans { { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23}, \
{ 1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22}, \
{ 2, 2, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21}, \
{ 3, 3, 2, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}, \
{ 4, 4, 3, 3, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 12, 11, 12, 13, 14, 15, 16, 17, 18, 19}, \
{ 5, 5, 4, 4, 4, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 12, 11, 12, 13, 14, 15, 16, 17, 18}};

  eMatrix outM = buildEditMatrix(X,Y);

  match_2D_Array(outM,ans);

}

TEST_CASE("editMatrix Public 4", "[weight=5]") {
  std::string X = "beep beep ima sheep";
  std::string Y = "meep meep lima deep";
  eMatrix ans { { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19}, \
{ 1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19}, \
{ 2, 2, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}, \
{ 3, 3, 2, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17}, \
{ 4, 4, 3, 2, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}, \
{ 5, 5, 4, 3, 2, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}, \
{ 6, 6, 5, 4, 3, 2, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}, \
{ 7, 7, 6, 5, 4, 3, 3, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}, \
{ 8, 8, 7, 6, 5, 4, 4, 3, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13}, \
{ 9, 9, 8, 7, 6, 5, 5, 4, 3, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}, \
{ 10, 10, 9, 8, 7, 6, 6, 5, 4, 3, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}, \
{ 11, 11, 10, 9, 8, 7, 7, 6, 5, 4, 3, 3, 3, 4, 5, 6, 7, 8, 9, 10}, \
{ 12, 11, 11, 10, 9, 8, 7, 7, 6, 5, 4, 4, 4, 3, 4, 5, 6, 7, 8, 9}, \
{ 13, 12, 12, 11, 10, 9, 8, 8, 7, 6, 5, 5, 5, 4, 3, 4, 5, 6, 7, 8}, \
{ 14, 13, 13, 12, 11, 10, 9, 9, 8, 7, 6, 6, 6, 5, 4, 3, 4, 5, 6, 7}, \
{ 15, 14, 14, 13, 12, 11, 10, 10, 9, 8, 7, 7, 7, 6, 5, 4, 4, 5, 6, 7}, \
{ 16, 15, 15, 14, 13, 12, 11, 11, 10, 9, 8, 8, 8, 7, 6, 5, 5, 5, 6, 7}, \
{ 17, 16, 15, 15, 14, 13, 12, 11, 11, 10, 9, 9, 9, 8, 7, 6, 6, 5, 5, 6}, \
{ 18, 17, 16, 15, 15, 14, 13, 12, 11, 11, 10, 10, 10, 9, 8, 7, 7, 6, 5, 6}, \
{ 19, 18, 17, 16, 15, 15, 14, 13, 12, 11, 11, 11, 11, 10, 9, 8, 8, 7, 6, 5} };

  eMatrix outM = buildEditMatrix(X,Y);

  match_2D_Array(outM,ans);

}

TEST_CASE("editMatrix Public 5", "[weight=5]") {
  std::string X = "AAAAAAAA";
  std::string Y = "BBBAAAAAAAAA";
  eMatrix ans { { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}, \
{ 1, 1, 2, 3, 3, 4, 5, 6, 7, 8, 9, 10, 11}, \
{ 2, 2, 2, 3, 3, 3, 4, 5, 6, 7, 8, 9, 10}, \
{ 3, 3, 3, 3, 3, 3, 3, 4, 5, 6, 7, 8, 9}, \
{ 4, 4, 4, 4, 3, 3, 3, 3, 4, 5, 6, 7, 8}, \
{ 5, 5, 5, 5, 4, 3, 3, 3, 3, 4, 5, 6, 7}, \
{ 6, 6, 6, 6, 5, 4, 3, 3, 3, 3, 4, 5, 6}, \
{ 7, 7, 7, 7, 6, 5, 4, 3, 3, 3, 3, 4, 5}, \
{ 8, 8, 8, 8, 7, 6, 5, 4, 3, 3, 3, 3, 4} };

  eMatrix outM = buildEditMatrix(X,Y);

  match_2D_Array(outM,ans);
}

/*
* Public test cases for editString (Total 25 points / weight 25)
*/

TEST_CASE("editString Public 1", "[weight=5]") {
  std::string X = "BABAAAB";
  std::string Y = "BBAABAB";
  std::string ans = "MDMMMIMM";

  std::string out = buildEditString(X,Y);

  matchString(out,ans);

}

TEST_CASE("editString Public 2", "[weight=5]") {
  std::string X = "these strings can be anything";
  std::string Y = "including small things";
  std::string ans = "DDDRRRRRRMMMDMDRRRRRMDDDMMMMMI";

  std::string out = buildEditString(X,Y);

  // cout << "[test] out: " << out << endl;
  // cout << "[test] ans: " << ans << endl;

  matchString(out,ans);

}

TEST_CASE("editString Public 3", "[weight=5]") {
  std::string X = "tinyX";
  std::string Y = "biiiiiiiiiitinyXiiiiigY";
  std::string ans = "IIIIIIIIIIIMMMMMIIIIIII";

  std::string out = buildEditString(X,Y);

  // cout << "[test] out: " << out << endl;
  // cout << "[test] ans: " << ans << endl;

  matchString(out,ans);

}

TEST_CASE("editString Public 4", "[weight=5]") {
  std::string X = "beep beep ima sheep";
  std::string Y = "meep meep lima deep";
  std::string ans = "RMMMMRMMMMIMMMMDRMMM";

  std::string out = buildEditString(X,Y);

  matchString(out,ans);

}

TEST_CASE("editString Public 5", "[weight=5]") {
  std::string X = "AAAAAAAA";
  std::string Y = "BBBAAAAAAAAA";
  std::string ans = "IIIIMMMMMMMM";

  std::string out = buildEditString(X,Y);

  // cout << "[test] out: " << out << endl;
  // cout << "[test] ans: " << ans << endl;

  matchString(out,ans);
}