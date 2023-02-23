
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
#include <unistd.h> // for getcwd()
#include "search.hpp"

/*
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

*/


int main(){
    struct TrieNode *TreeRoot = getNode();
    
    char cwd[1024];
       if (getcwd(cwd, sizeof(cwd)) != nullptr) {
          std::cout << "Current working directory: " << cwd << std::endl;
     } else {
        std::cout << "Failed to get current working directory" << std::endl;
      }
    
    
    ifstream iFile;
    ofstream oFile;
   
    iFile.open("Dictionary.txt");
    if (!iFile.is_open()){
        cout << "Not inputting file!\n";
        return 0;
    }
    
    
    string search_word = "hardware";
    bool found = false;
    string line;
    bool multipleFound = false;
    while (getline(iFile, line)) {
        if (!search(TreeRoot, line)) {
            insert(TreeRoot, line);
        }
        if (line.find(search_word) != string::npos) {
            if (!multipleFound){
                cout << "The word '" << search_word << "' is present!'" << endl;
                multipleFound = true;
            }
          
            found = true;
        }
        
    }
    /*
    while (getline(iFile, line))
       insert(TreeRoot, line);
        if(line.find(search_word) != string::npos){
            cout << "The word '" << search_word << "' is present!'" << endl;
            found = true;
        }
    //   cout << search_words << endl;
    }
    */
    iFile.close();
    
    
    if (!found){
        cout << " The Word ' " << search_word << " ' does not exist in this Dictionary File!\n";
    }
    
    iFile.close();
    
    
  //  string search_word = "hardware";
  //    if (search(TreeRoot, search_word)) {
  //        cout << "The word '" << search_word << //"' is present in the Trie.\n";
  //    } else {
  //        cout << "The word '" << search_word << "' is not present in the Trie.\n";
  //    }
    string Search_Inquiry;
    //int comparison = printAutoSuggestions(TreeRoot, Search_Inquiry);
    cout << "Please type in the word you are searching for " << endl;
    cin >> Search_Inquiry;
    printAutoSuggestions(TreeRoot, Search_Inquiry);
    
    
    
    

      return 0;
}

