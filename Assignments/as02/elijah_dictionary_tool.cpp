/*
dictTool.cpp

 */

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>

using std::cout;
using std::endl;

bool checkMatch(int semis, std::string semiToken, std::string key);

int main (int argc, char **argv) {
  std::ifstream file("/srv/datasets/wordnet.sorted.txt");
  std::string searchWord;
  std::string endSemi;
  int n = 0;
  int t = 0;
  
  for (int i = 0; i < argc; ++i) {
    if ((argc - 1) >= (i + 1)) {
    searchWord = argv[i + 1];
    for (int i = 0; i < searchWord.size(); ++i) {
      searchWord.at(i) = tolower(searchWord.at(i));
    }
    }
    for (std::string token; std::getline(file, token, '\t');) {
      std::string def;
      std::string word;
      std::string type;
      std::string definition;
      t = 0;
      
      // every other iteration breaks up word from def
      if (n % 2 == 0) {
        std::stringstream wsToken(token);        
        int k = 0;
        std::getline(wsToken, def, '\n'); // grabs def
        std::getline(wsToken, word, '\t'); // grabs word
        for (unsigned int i = 0; i < word.size(); ++i) { // counts numSemiColons (k)
          if (word.at(i) == ';') {
          ++k;
          }
        }
        if (0 < k) { // case 1 where multiple words with semiColons
          for (int i = 0; i < k; ++i) { // grabs words and isolates single word
            std::string isoWord;
            std::stringstream wordSemiCToken(word);          
            getline(wordSemiCToken, isoWord, ';'); 
            //cout << isoWord << endl;
            for (int i = 0; i < isoWord.size(); ++i) { // makes case insensitive
              isoWord.at(i) = tolower(isoWord.at(i));
            }
          
            if (searchWord == isoWord) {
              cout << word << endl;
              getline(file, type, '\t');
              cout << type << endl;
              getline(file, definition, '\n');
              cout << definition << endl;
              cout << "ONE" << endl;            
              cout << endl;
              // break;
            }            
          }
        } else { // case 2 where it has only one word
          for (int i = 0; i < word.size(); ++i) { //makes case insensitive
            word.at(i) = tolower(word.at(i));
          }
          
          if (searchWord == word) {
            cout << word << endl;
            getline(file, type, '\t');
            cout << type << endl;
            getline(file, definition, '\n');
            cout << definition << endl;
            cout << "TWO" << endl;
            cout << endl;
            // break;
          }       
        }
        
      }
      /* t = 0;
      for (int i = 0; i < token.size(); ++i) {
        if (token.at(i) == ';') {
          ++t;
        }
      }
      if (0 < t) {
        for (int i = 0; i < t; ++i) {
          std::stringstream wordSemiCTokenB(token);
          getline(wordSemiCTokenB, word, ';');
          if (searchWord == word) {
            cout << word << endl;
            getline(file, type, '\t');
            cout << type << endl;
            getline(file, definition, '\n');
            cout << definition << endl;
            cout << "THREE" << endl;
            cout << endl;

        }
        }        
      } else {
          if (searchWord == word) {
            cout << word << endl;
            getline(file, type, '\t');
            cout << type << endl;
            getline(file, definition, '\n');
            cout << definition << endl;
            cout << "FOUR" << endl;
            cout << endl;
        
            }
            }*/         
      }
      ++n;

    }
      return 0;  
}

    /*  
        'hood   noun   (slang) a neighborhood
        .22 caliber;.22-caliber;.22 calibre;.22-calibre adj   of or relating to the bore of a gun (or its ammunition) that measures twenty-two hundredths of an inch in diameter; "a .22 caliber pistol"

  std::getline(file, token, '\t');  // token == "'hood"
  std::cout << token << std::endl;
  std::getline(file, token, '\t');  // token == "noun"
  std::getline(file, token);        // token == "(slang) a neighborhood"
  std::getline(file, token, '\t');  // token == ".22 caliber;.22-caliber;.22 calibre;.22-calibre"
  std::istringstream terms(token);
  std::getline(terms, token, ';');  // token == ".22 caliber"
  std::getline(terms, token, ';');  // token == ".22-caliber"
  std::getline(terms, token, ';');  // token == ".22 calibre"
  std::getline(terms, token, ';');  // token == ".22-calibre"
  std::getline(file, token, '\t');  // token == "adj"
  std::getline(file, token);        
    */



/*
bool checkMatch (int semis, std::string semiToken, std::string key) {
      if (semis != 0) {
        for (int i = 0; i < semis; ++i) {
          std::stringstream colonToken(semiToken);
          std::string possibleMatch;
          std::getline(colonToken, possibleMatch, ';');
            if (key == possibleMatch) {
              return true; 
            } else {
              return false;
            }
        }
      } else {
      std::stringstream colonToken(semiToken);
      std::string possibleMatch;
      std::getline(colonToken, possibleMatch, ';');
        if (key == possibleMatch) {
          return true;
        } else {
          return false;
        }
      }
}
*/
