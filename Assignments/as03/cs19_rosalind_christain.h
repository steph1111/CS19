#ifndef CS19_ROSALIND_C_H_
#define CS19_ROSALIND_C_H_
// #include <iostream>
#include <tuple>
 
namespace cs19 {

/**
 * Counts the occurrences of each nucleotide in a DNA string, similar to Rosalind problem DNA.
 * See: http://rosalind.info/problems/dna/
 *
 * @tparam DnaSequence an iterable type that supports iteration with a range-based loop, and
 * contains A/C/G/T char values, e.g. std::string and std::vector<char>.
 *
 * @param dna a DNA sequence (assumed to contain A/C/G/T characters)
 * @return a tuple containing the number of occurrences of 'A', 'C', 'G', 'T' in dna, respectively
 */
template <typename DnaSequence>
std::tuple<int, int, int, int> nucleotide_counts(const DnaSequence &dna) {
  auto dnatypes = std::make_tuple(0,0,0,0);

    for(unsigned i = 0;i < dna.size();i++) {
        if(dna.at(i) == 'A') {
            std::get<0>(dnatypes)++;
        }else if(dna.at(i) == 'C') {
            std::get<1>(dnatypes)++;
        }else if(dna.at(i) == 'G') {
            std::get<2>(dnatypes)++;
        }else if(dna.at(i) == 'T') {
            std::get<3>(dnatypes)++;
        }
    }
return dnatypes;
}

/**
 * Returns a RNA sequence transcribed from a DNA sequence, similar to Rosalind problem RNA.
 * See: http://rosalind.info/problems/rna/
 *
 * @tparam NucleotideSequence a random-access container type offering operations similar to
 * std::string and std::vector<char>, e.g. member function size(), indexing with indexes from 0 to
 * size() - 1, and copying via assignment.
 *
 * @param dna a DNA sequence (assumed to contain A/C/G/T characters)
 * @return an object of the same type representing the transcribed RNA version of the input DNA
 */
template <typename NucleotideSequence>
NucleotideSequence transcribe(const NucleotideSequence &dna) {
  auto rna = dna;
  for(unsigned i = 0;i < rna.size();i++) {
    if(rna.at(i) == 'A'){
        rna.at(i) = 'A';
    }else if(rna.at(i) == 'T') {
        rna.at(i) = 'U';
    }else if(rna.at(i) == 'G') {
        rna.at(i) = 'G';
    }else if(rna.at(i) == 'C') {
        rna.at(i) = 'C';
    }
  }
return rna;
}
 
/**
 * Returns the reverse complement of a DNA sequence, similar to Rosalind problem RNA.
 * See: http://rosalind.info/problems/revc/
 *
 * @tparam DnaSequence a random-access container type offering operations similar to std::string and
 * std::vector<char>, e.g. member function size(), indexing with indexes from 0 to size() - 1, and
 * copying via assignment.
 *
 * @param dna a DNA sequence (assumed to contain A/C/G/T characters)
 * @return an object of the same type, representing reverse complement of the input DNA
 */
template <typename DnaSequence>
DnaSequence reverse_complement(const DnaSequence &dna) {
  auto rna = dna;
  for(unsigned i = 0;i < rna.size();i++) {
    if(rna.at(i) == 'A'){
        rna.at(i) = 'T';
    }else if(rna.at(i) == 'T') {
        rna.at(i) = 'A';
    }else if(rna.at(i) == 'G') {
        rna.at(i) = 'C';
    }else if(rna.at(i) == 'C') {
        rna.at(i) = 'G';
    }
  }
  std::reverse(rna.begin(), rna.end());
return rna;
}
 
/**
 * Returns the Hamming distance between two sequence, similar to Rosalind problem HAMM.
 * See: http://rosalind.info/problems/hamm/
 *
 * @tparam NucleotideSequence a random-access container type offering operations similar to
 * std::string and std::vector<char>, e.g. member function size(), and indexing with indexes from 0
 * to size() - 1.
 *
 * @param seq1 the first sequence
 * @param seq2 the second sequence
 * @return the Hamming distance between the two sequences, or -1 if they are of unequal length
 */
// template <typename NucleotideSequence>
// unsigned hamming_distance(const NucleotideSequence &seq1, const NucleotideSequence &seq2) {
  
// }
 
}  // namespace cs19
 
#endif  // CS19_ROSALIND_H