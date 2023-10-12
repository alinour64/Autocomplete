// /**
//  * Testing BST - Binary Search Tree functions
//  *
//  * This file has series of tests for BST
//  * Each test is independent and uses assert statements
//  * Test functions are of the form
//  *
//  *      test_netidXX()
//  *
//  * where netid is UW netid and XX is the test number starting from 01
//  *
//  * Test functions can only use the public functions from BST
//  * testBSTAll() is called from main in main.cpp
//  * testBSTAll calls all other functions
//  * @author Multiple
//  * @date ongoing
//  */

#include "bstmap.h"
#include <algorithm>
#include <cassert>
#include <cctype>
#include <sstream>

using namespace std;

// global value for testing
// NOLINTNEXTLINE
stringstream globalSS;

// need to reset SS before calling this
void printer(const BSTMap::value_type &p) {
  globalSS << "[" << p.first << "=" << p.second << "]";
}

// // Testing == and []
void test01() {
  cout << "Starting test01" << endl;
  cout << "* Testing ==, !=, [] and copy constructor" << endl;
  BSTMap b1;
  auto val = b1["hello"];
  assert(val == 0);
  b1["hello"] = 5;
  val = b1["hello"];
  assert(val == 5);
  b1["world"] = 42;

  BSTMap b2;
  assert(b1 != b2);
  b2["hello"] = 5;
  b2["world"] = 42;
  assert(b1 == b2);

  BSTMap b3(b2);
  assert(b1 == b3);
  cout << "Ending tes01" << endl;
}

// Testing traversal
void test02() {
  cout << "Starting test02" << endl;
  cout << "* Testing traversal" << endl;
  BSTMap b;
  b["x"] = 10;
  b["f"] = 5;
  b["b"] = 3;
  b["e"] = 4;
  b["z"] = 50;
  // cout << b;

  globalSS.str("");
  b.inorder(printer);
  string order = globalSS.str();
  assert(order == "[b=3][e=4][f=5][x=10][z=50]");

  globalSS.str("");
  b.preorder(printer);
  order = globalSS.str();
  assert(order == "[x=10][f=5][b=3][e=4][z=50]");

  globalSS.str("");
  b.postorder(printer);
  order = globalSS.str();
  assert(order == "[e=4][b=3][f=5][z=50][x=10]");
  cout << "Ending test02" << endl;
}

// Testing rebalance
void test03() {
  cout << "Starting test03" << endl;
  cout << "* Testing rebalance" << endl;
  BSTMap b;
  b["1"] = 1;
  b["2"] = 2;
  b["3"] = 3;
  b["4"] = 4;
  b["5"] = 5;
  b["6"] = 6;
  assert(b.height() == 6);
  // cout << b << endl;
  b.rebalance();
  assert(b.height() == 3);
  // cout << b << endl;
  b.clear();
  assert(b.height() == 0);
  cout << "Ending test03" << endl;
}

void test04() {
  cout << "Starting test04" << endl;
  cout << "* Testing insertion and removal" << endl;
  BSTMap b;
  b["a"] = 1;
  b["b"] = 2;
  b["c"] = 3;
  b["d"] = 4;
  b["e"] = 5;

  assert(b.size() == 5);
  assert(b["a"] == 1);
  assert(b["b"] == 2);
  assert(b["c"] == 3);
  assert(b["d"] == 4);
  assert(b["e"] == 5);

  b.erase("a");
  b.erase("b");
  assert(b.size() == 3);
  assert(!b.contains("a"));
  assert(!b.contains("b"));
  cout << "Ending test04" << endl;
}

void test05() {
  cout << "Starting test05" << endl;
  cout << "* Testing empty() and size() functions" << endl;
  BSTMap b;
  assert(b.empty());
  assert(b.empty());

  b["a"] = 1;
  b["b"] = 2;
  b["c"] = 3;

  assert(!b.empty());
  assert(b.size() == 3);

  b.clear();
  assert(b.empty());
  assert(b.empty());
  cout << "Ending test05" << endl;
}

void test06() {
  cout << "Starting test06" << endl;
  cout << "* Testing contains() function" << endl;
  BSTMap b;
  b["a"] = 1;
  b["b"] = 2;
  b["c"] = 3;

  assert(b.contains("a"));
  assert(b.contains("b"));
  assert(b.contains("c"));
  assert(!b.contains("d"));
  assert(!b.contains("e"));

  b.erase("a");
  assert(!b.contains("a"));
  cout << "Ending test06" << endl;
}

void test07() {
  cout << "Starting test07" << endl;
  cout << "* Testing clear() function" << endl;
  BSTMap b;
  b["a"] = 1;
  b["b"] = 2;
  b["c"] = 3;
  b["d"] = 4;
  b["e"] = 5;

  b.clear();
  assert(b.empty());
  assert(b.empty());
  cout << "Ending test07" << endl;
}

void test08() {
  cout << "Starting test08" << endl;
  cout << "* Testing getAll() function" << endl;
  BSTMap b;
  b["a"] = 1;
  b["b"] = 2;
  b["c"] = 3;

  auto result = b.getAll("a");
  assert(result.size() == 1);
  assert(result[0].first == "a");
  assert(result[0].second == 1);

  result = b.getAll("d");
  assert(result.empty());
  cout << "Ending test08" << endl;
}

void test09() {
  cout << "Starting test09" << endl;
  cout << "* Testing count() function" << endl;
  BSTMap b;
  b["a"] = 1;
  b["b"] = 2;
  b["c"] = 3;

  assert(b.count("a") == 1);
  assert(b.count("d") == 0);
  cout << "Ending test09" << endl;
}

void test10() {
  cout << "Starting test10" << endl;
  cout << "* Testing BSTMap(const vector<value_type> &v) constructor" << endl;

  vector<BSTMap::value_type> v = {
      {"a", 1}, {"b", 2}, {"c", 3}, {"d", 4}, {"e", 5}};
  BSTMap b(v);

  assert(b.size() == 5);
  assert(b["a"] == 1);
  assert(b["b"] == 2);
  assert(b["c"] == 3);
  assert(b["d"] == 4);
  assert(b["e"] == 5);

  cout << "Ending test10" << endl;
}

// // Calling all test functions
void testBSTAll() {
  test01();
  test02();
  test03();
  // TODO(student) Add more tests
  test04();
  test05();
  test06();
  test07();
  test08();
  test09();
  test10();
}