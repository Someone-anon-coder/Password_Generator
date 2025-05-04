# Password Generator CLI

## Project Overview

This project implements a deterministic, seed-based password generator in C++. Given a user's first name, last name, service name, and a secret passphrase (six words), it produces a repeatable, high-entropy password comprising six dictionary words (capitalized), one special character, and one digit. Internally, inputs are concatenated, salted, and hashed with SHA-256 to derive a 64-bit seed, which initializes a C++ PRNG (`std::mt19937_64`). Selection of words, the special character, and digit is driven by this seeded RNG, guaranteeing identical output for identical inputs.

## Features

* **Deterministic Generation:** Same inputs always yield the same password.
* **Human-Friendly Words:** Six meaningful dictionary words instead of random gibberish.
* **High Entropy:** Includes six words + one special character + one digit.
* **Modular Design:** Clear separation between hashing utilities and password logic.
* **Salting & Secret Key:** Salted SHA-256 hash incorporates a user-supplied six-word secret key and a static salt.
* **CLI Only:** Lightweight command-line interface with no GUI overhead.

## Prerequisites

* C++17-compatible compiler (e.g., `g++`, `clang++`)
* [OpenSSL](https://www.openssl.org/) development libraries for SHA-256 hashing

## Building the Project

1. Clone or download the repository.
2. Ensure `Wordlists/default_wordlist.txt` is populated with one lowercase English word per line (≥100,000 words recommended).
3. Compile using:

   ```sh
   g++ -std=c++17 -O2 \
       main.cpp src/hash_util.cpp src/password_generator.cpp \
       -o seedpass -lssl -lcrypto
   ```

## Usage

```sh
$ ./seedpass
Enter First Name: Alice
Enter Last Name: Smith
Enter Service Name (e.g., twitter.com): twitter.com
Enter Secret Key (6 words separated by space): alpha beta gamma delta epsilon zeta
Generated Password: MapleCloudRocketBright!7
```

## File Structure

```
include/
├── hash_util.hpp           # SHA-256 hashing utility API
└── password_generator.hpp  # Password generation class API

src/
├── hash_util.cpp           # SHA-256 implementation (OpenSSL)
└── password_generator.cpp  # Core password generation logic

Wordlists/
└── default_wordlist.txt    # One lowercase word per line

main.cpp                    # CLI entry point
```

## Key Code Snippets

### `hash_util.hpp`

```cpp
#pragma once
#include <string>
#include <cstdint>

/// @brief Hashes a string to a 64-bit unsigned integer using SHA-256.
std::uint64_t hash_seed(const std::string& input);
```

### `password_generator.hpp`

```cpp
#pragma once
#include <string>
#include <vector>

class PasswordGenerator {
public:
    explicit PasswordGenerator(const std::string& wordlistPath);
    std::string generate(
        const std::string& name,
        const std::string& lastname,
        const std::string& service,
        const std::string& secretKey
    );

private:
    std::vector<std::string> words;
    std::vector<char> specialChars = {'!', '@', '#', '$', '%', '^', '&', '*', '-', '+'};
    void loadWordlist(const std::string& path);
    std::string capitalize(const std::string& word);
};
```

## Contributing

1. Fork the repository.
2. Create a feature branch (`git checkout -b feature-name`).
3. Commit your changes (`git commit -m "Add feature"`).
4. Push to the branch (`git push origin feature-name`).
5. Open a pull request.

## License

This project is licensed under the MIT License. See `LICENSE` for details.
