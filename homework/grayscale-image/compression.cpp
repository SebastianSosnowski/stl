#include "compression.hpp"

std::vector<std::pair<uint8_t, uint8_t>> compressGrayscale(std::array<std::array<uint8_t, width>, height>& bitmap) {
    std::vector<std::pair<uint8_t, uint8_t>> compressed;
    for (int i = 0; i < height; i++) {
        int count = 1, left = bitmap[i][0], right;
        for (int j = 1; j < width; j++) {
            right = bitmap[i][j];
            if (right == left) {
                count++;
            } else {
                compressed.push_back(std::make_pair(left, count));
                left = right;
                count = 1;
            }
        }
        compressed.push_back(std::make_pair(left, count));  // push last pixel / series of pixels
    }
    return compressed;
}

std::array<std::array<uint8_t, width>, height> decompressGrayscale(const std::vector<std::pair<uint8_t, uint8_t>>& compressed_bitmap) {
    std::array<std::array<uint8_t, width>, height> decompressed;

    return decompressed;
}

void printMap(const std::array<std::array<uint8_t, width>, height>& bitmap) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            std::cout << std::setw(3) << int(bitmap[i][j]) << ' ';
        }
        std::cout << "\n";
    }
}