/**
 * @file readability.cpp
 * @author Stephanie L'Heureux (salheureux)
 * @date 10.01.22
 * 
 * C++ program that calculates the readability of text on standard input. 
 * The test applied shall be decided based on the value of a command-line argument.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <cmath>
#include <tuple>

/**
 * Ensures the user entered valid command line arguments and calls the function 
 * to calculate readability score. 
 * If the user provided too few or too many arguements, program exits with status of 1. 
 * If the user provided an invalid readability command, the user is provided with an 
 * option to see avaliable commands. Program exits with status 2. 
 * If the user entered valid commands, calls appropriate readability calculation function
 * based on command line arguments.
 * 
 * @param argv The command line arguements given when running the executable 
 */ 
void verify_choice(int argc, char** argv);

/**
 * Reads familiar words from a file, converts them to lowercase and stores them in a set
 * 
 * @param familiar_words Pointer to a unordered set to store familiar words in
 * @param file_name File to read familiar words from 
 */ 
void input_familiar_words(std::unordered_set<std::string> *familiar_words, std::string file_name);

/**
 * Reads information from a file containing data about syllables. The file divides 
 * syllables in words by ';' and '-'. The syllable data is stored in a map in which
 * word is the key and number of syllables is the value. Some words have multiple syllable 
 * counts, in such a case, the higher count is recorded. Note: it is assumed all words in
 * the file are lowercase.
 * 
 * @param familiar_words Pointer to a unordered set to store familiar words in
 * @param file_name File to read familiar words from 
 */ 
void input_syllables(std::unordered_map<std::string, int> *syllables, std::string file_name);

/**
 * Removes given characters from the end of a string 
 * 
 * @param str String to remove ending characters from
 * @param remove1 Character to remove
 * @param remove2 Default parameter. Optional second character to remove
 */ 
void remove_from_end(std::string *str, char remove1, char remove2 = '\0');

/**
 * Removes given characters from the start of a string 
 * 
 * @param str String to remove starting characters from
 * @param remove1 Character to remove
 * @param remove2 Default parameter. Optional second character to remove
 */ 
void remove_from_beginning(std::string *str, char remove1, char remove2 = '\0');

/**
 * Determines if a string is a sentence when a sentence is defined to be denoted 
 * by any whitespace-delimited token that ends with any of the following, 
 * ignoring any single or double quotes at the end of the token: .?!
 * 
 * @param str A pointer to the string to determine if it is a sentence
 * @return true if the whitespace-delimited token is a sentence, oherwise false
 */ 
bool is_sentence(std::string *str);

/**
 * Converts 'str' to a word when a word is defined any whitespace-delimited token 
 * that remains non-empty after removing all characters other than the following 
 * (case-insensitive) and stripping single-quotes and hyphens from both ends
 * " abcdefghijklmnopqrstuvwxyz'- "
 * 
 * @param str A pointer to the string to convert to a word
 * @return 'str' with invalid characters removed
 */
std::string determine_word(std::string *str);

/**
 * Counts the number of difficult words in vector 'words' when a 
 * difficult words is the number of words that are not present 
 * in a vector of 3000 “easy” words aka 'familiar_words'
 * 
 * @param words The vector of words to count difficult words from
 * @param familiar_words A set containing “easy” words
 * @return The number of 'familiar_words' present in 'words'
 */
int difficult_count(const std::vector<std::string> *words,
                    const std::unordered_set<std::string> *familiar_words);

/**
 * Counts the number of syllables and complex words in vector 'words' when a 
 * complex word is any word containing three or more syllables.
 * 
 * @param words The vector of words to count syllables and complex words from
 * @param syllables A set map containing words and their syllable count
 * @return A tuple containg the number of syllables at index zero and 
 *         the number of complex words at index one 
 */
std::tuple<int, int> syllable_and_complex_count(const std::vector<std::string> *words,
                                                std::unordered_map<std::string, int> *syllables);

/**
 * Computes the Automated Readability Index
 * 
 * @param num_sentences The number of sentences
 * @param num_chars The number of characters
 * @param num_words The number of words
 * @return An estimate of the US grade level needed to comprehend a tex
 */
double ari(double num_sentences, double num_chars, double num_words);

/**
 * Computes the Coleman-Liau Index
 * 
 * @param num_sentences The number of sentences
 * @param num_chars The number of characters
 * @param num_words The number of words
 * @return An estimate of the US grade level needed to comprehend a tex
 */
double cli(double num_sentences, double num_chars, double num_words);

/**
 * Computes the Dale-Chall Readability Score
 * 
 * @param num_words The number of words
 * @param num_sentences The number of sentences
 * @param words A pointer to a vector of words
 * @return Dale-Chall Readability Score 
 *         @see https://en.wikipedia.org/wiki/Dale–Chall_readability_formula
 */
double dcrs(double num_words, double num_sentences, const std::vector<std::string> *words);

/**
 * Computes the Flesch-Kincaid Grade Level
 * 
 * @param num_words The number of words
 * @param num_sentences The number of sentences
 * @param words A pointer to a vector of words
 * @return An estimate of the US grade level needed to comprehend a text
 */
double fkgl(double num_words, double num_sentences, const std::vector<std::string> *words);

/**
 * Computes the Gunning Fog Index
 * 
 * @param num_words The number of words
 * @param num_sentences The number of sentences
 * @param words A pointer to a vector of words
 * @return An estimate of the number of years of education needed to comprehend a text
 */
double gfi(double num_words, double num_sentences, const std::vector<std::string> *words);

/**
 * Computes the SMOG Grade
 * 
 * @param num_sentences The number of sentences
 * @param words A pointer to a vector of words
 * @return An estimate of the number of years of education needed to comprehend a text
 */
double smog(double num_sentences, const std::vector<std::string> *words);

int main(int argc, char** argv) {
  const std::string SYLLABLES_FILE = "/srv/datasets/syllables.txt";
  int num_sentences = 0;
  int num_chars = 0;
  int num_words = 0;
  std::string word;
  std::string test_name;
  std::vector<std::string> words;
  std::unordered_map<std::string, int> syllables;

  // ensures the user ran the program correctly
  verify_choice(argc, argv);
  test_name = argv[1];

  // inputs file data
  input_syllables(&syllables, SYLLABLES_FILE);

  // reads user input from stdin
  for (std::string token; std::cin >> token;) {
    if (is_sentence(&token)) num_sentences++;  // counts sentences
    word = determine_word(&token);             // updates token to meet word specifications
    if (word.size()) words.push_back(word);   // adds word to vector if it has a size greater than 0
    num_chars += word.size();                 // counts characters from valid word
  }

  num_words = words.size();  // number of words is the size of the vector of valid words

  if (test_name == "ari") {
    std::cout << ari(num_sentences, num_chars, num_words) << std::endl;
  } else if (test_name == "cli") {
    std::cout << cli(num_sentences, num_chars, num_words) << std::endl;
  } else if (test_name == "dcrs") {
    std::cout << dcrs(num_words, num_sentences, &words) << std::endl;
  } else if (test_name == "fkgl") {
    std::cout << fkgl(num_words, num_sentences, &words) << std::endl;
  } else if (test_name == "gfi") {
    std::cout << gfi(num_words, num_sentences, &words) << std::endl;
  } else if (test_name == "smog") {
    std::cout << smog(num_sentences, &words) << std::endl;
  }

  return 0;
}

void verify_choice(int argc, char** argv) {
  std::string usr_choice;
  std::unordered_set<std::string> valid_test_names{"ari", "cli", "dcrs", "fkgl", "gfi", "smog"};

  if (argc != 2) {
    std::cerr << "USAGE: " << argv[0] << " 'readability test name'\n";
    std::cerr << "You provided: " << argc << " arguments, expected 2 arguments.\n";
    exit(1);
  }

  std::string test_name = argv[1];

  if (!valid_test_names.count(test_name)) {
    std::cerr << "USAGE: " << argv[0] << " 'readability test name'\n";
    std::cerr << "Invalid readability test name\n\n";
    std::cerr << "Would you like to see the readability commands? (y/n) ";
    std::cin >> usr_choice;
    if (usr_choice[0] != 'N' && usr_choice[0] != 'n') {
      std::cerr << "ari  — computes the automated readability index\n";
      std::cerr << "cli  — computes the Coleman-Liau index\n";
      std::cerr << "dcrs — computes the Dale-Chall readability score\n";
      std::cerr << "fkgl — computes the Flesch-Kincaid grade level\n";
      std::cerr << "gfi  — computes the Gunning fog index]\n";
      std::cerr << "smog — computes the SMOG grade\n";
    }
    exit(2);
  }
}

void input_familiar_words(std::unordered_set<std::string> *familiar_words, std::string file_name) {
  {
  std::ifstream familiar_words_file(file_name);
  for (std::string word; familiar_words_file >> word;) {
    std::transform(word.begin(), word.end(), word.begin(), ::tolower);
    familiar_words->insert(word);
  }
  }
}

void input_syllables(std::unordered_map<std::string, int> *syllables, std::string file_name) {
  int num_syllables;
  {
  std::ifstream syllables_file(file_name);
  for (std::string word; syllables_file >> word;) {
    num_syllables = std::count(word.begin(), word.end(), ';') + 1;
    word.erase(std::remove(word.begin(), word.end(), ';'), word.end());
    if ((*syllables)[word] < num_syllables) {
      (*syllables)[word] = num_syllables;
    }
  }
  }
}

void remove_from_end(std::string *str, char remove1, char remove2) {
  int new_size = 0;
  for (int i = str->size() - 1; i >= 0; i--) {
    if ((*str)[i] != remove1 && (*str)[i] != remove2) {
      new_size = i + 1;
      break;
    }
  }
  str->resize(new_size);
}

void remove_from_beginning(std::string *str, char remove1, char remove2) {
  for (unsigned i = 0; i < str->size(); i++) {
    if ((*str)[i] != remove1 && (*str)[i] != remove2) {
      *str = str->substr(i, str->size() - i);
      break;
    }
  }
}

bool is_sentence(std::string *str) {
  int last_index;

  remove_from_end(str, '"', '\'');

  last_index = str->size() -1;

  if ((*str)[last_index] == '!' || (*str)[last_index] == '?' || (*str)[last_index] == '.') {
    return true;
  }

  return false;
}

std::string determine_word(std::string *str) {
  std::transform(str->begin(), str->end(), str->begin(), ::tolower);

  for (auto it = str->begin(); it != str->end();) {
    if (!((*it >= 'a' && *it <= 'z') || *it == '\'' || *it == '-')) {
      it = str->erase(it);
    } else {
      it++;
    }
  }

  remove_from_beginning(str, '\'', '-');
  if (str->size()) remove_from_end(str, '\'', '-');

  return *str;
}

int difficult_count(const std::vector<std::string> *words,
                    const std::unordered_set<std::string> *familiar_words) {
  int num_difficult = 0;

  for (std::string word : *words) {
    if (!familiar_words->count(word)) num_difficult++;
  }

  return num_difficult;
}

std::tuple<int, int> syllable_and_complex_count(const std::vector<std::string> *words,
                                                std::unordered_map<std::string, int> *syllables) {
  int num_syllables = 0;
  int num_complex = 0;
  int syllables_in_word = 0;

  for (std::string word : *words) {
    if (syllables->count(word)) {
      syllables_in_word = (*syllables)[word];
      num_syllables += syllables_in_word;
      if (syllables_in_word >= 3) num_complex++;
    } else {
      syllables_in_word = round(word.size() / 5.0);
      num_syllables += syllables_in_word;
      if (syllables_in_word >= 3) num_complex++;
    }
  }

  auto num_syllables_and_complex = std::make_tuple(num_syllables, num_complex);

  return num_syllables_and_complex;
}

double ari(double num_sentences, double num_chars, double num_words) {
  double result = 4.71 * (num_chars / num_words) + 0.5 * (num_words / num_sentences) - 21.43;

  return result;
}

double cli(double num_sentences, double num_chars, double num_words) {
  double L = num_chars / num_words * 100;
  double S = num_sentences / num_words * 100;
  double result = 0.0588 * L - 0.296 * S - 15.8;

  return result;
}

double dcrs(double num_words, double num_sentences, const std::vector<std::string> *words) {
  const std::string FAMILIAR_FILE = "/srv/datasets/dale-chall_familiar_words.txt";
  std::unordered_set<std::string> familiar_words;
  input_familiar_words(&familiar_words, FAMILIAR_FILE);

  double num_difficult = difficult_count(words, &familiar_words);
  double result = 0.1579 * ((num_difficult / num_words) * 100) +
                  0.0496 * (num_words / num_sentences);

  return result;
}

double fkgl(double num_words, double num_sentences, const std::vector<std::string> *words) {
  const std::string SYLLABLES_FILE = "/srv/datasets/syllables.txt";
  std::unordered_map<std::string, int> syllables;
  input_syllables(&syllables, SYLLABLES_FILE);

  double num_syllables = std::get<0>(syllable_and_complex_count(words, &syllables));
  double result = 0.39 * (num_words / num_sentences) + 11.8 * (num_syllables / num_words) - 15.59;

  return result;
}

double gfi(double num_words, double num_sentences, const std::vector<std::string> *words) {
  const std::string SYLLABLES_FILE = "/srv/datasets/syllables.txt";
  std::unordered_map<std::string, int> syllables;
  input_syllables(&syllables, SYLLABLES_FILE);

  double num_complex = std::get<1>(syllable_and_complex_count(words, &syllables));
  double result = 0.4 * ((num_words / num_sentences) + 100 * (num_complex / num_words));

  return result;
}

double smog(double num_sentences, const std::vector<std::string> *words) {
  const std::string SYLLABLES_FILE = "/srv/datasets/syllables.txt";
  std::unordered_map<std::string, int> syllables;
  input_syllables(&syllables, SYLLABLES_FILE);

  double num_complex = std::get<1>(syllable_and_complex_count(words, &syllables));
  double result = 1.0430 * sqrt(num_complex * (30 / num_sentences)) + 3.1291;

  return result;
}