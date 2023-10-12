#ifndef AUTOCOMPLETE_H
#define AUTOCOMPLETE_H

#include "bstmap.h"

using namespace std;

class Autocomplete {
public:
  Autocomplete() = default;
  void readFile(const string &fileName);
  vector<BSTMap::value_type> complete(const string &prefix) const;

private:
  // BST of phrases and their frequency
  BSTMap phrases;

  // sorter
  bool static sortByWeight(BSTMap::value_type &a, BSTMap::value_type &b);

  void traverseAndComplete(const BSTMap::Node* node, const string &prefix, vector<BSTMap::value_type>& results) const;

};

#endif // AUTOCOMPLETE_H
