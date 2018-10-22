#include <vector>
#include <string>
#include <iostream>
#include "Trie.h"

namespace TI {

namespace Trie {


TrieNode *getNode(const int numberChildren) { 
  /*
  TrieNode* children[numberChildren];
  for (int child = 0; child < numberChildren; ++child) {
    children[child] = nullptr;
  }
  */

  TrieNode *pNode =  new TrieNode;
  pNode->isEndOfWord = false; 

  for (int i = 0; i < 48; i++) 
    pNode->children[i] = nullptr; 
  
  return pNode; 
} 
  

void insert(struct TrieNode *root, std::vector<int> key) { 
  struct TrieNode *pCrawl = root;
  
  for (int i = 0; i < key.size(); ++i) { 
    int index = key[i];
    std::cout << key[i] << std::endl;
    std::cout << pCrawl->children[index] << std::endl;
    if (pCrawl->children[index] == nullptr)
      pCrawl->children[index] = getNode(key.size());

    pCrawl = pCrawl->children[index]; 
  } 

  // mark last node as leaf 
  pCrawl->isEndOfWord = true; 
} 
  

bool search(struct TrieNode *root, std::vector<int> key) { 
  struct TrieNode *pCrawl = root; 

  for (int i = 0; i < key.size(); ++i) { 
    int index = key[i]; 
    if (pCrawl->children[index] == nullptr) 
        return false;

    pCrawl = pCrawl->children[index]; 
  }

  return (pCrawl != nullptr && pCrawl->isEndOfWord); 
}


} // namespace Trie
	

} // namespace TI
