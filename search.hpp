//
//  Search.hpp
//  ProjectMain
//
//  Created by Michael Encinas on 2/21/23.
//

#ifndef search_hpp
#define search_hpp
#include <string>
#include <iostream>
#include <vector>
#include <stdio.h>
using namespace std;


struct TrieNode* getNode();
void insert(struct TrieNode* Treeroot, string key);
bool search(struct TrieNode* TreeRoot, string key);
int printAutoSuggestions(struct TrieNode* Treeroot, const string query);
void suggestionsRec(struct TrieNode* root,
                    string currPrefix);
bool isLastNode(struct TrieNode* Treeroot);


#endif /* Search_hpp */



