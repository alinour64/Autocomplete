// Yusuf Pisan pisan@uw.edu
// 17 Jan 2021

// BST class
// Creates a BST to store values
// Uses Node which holds the data

#include "bstmap.h"
#include <cassert>
#include <memory>

using namespace std;

// copy constructor
BSTMap::BSTMap(const BSTMap &bst) {
  root = nullptr;
  if (bst.root != nullptr) {
    root = new Node{*bst.root};
    copy_helper(bst.root, root);
  }
}

void BSTMap::copy_helper(Node *original, Node *other) {
  if (original->left != nullptr) {
    other->left = new Node{*original->left};
    copy_helper(original->left, other->left);
  }
  if (original->right != nullptr) {
    other->right = new Node{*original->right};
    copy_helper(original->right, other->right);
  }
}

// given an array of length n
// create a tree to have all items in that array
// with the minimum height (uses same helper as rebalance)
BSTMap::BSTMap(const vector<value_type> &v) {
  // create a balanced tree from the input vector
  Node *newRoot = createBalancedTree(v, 0, static_cast<int>(v.size()) - 1);
  // swap the contents of this tree with the new tree
  swap(root, newRoot);
  // delete the old tree
  clear(newRoot);
}

// destructor
BSTMap::~BSTMap() { clear(); }

// delete all nodes in tree
void BSTMap::clear() {

  clear(root);
  root = nullptr;
}
void BSTMap::clear(Node *node) {
  if (node != nullptr) {
    clear(node->left);
    clear(node->right);
    delete node;
  }
}
// true if no nodes in BST
bool BSTMap::empty() const { return root == nullptr; }

// Number of nodes in BST
int BSTMap::size() const { return countNodes(root); }

int BSTMap::countNodes(const Node *curr) const {
  if (curr == nullptr) {
    return 0;
  }
  return 1 + countNodes(curr->left) + countNodes(curr->right);
}

// true if item is in BST
bool BSTMap::contains(const key_type &key) const {
  Node *curr = root;
  while (curr != nullptr) {
    if (curr->data.first == key) {
      return true;
    }
    if (key < curr->data.first) {
      curr = curr->left;
    } else {
      curr = curr->right;
    }
  }
  return false;
}

// If k matches the key returns a reference to its value
// If k does not match any key, inserts a new element
// with that key and returns a reference to its mapped value.
BSTMap::mapped_type &BSTMap::operator[](const key_type &k) {
  // Find the node with the given key or the position where it should be
  // inserted
  Node *curr = root;
  Node *parent = nullptr;
  while (curr != nullptr && curr->data.first != k) {
    parent = curr;
    if (k < curr->data.first) {
      curr = curr->left;
    } else {
      curr = curr->right;
    }
  }
  if (curr != nullptr) {
    // Key already exists, return a reference to its mapped value
    return curr->data.second;
  }
  // Key doesn't exist, insert a new node with the default value for the
  // mapped type
  Node *newNode = new Node{make_pair(k, mapped_type{}), nullptr, nullptr};
  if (parent == nullptr) {
    root = newNode;
  } else if (k < parent->data.first) {
    parent->left = newNode;
  } else {
    parent->right = newNode;
  }
  return newNode->data.second;
}

vector<BSTMap::value_type> BSTMap::getAll(const key_type &k) const {
  vector<value_type> v;
  Node *curr = root;
  while (curr != nullptr) {
    if (curr->data.first == k) {
      v.push_back(curr->data);
    }
    if (curr->data.first < k) {
      curr = curr->right;
    } else {
      curr = curr->left;
    }
  }
  return v;
}

// 0 if empty, 1 if only root, otherwise
// height of root is max height of subtrees + 1
int BSTMap::height() const { return getHeight(root); }

// height of a Node, nullptr is 0, root is 1, static, no access to 'this'
// helper function to height(), used by printVertical
int BSTMap::getHeight(const Node *n) {
  if (n == nullptr) {
    return 0;
  }
  int leftHeight = getHeight(n->left);
  int rightHeight = getHeight(n->right);
  return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// same as contains, but returns 1 or 0
// compatibility with std::map
size_t BSTMap::count(const string &k) const {
  if (contains(k)) {
    return 1;
  }
  return 0;
}

// inorder traversal: left-root-right
// takes a function that takes a single parameter of type T
void BSTMap::inorder(void visit(const value_type &item)) const {
  inorderHelper(root, visit);
}

void BSTMap::inorderHelper(
    const Node *curr, std::function<void(const value_type &)> visit) const {
  if (curr == nullptr) {
    return;
  }
  inorderHelper(curr->left, visit);
  visit(curr->data);
  inorderHelper(curr->right, visit);
}

// preorder traversal: root-left-right
void BSTMap::preorder(void visit(const value_type &item)) const {
  preorderHelper(root, visit);
}

void BSTMap::preorderHelper(const Node *curr,
                            void visit(const value_type &)) const {
  if (curr == nullptr) {
    return;
  }
  visit(curr->data);
  preorderHelper(curr->left, visit);
  preorderHelper(curr->right, visit);
}

// postorder traversal: left-right-root
void BSTMap::postorder(void visit(const value_type &item)) const {
  postorderHelper(root, visit);
}

void BSTMap::postorderHelper(const Node *curr,
                             void visit(const value_type &)) const {
  if (curr == nullptr) {
    return;
  }
  postorderHelper(curr->left, visit);
  postorderHelper(curr->right, visit);
  visit(curr->data);
}

// balance the BST by saving all nodes to a vector inorder
// and then recreating the BST from the vector
void BSTMap::rebalance() {
  // create a sorted copy of the nodes
  vector<value_type> sortedNodes;
  inorderHelper(root,
                [&](const value_type &item) { sortedNodes.push_back(item); });
  // create a balanced tree from the sorted nodes
  Node *newRoot = createBalancedTree(sortedNodes, 0,
                                     static_cast<int>(sortedNodes.size()) - 1);
  // delete the old tree
  clear();
  // assign the new tree to the root
  root = newRoot;
}

BSTMap::Node *BSTMap::createBalancedTree(const vector<value_type> &v, int start,
                                         int end) {
  if (start > end) {
    // base case: empty subtree
    return nullptr;
  }
  // find the middle element and make it the root
  int mid = (start + end) / 2;
  Node *root = new Node{v[mid], nullptr, nullptr};
  // recursively create left and right subtrees
  root->left = createBalancedTree(v, start, mid - 1);
  root->right = createBalancedTree(v, mid + 1, end);
  return root;
}

// trees are equal if they have the same structure
// AND the same item values at all the nodes
bool BSTMap::operator==(const BSTMap &other) const {
  // If the two trees' sizes are not equal, they are not equal
  if (size() != other.size()) {
    return false;
  }

  // If both trees are empty, they are equal
  if (empty() && other.empty()) {
    return true;
  }

  // Recursively compare the structures and data in each node
  return isEqual(root, other.root);
}

bool BSTMap::isEqual(Node *node1, Node *node2) const {
  // If both nodes are nullptr, they are equal
  if (node1 == nullptr && node2 == nullptr) {
    return true;
  }

  // If only one node is nullptr, they are not equal
  if (node1 == nullptr || node2 == nullptr) {
    return false;
  }

  // If the data in the nodes are not equal, they are not equal
  if (node1->data != node2->data) {
    return false;
  }

  // Recursively compare the left and right subtrees
  return isEqual(node1->left, node2->left) &&
         isEqual(node1->right, node2->right);
}

// not == to each other
bool BSTMap::operator!=(const BSTMap &other) const { return !(*this == other); }

bool BSTMap::erase(const key_type &k) {
  // find the node to erase
  Node **curr = &root;
  while (*curr != nullptr) {
    if ((*curr)->data.first == k) {
      break;
    }
    if ((*curr)->data.first > k) {
      curr = &((*curr)->left);
    } else {
      curr = &((*curr)->right);
    }
  }
  // key not found
  if (*curr == nullptr) {
    return false;
  }
  Node *toDelete = *curr;
  // case 1: node has no children
  if (toDelete->left == nullptr && toDelete->right == nullptr) {
    *curr = nullptr;
  }
  // case 2: node has one child
  else if (toDelete->left == nullptr) {
    *curr = toDelete->right;
  } else if (toDelete->right == nullptr) {
    *curr = toDelete->left;
  }
  // case 3: node has two children
  else {
    Node *minRight = toDelete->right;
    while (minRight->left != nullptr) {
      minRight = minRight->left;
    }
    toDelete->data = minRight->data;
    erase(minRight->data.first);
  }
  delete toDelete;
  return true;
}
