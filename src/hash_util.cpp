#include "hash_util.hpp"
#include <openssl/sha.h>
#include <cstring>

std::uint64_t hash_seed(const std::string& input) {
    unsigned char hash[SHA256_DIGEST_LENGTH]; // Buffer to hold the hash
    SHA256(reinterpret_cast<const unsigned char*>(input.data()), input.size(), hash);

    std::uint64_t seed = 0; // Initialize seed
    std::memcpy(&seed, hash, sizeof(seed));
    
    return seed;
}
