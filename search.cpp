

#include "search.hpp"


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
#include <unistd.h> // for getcwd()

const int ASCII_Size = 128;

struct TrieNode {
    TrieNode* children[ASCII_Size];
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
 

void suggestionsRec(struct TrieNode* root,
                    string currPrefix)
{
    if (root->EndOfWord)
        cout << currPrefix << endl;
 
    for (int i = 0; i < ASCII_Size; i++)
        if (root->children[i]) {
        
            char child = i;
            suggestionsRec(root->children[i],
                           currPrefix + child);
        }
}
 
// print suggestions for given query prefix.
/*
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
 */
int printAutoSuggestions(TrieNode* Treeroot, const string query)
{
    struct TrieNode* pCrawl = Treeroot;
    for (char c : query) {
        int index = (int)c;

   
        if (!pCrawl->children[index]) {
            // recommend the top 3 most similar entries in the Trie
            vector<pair<int, string>> suggestions;
            for (int i = 0; i < ASCII_Size; i++) {
                if (pCrawl->children[i]) {
                    string prefix = query + (char)i;
                    int similarity = 0;
                    for (int j = 0; j < prefix.length() && j < query.length(); j++) {
                        if (prefix[j] == query[j]) {
                            similarity++;
                        }
                    }
                    suggestions.push_back(make_pair(similarity, prefix));
                }
            }
            sort(suggestions.rbegin(), suggestions.rend());
            cout << "Do you mean:" << endl;
            for (int i = 0; i < min((int)suggestions.size(), 3); i++) {
                cout << suggestions[i].second << endl;
            }
            return 0;
        }

        pCrawl = pCrawl->children[index];
    }

  
    if (isLastNode(pCrawl)) {
        cout << query << endl;
        return -1;
    }

    suggestionsRec(pCrawl, query);
    return 1;
}

