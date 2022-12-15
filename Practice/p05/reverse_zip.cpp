/**
 * @file reverse_zip.cpp
 * @author Stephanie L'Heureux (salheureux)
 * @date 10.09.22
 * 
 * For your weekly participation practice, see if you can 
 * rewrite the example with ZIP codes so that runs in the other 
 * direction: That is, the user enters a city and state, and the 
 * program produces every associated ZIP code.
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <unordered_map>

int main () {
  std::string location;
  int zip;
  std::unordered_map<std::string, std::vector<int>> zip_codes;

  {
    std::ifstream fin("/srv/datasets/zip_tokens");
    while (fin >> zip >> location) {
      std::replace(location.begin(), location.end(), '_', ' ');
      zip_codes[location].push_back(zip);
    }
  }
  std::cout << "Enter a location (city, state abbrv.)\n";
  while (std::getline(std::cin, location)) {
    for (int code : zip_codes[location]) {
      std::cout << code << std::endl;
    }
    std::cout << std::endl;
  }
  return 0;
}
