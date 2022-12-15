/**
 * @author Stephanie L'Heureux (salheureux)
 * @version 2.0
 * @date 09.05.22
 * 
 * A modified version of Rosalind Problem GC that computes 
 * the GC-content of DNA strings on standard input.
*/

#include <iostream>   // Input/Output stream library
#include <string>     // standard strings
#include <iomanip>    // Output formatting

int main() {
  int ta_count = 0, gc_count = 0;   // group totals
  double total_valid = 0.0;         // total a, g, c, and t
  double gc_content = 0;            // gc content

  for (std::string dna; std::getline(std::cin, dna);) {
    for (char base : dna) {
      if (base == 'G' || base == 'C') gc_count++;
      if (base == 'T' || base == 'A') ta_count++;
    }
  }

  total_valid = ta_count + gc_count;

  if (total_valid > 0) {
    gc_content = (gc_count / total_valid) * 100;
  }

  std::cout << std::fixed << std::setprecision(6);
  std::cout << gc_content << std::endl;

  return 0;
}