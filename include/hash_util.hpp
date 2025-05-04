#pragma once
#include <string>
#include <vector>
#include <cstdint>

/// @brief Hashes a string to a 64-bit unsigned integer using SHA-256.
/// @param input The string to be hashed.
/// @return A 64-bit unsigned integer representing the hash of the input string.
std::uint64_t hash_seed(const std::string& input);