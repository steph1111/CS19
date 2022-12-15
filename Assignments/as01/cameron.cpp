#include <iostream>  // Input/Output Stream Library
#include <string>  // Standard Strings

int main() {
    int count_a = 0, count_c = 0, count_g = 0, count_t = 0, gc_count = 0, total_count = 0;
    float gc_content = 0.0;
    for (std::string dna_string; std::getline(std::cin, dna_string);) {
        // takes one line of input from stdin

        for (char base : dna_string) {
            // base: each character in string dna_string, one by one
            if (base == 'A') {
                ++count_a;
            } else if (base == 'C') {
                ++count_c;
            } else if (base == 'G') {
                ++count_g;
            } else if (base == 'T') {
                ++count_t;
            }

            ++total_count;
        }
    }

    // calculate the gc_content

    gc_count = count_g + count_c;

    if (total_count != 0) {
      gc_content = (static_cast<float>(gc_count) / static_cast<float>(total_count)) * 100;
    } else { gc_content = 0; }

    // print gc_content

    std::cout << gc_content << std::endl;
}