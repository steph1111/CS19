/**
 * @file cs19_protein.h
 * @author Stephanie L'Heureux (salheureux)
 * @date 10.27.22
 *
 * Class named Protein in the cs19 namespace, instances of which represent
 * the primary structure of a protein using the amino-acid alphabet
 */

#ifndef _CS19_PROTEIN_H
#define _CS19_PROTEIN_H

#include <algorithm>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <tuple>
#include <fstream>
#include <sstream>

namespace cs19 {
std::map<char, double> masses;
bool map_created = false;

void input_masses();

class Protein {
 public:
  Protein() {
    if (!map_created) {
      cs19::input_masses();
    }
  }

  Protein(const char *amino_acids) {
    if (!map_created) {
      cs19::input_masses();
    }
    this->operator+=(amino_acids);
  }

  template <typename Sequence>
  Protein(const Sequence &amino_acids) {
    if (!map_created) {
      cs19::input_masses();
    }
    this->operator+=(amino_acids);
  }

  template <class InputIterator>
  Protein(InputIterator first, InputIterator last) {
    if (!map_created) {
      cs19::input_masses();
    }
    while (first != last) {
      this->operator+=(*first++);
    }
  }

  Protein(std::initializer_list<char> list) {
    if (!map_created) {
      cs19::input_masses();
    }
    for (char amino_acid : list) {
      this->operator+=(amino_acid);
    }
  }

  auto begin() const { return this->sequence.cbegin(); }

  auto end() const { return this->sequence.cend(); }

  bool operator!=(const char *that) const { return this->sequence != that; }

  template <typename Sequence>
  bool operator!=(const Sequence &that) const {
    return !std::equal(this->sequence.begin(), this->sequence.end(),
                       that.begin(), that.end());
  }

  Protein operator*(std::size_t repeat_count) const {
    std::string new_sequence;
    for (size_t i = 0; i < repeat_count; ++i) new_sequence += this->sequence;
    return Protein(new_sequence);
  }

  Protein operator+(const char *that) const {
    return Protein(this->sequence + std::string(that));
  }

  template <typename Sequence>
  Protein operator+(const Sequence &that) const {
    return Protein(this->sequence + std::string(that.begin(), that.end()));
  }

  Protein &operator+=(char appendage) {
    if (cs19::masses.find(appendage) == cs19::masses.end())
      throw std::domain_error(
          std::string("Invalid character protein sequence: ") + appendage);
    this->sequence += appendage;
    return *this;
  }

  Protein &operator+=(const char *appendage) {
    this->operator+=(std::string(appendage));
    return *this;
  }

  template <typename Sequence>
  Protein &operator+=(const Sequence &appendage) {
    for (char amino_acid : appendage) this->operator+=(amino_acid);
    return *this;
  }

  Protein operator=(const char *that) {
    this->sequence.clear();
    this->operator+=(that);
    return *this;
  }

  template <typename Sequence>
  Protein &operator=(const Sequence &that) {
    this->sequence.clear();
    this->operator+=(that);
    return *this;
  }

  bool operator==(const char *that) const { return this->sequence == that; }

  template <typename Sequence>
  bool operator==(const Sequence &that) const {
    return std::equal(this->sequence.begin(), this->sequence.end(),
                      that.begin(), that.end());
  }

  char operator[](std::size_t index) const {
    if (index >= this->sequence.size()) {
      throw std::out_of_range("Instance of std::out_of_range");
    }
    return this->sequence[index];
  }

  void set(std::size_t index, char amino_acid) {
    if (index >= this->sequence.size()) {
      throw std::out_of_range("Instance of std::out_of_range");
    }
    if (cs19::masses.find(amino_acid) == cs19::masses.end()) {
      throw std::domain_error(
          std::string("Invalid character protein sequence: ") + amino_acid);
    }
    this->sequence[index] = amino_acid;
  }

  std::size_t size() const { return this->sequence.size(); }

  std::string to_string() const { return this->sequence; }

  friend std::ostream &operator<<(std::ostream &out, const Protein &protein) {
    out << protein.sequence;
    return out;
  }

  friend std::istream &operator>>(std::istream &in, Protein &protein) {
    std::string sequence;
    in >> sequence;

    protein = sequence;
    return in;
  }

  double mass() const {
    double protein_mass = 0;

    for (char amino_acid : this->sequence) {
      protein_mass += cs19::masses.at(amino_acid);
    }

    return protein_mass;
  }

 private:
  std::string sequence;
};

void input_masses() {
  double mass;
  char amino_acid;
  {
    std::string file_name = "/srv/datasets/amino-monoisotopic-mass";
    std::ifstream file_stream(file_name);

    while (file_stream >> amino_acid >> mass) {
      masses[amino_acid] = mass;
    }
  }
  map_created = true;
}

}  // namespace cs19

#endif  // _CS19_PROTEIN_H
