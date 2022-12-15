/**
 * @file define.cpp
 * @author Stephanie L'Heureux (salheureux)
 * @version 6.0
 * @date 09.08.22
 * 
 * C++ program that serves as a sort of dictionary lookup tool,
 * finding and printing the definitions of a given word/term using 
 * the WordNet dataset
 */

#include <iostream>  // cin / cout
#include <string>    // strings 
#include <cstdlib>   // exit()
#include <fstream>   // file I/O
#include <sstream>   // string streamss

/**
 * Returns the lowecase version of a given string
 * 
 * @param str The string to convert to lowercase 
 * @return The string str in lowercase
 */
std::string lower_str(std::string str);

int main(int argc, char **argv) {
  // Ensures the user entered the correct number of arguements
  if (argc != 2) {
    std::cerr << "USAGE: " << argv[0] << " word to search\n";
    std::cerr << "You provided: " << argc << " arguments, expected 2 arguments.\n";
    exit(1);
  }

  // Variable declarations
  std::string user_word = lower_str(argv[1]);
  std::string file_name = "/srv/datasets/wordnet.sorted.txt";
  std::string token;
  std::string words;
  int count = 0;

  // Sets up file stream
  std::ifstream fin;
  fin.open(file_name);
  if (!fin.is_open()) {
    std::cerr << "File " << file_name << " failed to open\n";
    exit(2);
  }

  // Searches for words
  for (std::string line; std::getline(fin, line);) {
    std::istringstream line_stream(line);
    std::getline(line_stream, words, '\t');
    std::istringstream word_stream(words);
    for (std::string word; std::getline(word_stream, word, ';');) {
      if (user_word == lower_str(word)) {
        if (count >= 1) std::cout << std::endl;
        std::istringstream found_line_stream(line);
        count++;
        for (std::string token; std::getline(found_line_stream, token, '\t');) {
          std::cout << token << std::endl;
        }
      }
    }
  }

  fin.close();

  return 0;
}

std::string lower_str(std::string str) {
  const int CASE_DIFF = 32;

  for (unsigned i = 0; i < str.size(); i++) {
    if (str[i] <= 'Z' && str[i] >= 'A') str[i] += CASE_DIFF;
  }

  return str;
}