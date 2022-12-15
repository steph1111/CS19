#ifndef _CS19_RECURRENCE_H_
#define _CS19_RECURRENCE_H_

#include <gmpxx.h>
#include <cmath>
#include <unordered_map>

namespace cs19 {

/**
 * Recursively calculates index i of the Fibonacci sequence.
 *
 * @see https://en.wikipedia.org/wiki/Fibonacci_number
 * @param i the requested index
 * @param memoized whether to perform memoized recursion
 * @return index i of the Fibonacci sequence
 */
mpz_class fibonacci(unsigned i, bool memoized = false) {
  // We covered this in class, so might as well just include the code here.
  if (i < 2) return i;
  if (memoized) {
    static std::unordered_map<unsigned, mpz_class> memos;
    auto memo = memos.find(i);
    if (memo == memos.end()) {
      mpz_class result = fibonacci(i - 1, true) + fibonacci(i - 2, true);
      memos[i] = result;
      return result;
    } else {
      return memo->second;
    }
  }
  return fibonacci(i - 1) + fibonacci(i - 2);
}

/**
 * Recursively calculates the golden ratio (often denoted as the Greek letter φ
 * ("phi") via its
 * nested radical representation.
 *
 * @see https://en.wikipedia.org/wiki/Golden_ratio
 * @param terms the number of terms in the nested radical to compute (assumed to
 * be >= 1)
 * @return phi calculated via the requested number of nested-radical terms
 */
double phi(unsigned terms) {
  if (terms <= 1) {
    return sqrt(terms);
  } else {
    return sqrt(1 + phi(terms - 1));
  }
}

/**
 * Recursively calculates the plastic number (often denoted as the Greek letter
 * ρ ("rho")) via its
 * nested radical representation.
 *
 * @see https://en.wikipedia.org/wiki/Plastic_number
 * @param terms the number of terms in the nested radical to compute (assumed to
 * be >= 1)
 * @return rho calculated via the requested number of nested-radical terms
 */
double rho(unsigned terms) {
  if (terms <= 1) {
    return cbrt(terms);
  } else {
    return cbrt(1 + rho(terms - 1));
  }
}

/**
 * Calls a function with successively larger integer arguments (starting from 1)
 * until the function
 * returns the same value twice in succession, and returns that value. Meant to
 * work with functions
 * like rho and phi in this assignment, e.g. `most_precise(rho)` will repeatedly
 * call rho (`rho(1)`,
 * `rho(2)`, `rho(3)`, etc.) requesting more levels of recursion until two
 * successive calls return
 * the same value.
 *
 * @tparam Function a function with one parameter of type `unsigned` and a
 * return type of `double`
 * @param fun the function to call with successively larger arguments
 * @return the first repeated return value
 */
template <typename Function>
double most_precise(Function func) {
  unsigned i = 1;
  double prev = func(i), curr = 0;
  do {
    i++;
    prev = curr;
    curr = func(i);
  } while (prev != curr);
  return curr;
}

/**
 * Recursively calculates index i of the Padovan sequence.
 * @see https://en.wikipedia.org/wiki/Padovan_sequence
 *
 * @param i the requested index (starting from 0)
 * @param memoized whether to perform memoized recursion
 * @return index i of the Padovan sequence
 */
mpz_class padovan(unsigned i, bool memoized = false) {
  if (i <= 2) return 1;
  if (memoized) {
    static std::unordered_map<unsigned, mpz_class> memos;
    auto memo = memos.find(i);
    if (memo == memos.end()) {
      mpz_class result = padovan(i - 2, true) + padovan(i - 3, true);
      memos[i] = result;
      return result;
    } else {
      return memo->second;
    }
  }
  return padovan(i - 2) + padovan(i - 3);
}

/**
 * Recursively calculates index i of the Perrin sequence.
 * @see https://en.wikipedia.org/wiki/Perrin_number
 *
 * @param i the requested index (starting from 0)
 * @param memoized whether to perform memoized recursion
 * @return index i of the Perrin sequence
 */
mpz_class perrin(unsigned i, bool memoized = false) {
  if (i == 0)
    return 3;
  else if (i == 1)
    return 0;
  else if (i == 2)
    return 2;
  if (memoized) {
    static std::unordered_map<unsigned, mpz_class> memos;
    auto memo = memos.find(i);
    if (memo == memos.end()) {
      mpz_class result = perrin(i - 2, true) + perrin(i - 3, true);
      memos[i] = result;
      return result;
    } else {
      return memo->second;
    }
  }
  return perrin(i - 2) + perrin(i - 3);
}

}  // namespace cs19
#endif  // _CS19_RECURRENCE_H_
