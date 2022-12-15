#include <cassert>
#include <cmath>
#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <string>
#include "cs19_protein.h"
#include <map>
 
int main(int argc, char **argv) {
  // from Rosalind PRTM: https://rosalind.info/problems/prtm/
  // cs19::Protein test("GATTACA");
  const std::initializer_list<char> prtm_prot{'S', 'K', 'A', 'D', 'Y', 'E', 'K'};
  constexpr double prtm_mass = 821.392;
  assert(std::abs(cs19::Protein(prtm_prot).mass() - prtm_mass) < .001);
  assert(std::abs(cs19::Protein(std::string(prtm_prot)).mass() - prtm_mass) < .001);
  assert(std::abs(cs19::Protein(std::string(prtm_prot).c_str()).mass() - prtm_mass) < .001);
  assert(std::abs(cs19::Protein(prtm_prot.begin(), prtm_prot.end()).mass() - prtm_mass) < .001);
 
  cs19::Protein test;
  while (std::cin) {
    try {
      if (std::cin >> test)
        std::cout << test << ' ' << test.size() << ' ' << test.mass() << '\n';
    } catch (std::domain_error &error) {
      std::cerr << error.what() << '\n';
    }
  }
}