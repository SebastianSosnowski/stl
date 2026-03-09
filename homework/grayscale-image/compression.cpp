#include "compression.hpp"

static void compressRow(const std::array<uint8_t, width>& row,
                        std::vector<std::pair<uint8_t, uint8_t>>& compressed) {
    auto pixel = row.begin();
    while (pixel != row.end()) {
        auto next =
            std::find_if(pixel, row.end(), [&pixel](auto current) { return *pixel != current; });
        auto count = std::distance(pixel, next);
        compressed.emplace_back(*pixel, count);
        pixel = next;
    }
}

std::vector<std::pair<uint8_t, uint8_t>> compressGrayscale(
    std::array<std::array<uint8_t, width>, height>& bitmap) {
    std::vector<std::pair<uint8_t, uint8_t>> compressed;
    std::for_each(bitmap.begin(), bitmap.end(),
                  [&compressed](const auto& row) { compressRow(row, compressed); });
    return compressed;
}

std::array<std::array<uint8_t, width>, height> decompressGrayscale(
    const std::vector<std::pair<uint8_t, uint8_t>>& compressed_bitmap) {
    std::array<std::array<uint8_t, width>, height> decompressed{};
    auto decompressed_it = decompressed[0].begin();
    std::ranges::for_each(compressed_bitmap, [&decompressed_it](const auto& p) {
        std::fill_n(decompressed_it, p.second, p.first);
        std::advance(decompressed_it, p.second);
    });
    return decompressed;
}

void printMap(const std::array<std::array<uint8_t, width>, height>& bitmap) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            std::cout << std::setw(3) << int(bitmap[i][j]) << ' ';
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}