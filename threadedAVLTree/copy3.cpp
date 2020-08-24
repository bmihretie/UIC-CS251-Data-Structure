/*test.cpp*/

//
// An AVL unit test based on Catch framework
// By Birhanu Mihretie
// NetId: bmihre2
//

#include <iostream>
#include <vector>
#include <algorithm>

#include "avlt.h"

#include "catch.hpp"

using namespace std;

// //test case for empty tree
// TEST_CASE("(1) empty tree")
// {
//   avlt<int, int>  tree;

//   REQUIRE(tree.size() == 0);
//   REQUIRE(tree.height() == -1);
// } // end of tes case 1


//test case at the root to the left with 3 nodes
TEST_CASE("(2) case 1 at the root to the left with 3 nodes")
{
  avlt<int, int>  tree;

  vector<int> keys = {100, 120, 80,60, 40,20};
  vector<int> heights = { 1, 0, 0,2,1,0};

  for (int key : keys)
  {
    tree.insert(key, -key);
  }

  //
  // size and height?  after rebalance should be 1:
  //
  REQUIRE(tree.size() == keys.size());

  auto maxH = std::max_element(heights.begin(), heights.end());
  REQUIRE(tree.height() == *maxH);
  // 
  // values inserted?
  //
  int value;

  for (int key : keys)
  {
    REQUIRE(tree.search(key, value));
    REQUIRE(value == -key);
  }

  //
  // heights correct after rebalance?
  //
  for (size_t i = 0; i < keys.size(); ++i)
  {
    REQUIRE((tree % keys[i]) == heights[i]);
  }
	
} // end of test 2

