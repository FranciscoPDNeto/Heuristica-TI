#include <vector>

namespace TI {

namespace Trie {


// Trie node
struct TrieNode {
  TrieNode* children[48];

  // isEndOfWord is true if the node
  // represents end of a word
  bool isEndOfWord;
};


// Returns new trie node (initialized to NULLs)
TrieNode *getNode(const int numberChildren);
// If not present, inserts key into trie 
// If the key is prefix of trie node, just 
// marks leaf node 
void insert(struct TrieNode *root, std::vector<int> key);
// Returns true if key presents in trie, else 
// false 
bool search(struct TrieNode *root, std::vector<int> key);

}

}