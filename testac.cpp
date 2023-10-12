#include "autocomplete.h"
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void testAC01() {
  cout << "Starting AC test01" << endl;
  cout << "* Testing basic autocomplete" << endl;
  Autocomplete ac;
  ac.readFile("small.txt");
  auto v = ac.complete("hel");
  assert(v.size() == 2);
  assert(v[0].first == "help");
  assert(v[0].second == 20);
  assert(v[1].first == "hello");
  assert(v[1].second == 10);
  cout << "Ending tesAC01" << endl;
}

void testAC02() {
  cout << "Starting AC test02" << endl;
  cout << "* Testing cities autocomplete" << endl;
  Autocomplete ac;
  ac.readFile("cities.txt");
  auto v = ac.complete("Sea");
  assert(v.size() == 47);
  assert(v[0].first == "Seattle, Washington, United States");
  assert(v[0].second == 608660);
  assert(v[46].first == "Seabeck, Washington, United States");
  assert(v[46].second == 1105);
  cout << "Ending tesAC02" << endl;
}

void testAC03() {
  cout << "Starting AC test03" << endl;
  cout << "* Testing case sensitivity" << endl;
  Autocomplete ac;
  ac.readFile("small.txt");
  auto v = ac.complete("Hel");
  assert(v.size() == 2);
  assert(v[0].first == "help");
  assert(v[0].second == 20);
  assert(v[1].first == "hello");
  assert(v[1].second == 10);
  cout << "Ending testAC03" << endl;
}

void testAC04() {
  cout << "Starting AC test04" << endl;
  cout << "* Testing no match found" << endl;
  Autocomplete ac;
  ac.readFile("small.txt");
  auto v = ac.complete("xyz");
  assert(v.empty());
  cout << "Ending testAC04" << endl;
}

void testAC05() {
  cout << "Starting AC test05" << endl;
  cout << "* Testing empty string input" << endl;
  Autocomplete ac;
  ac.readFile("small.txt");
  auto v = ac.complete("");
  assert(v.empty());
  cout << "Ending testAC05" << endl;
}

void testAC06() {
  cout << "Starting AC test06" << endl;
  cout << "* Testing invalid file name" << endl;
  Autocomplete ac;
  try {
    ac.readFile("non_existent_file.txt");
  } catch (const std::runtime_error &e) {
    assert(string(e.what()) == "Unable to open file: non_existent_file.txt");
  }
  auto v = ac.complete("hel");
  assert(v.empty());
  cout << "Ending testAC06" << endl;
}

// // Calling all test functions
void testACAll() {
  testAC01();
  testAC02();
  // TODO(student) Add more tests
  testAC03();
  testAC04();
  testAC05();
  testAC06();
}