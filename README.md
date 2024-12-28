# Concept #

A C++ library providing hash functions.

# Install #
## Requirements ##

Binaries:

- A C++20 compiler (ex: g++-14)
- CMake 3.26 or later

Testing Libraries (optional):

- [Google Test](https://github.com/google/googletest) 1.14 or later (optional)

## Clone

```
git clone https://github.com/arapelle/arba-hash
```

## Use with `conan`

Create the conan package.
```
conan create . --build=missing -c
```
Add a requirement in your conanfile project file.
```python
    def requirements(self):
        self.requires("arba-hash/0.1.0")
```

## Quick Install ##
There is a cmake script at the root of the project which builds the library in *Release* mode and install it (default options are used).
```
cd /path/to/arba-hash
cmake -P cmake/scripts/quick_install.cmake
```
Use the following to quickly install a different mode.
```
cmake -P cmake/scripts/quick_install.cmake -- TESTS BUILD Debug DIR /tmp/local
```

## Uninstall ##
There is a uninstall cmake script created during installation. You can use it to uninstall properly this library.
```
cd /path/to/installed-arba-hash/
cmake -P uninstall.cmake
```

# How to use
## Example - Compute a neutral murmur hash with 64 bits
```c++
#include <arba/hash/murmur_hash.hpp>
#include <arba/hash/version.hpp>
#include <cstdlib>
#include <iostream>

int main()
{
    std::cout << arba::hash::neutral_murmur_hash_64("hello world") << std::endl;
    std::cout << "EXIT SUCCESS" << std::endl;
    return EXIT_SUCCESS;
}
```

# License

[MIT License](./LICENSE.md) © arba-hash
