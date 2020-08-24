#include <iostream>
#include <vector>

#include "bstt.h"

#include "catch.hpp"

using namespace std;


TEST_CASE("(2) empty tree") 
{
  bstt<int, int>  tree;
  //int key;
  tree.insert(90,3);
  REQUIRE(tree[90] == 3);

  //REQUIRE(tree.size() == 0);
}