/**
 * @file define.cpp
 * @author Stephanie L'Heureux (salheureux)
 * @version 1.0
 * @date 09.14.22
 * 
 * For your weekly participation practice, try creating a function 
 * template that will print any value of any printable type, prefixed 
 * with the current date and time
 */
// week03_log(10);          // Output: (Current date/time): 10
// week03_log("whatever");  // Output: (Current date/time): whatever
// week03_log(1.12345);     // Output: (Current date/time): 1.2345

#include <iostream>
#include <chrono>
#include <ctime>
#include <sstream>

/**
 * Prints any printable type prefixed with the current date and time 
 * 
 * @tparam PrintableType Any printable type
 * 
 * @param text text to print
 * @return The string str in lowercase
 */
template <typename PrintableType>
void week03_log(PrintableType text);

int main () {
  week03_log(10);  
  week03_log("whatever");
  week03_log(1.12345);

  return 0;
}

template <typename Message>
void week03_log(Message text) {
  auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  auto c_time_formatted = ctime(&time);
  std::istringstream ss(c_time_formatted);
  std::string string_time;

  getline(ss, string_time);

  std::cout << string_time << ": " << text << std::endl;
}
