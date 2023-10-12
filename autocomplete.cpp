#include "autocomplete.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

void testBSTAll();

void Autocomplete::readFile(const string &fileName) {
  ifstream ifs(fileName);
  if (!ifs.is_open()) {
    cerr << "Error opening file: " << fileName << endl;
    return;
  }

  // Read the first line to get the number of records and ignore it
  string firstLine;
  getline(ifs, firstLine);

  string line;
  while (getline(ifs, line)) {
    stringstream ss(line);
    int population;
    string cityName;
    string regionName;
    string countryName;

    ss >> population;
    ss.ignore(); // ignore empty spaces

    // Check if the line contains a comma (city format)
    if (line.find(',') != string::npos) {
      getline(ss, cityName, ',');
      ss.ignore(); // ignore empty spaces
      getline(ss, regionName, ',');
      ss.ignore(); // ignore empty spaces
      getline(ss, countryName);

      // create the full location string
      cityName = cityName + ", " + regionName + ", " + countryName;
    } else {
      // No comma, read the remaining part of the line as the city name
      getline(ss, cityName);
    }

    // add the city/phrase to the phrases BST with its population as the weight
    phrases[cityName] = population;
  }

  ifs.close();
  phrases.rebalance();
}

// Function to sort the results by weight (frequency) in descending order
bool Autocomplete::sortByWeight(BSTMap::value_type &a, BSTMap::value_type &b) {
  return a.second > b.second;
}

// Function to find all the phrases in the BST that start with a given prefix
vector<BSTMap::value_type> Autocomplete::complete(const string &prefix) const {
  // If the prefix is empty, return an empty vector
  if (prefix.empty()) {
    return vector<BSTMap::value_type>();
  }

  // Convert the prefix to lowercase
  string lowerCasePrefix = prefix;
  transform(lowerCasePrefix.begin(), lowerCasePrefix.end(),
            lowerCasePrefix.begin(), ::tolower);

  // Prepare a vector to store the results
  vector<BSTMap::value_type> results;

  // Traverse the BST and collect phrases that start with the prefix
  traverseAndComplete(phrases.root, lowerCasePrefix, results);

  // Sort the results by weight (frequency) in descending order
  sort(results.begin(), results.end(), sortByWeight);

  // Return the results
  return results;
}

// Recursive function to traverse the BST and collect phrases that start with a
// given prefix
void Autocomplete::traverseAndComplete(
    const BSTMap::Node *node, const string &prefix,
    vector<BSTMap::value_type> &results) const {
  // If the node is nullptr, return immediately
  if (node == nullptr) {
    return;
  }

  // Traverse the left subtree
  traverseAndComplete(node->left, prefix, results);

  // Convert the current node's data to lowercase
  string lowerCaseData = node->data.first;
  transform(lowerCaseData.begin(), lowerCaseData.end(), lowerCaseData.begin(),
            ::tolower);

  // If the current node's data starts with the prefix, add it to the results
  if (lowerCaseData.compare(0, prefix.size(), prefix) == 0) {
    results.push_back(node->data);
  }

  // Traverse the right subtree
  traverseAndComplete(node->right, prefix, results);
}
