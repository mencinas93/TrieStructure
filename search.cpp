//
//  Search.cpp
//  ProjectMain
//
//  Created by Michael Encinas on 2/21/23.
//

#include "search.hpp"


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
#include <unistd.h> // for getcwd()

//const int Alphabet_Size = 26;
const int ASCII_Size = 128;

struct TrieNode {
    TrieNode* children[ASCII_Size];
   // char letter;
    bool EndOfWord;
};

struct TrieNode* getNode(){
    struct TrieNode* PointerNode = new TrieNode;
    PointerNode-> EndOfWord = false;
    for (int i = 0; i < ASCII_Size; i++){
        PointerNode->children[i] = NULL;
    }
    return PointerNode;
}

void insert(struct TrieNode *Treeroot, string key) {
    struct TrieNode *pTraverse = Treeroot;
    for (int i = 0; i < key.length(); i++) {
        int index = (int)key[i];
        if (index < 0 || index >= ASCII_Size) {
            cerr << "Error: invalid index " << index << " for character " << key[i] << endl;
            return;
        }
        if (!pTraverse->children[index]) {
            struct TrieNode* childNode = getNode();
            if (!childNode) {
                cerr << "Error: failed to allocate memory for child node\n";
                return;
            }
            pTraverse->children[index] = childNode;
        }
        pTraverse = pTraverse->children[index];
    }
    pTraverse->EndOfWord = true;
}
bool search(struct TrieNode *TreeRoot, string key)
{
    struct TrieNode *pTraverse = TreeRoot;
    for (int i = 0; i < key.length(); i++){
        int index = (int)key[i];
        if (!pTraverse-> children[index])
            return false;
        pTraverse = pTraverse-> children[index];
    }
    return (pTraverse-> EndOfWord);
}

bool isLastNode(struct TrieNode* Treeroot)
{
    for (int i = 0; i < ASCII_Size; i++)
        if (Treeroot->children[i])
            return 0;
    return 1;
}
 
// Recursive function to print auto-suggestions for given
// node.
void suggestionsRec(struct TrieNode* root,
                    string currPrefix)
{
    // found a string in Trie with the given prefix
    if (root->EndOfWord)
        cout << currPrefix << endl;
 
    for (int i = 0; i < ASCII_Size; i++)
        if (root->children[i]) {
            // child node character value
            char child = i;
            suggestionsRec(root->children[i],
                           currPrefix + child);
        }
}
 
// print suggestions for given query prefix.
int printAutoSuggestions(TrieNode* Treeroot, const string query)
{
    struct TrieNode* pCrawl = Treeroot;
    for (char c : query) {
        int index = (int)c;
 
        // no string in the Trie has this prefix
        if (!pCrawl->children[index])
            return 0;
 
        pCrawl = pCrawl->children[index];
    }
    // If prefix is present as a word, but
    // there is no subtree below the last
    // matching node.
    if (isLastNode(pCrawl)) {
        cout << query << endl;
        return -1;
    }
    suggestionsRec(pCrawl, query);
    return 1;
}

