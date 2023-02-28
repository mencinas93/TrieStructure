
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
#include <unistd.h> // for getcwd()
#include "search.hpp"


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
  
    iFile.close();
    
    
    if (!found){
        cout << " The Word ' " << search_word << " ' does not exist in this Dictionary File!\n";
    }
    
    iFile.close();
    
    
    string Search_Inquiry;
    //int comparison = printAutoSuggestions(TreeRoot, Search_Inquiry);
    cout << "Please type in the word you are searching for " << endl;
    cin >> Search_Inquiry;
    printAutoSuggestions(TreeRoot, Search_Inquiry);
    
    

      return 0;
}

