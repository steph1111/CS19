/**
 * @file cs19_rosalind.h
 *
 * Function templates to solve a few of the introductory Rosalind problems.
 *
 * @author Stephanie L'Heureux, salheureux@jeff.cis.cabrillo.edu
 */

// Header guard ensures that the contents of this file will only be added once to an executable
#ifndef CS19_ROSALIND_H_
#define CS19_ROSALIND_H_

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
  auto counts = std::make_tuple(0, 0, 0, 0);

  for (char nucleotide : dna) {
    if (nucleotide == 'A') std::get<0>(counts)++;
    if (nucleotide == 'C') std::get<1>(counts)++;
    if (nucleotide == 'G') std::get<2>(counts)++;
    if (nucleotide == 'T') std::get<3>(counts)++;
  }

  return counts;
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

  for (unsigned i = 0; i < dna.size(); i++) {
    if (dna[i] == 'T') rna[i] = 'U';
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
  char comp[2][4] = {{'A', 'C', 'G', 'T'}, {'T', 'G', 'C', 'A'}};
  auto reversed_comp = dna;
  reversed_comp.clear();

  for (int i = dna.size() - 1; i >= 0; i--) {
    for (unsigned j = 0; j < 4; j++) {
      if (dna[i] == comp[0][j]) reversed_comp.push_back(comp[1][j]);
    }
  }

  return reversed_comp;
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
template <typename NucleotideSequence>
unsigned hamming_distance(const NucleotideSequence &seq1, const NucleotideSequence &seq2) {
  unsigned int ham_distance = 0;

  if (seq1.size() != seq2.size()) return -1;

  for (unsigned i = 0; i < seq1.size(); i++) {
    if (seq1[i] != seq2[i]) ham_distance++;
  }

  return ham_distance;
}

}  // namespace cs19

#endif  // CS19_ROSALIND_H