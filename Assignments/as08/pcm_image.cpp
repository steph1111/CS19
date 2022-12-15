/**
 * @file pcm_image.cpp
 * @author Stephanie L'Heureux (salheureux)
 * @date 10.29.22
 *
 * C++ program that accepts two command-line arguments specifying the width and 
 * height of an image and interprets the contents of standard input as a stream of
 * raw (binary) 16-bit integer PCM audio samples and emits on standard output a 
 * sequence of 8-bit grayscale pixel values representing a width×height-pixel image
 * on which the PCM waveform has been plotted as white pixels against a black background.
 * Image avaliable at https://jeff.cis.cabrillo.edu/~salheureux/as08.png
 */

#include <cmath>      // for math functions
#include <cstdint>    // for sized types
#include <iostream>   // for stdin and stdout
#include <vector>     // for std::vector
#include <cstdlib>    // for exit()

int main(int argc, char **argv) {
  // Ensure the user entered the correct command line arguements
  if (argc != 3) {
    std::cerr << "USAGE: " << argv[0] << " 'width' 'height'\n";
    std::cerr << "You provided: " << argc << " arguments, expected 3 arguments.\n";
    exit(1);
  }

  const double IMAGE_WIDTH = std::stoi(argv[1]);
  const double IMAGE_HEIGHT = std::stoi(argv[2]);
  char byte_buffer[2];
  std::vector<char> image(IMAGE_WIDTH * IMAGE_HEIGHT);
  std::vector<int16_t> int_vals;
  unsigned x, y;

  // reads bytes from stdin, two bytes at a time
  while (std::cin.read(byte_buffer, 2)) {
    int16_t *temp = reinterpret_cast<int16_t *>(byte_buffer);
    int_vals.push_back(*temp);
  }

  unsigned num_samples = int_vals.size();

  int bound_distance = std::round(2 * (IMAGE_WIDTH / num_samples));
  if (bound_distance < 2) bound_distance = 2;
  if (bound_distance > (IMAGE_HEIGHT) / 16) bound_distance = std::round(IMAGE_HEIGHT / 16);

  // cerr output for testing
  std::cerr << "Sample count: " << num_samples << std::endl;
  std::cerr << "Bounding box distance: " << bound_distance << std::endl;

  // Plots the graph on the image vector
  for (unsigned i = 0; i < num_samples - 1; i++) {
    x = std::round((IMAGE_WIDTH - 1) / num_samples * i);
    y = std::round((IMAGE_HEIGHT - 1) / 2 - (int_vals[i] / 32767.0) * ((IMAGE_HEIGHT - 1)/ 2));

    for (unsigned col = x - bound_distance; col <= x + bound_distance; col++) {
      for (unsigned row = y + bound_distance ; row >= y - bound_distance; row--) {
        try {
          image.at(row * IMAGE_WIDTH + col) = '\xff';  // index @ (x, y) = y * width + x
        } catch (const std::out_of_range& e) { }       // catch errors from bounding box
      }
    }
  }


  // Write the image
  std::cout.write(image.data(), image.size());
}