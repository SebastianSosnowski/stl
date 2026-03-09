#pragma once
#include <algorithm>
#include <array>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <ranges>
#include <utility>
#include <vector>

constexpr size_t width = 240;
constexpr size_t height = 160;

std::vector<std::pair<uint8_t, uint8_t>> compressGrayscale(std::array<std::array<uint8_t, width>, height>& bitmap);
std::array<std::array<uint8_t, width>, height> decompressGrayscale(const std::vector<std::pair<uint8_t, uint8_t>>& compressed_bitmap);
void printMap(const std::array<std::array<uint8_t, width>, height>& bitmap);