#include <cstdint>

// clang-format off
//===========================================================================//
// From https://github.com/aappleby/smhasher/blob/master/src/MurmurHash2.cpp //
//   to compare with arba implementation.                                    //
// (commit 0ff96f7835817a27d0487325b6c16033e2992eb5)                         //
//===========================================================================//

#if defined(_MSC_VER)

#define BIG_CONSTANT(x) (x)

// Other compilers

#else	// defined(_MSC_VER)

#define BIG_CONSTANT(x) (x##LLU)

#endif // !defined(_MSC_VER)

//-----------------------------------------------------------------------------
// MurmurHash2, 64-bit versions, by Austin Appleby

// 64-bit hash for 64-bit platforms

uint64_t MurmurHash64A ( const void * key, int len, uint64_t seed )
{
    const uint64_t m = BIG_CONSTANT(0xc6a4a7935bd1e995);
    const int r = 47;

    uint64_t h = seed ^ (len * m);

    const uint64_t * data = static_cast<const uint64_t*>(key);
    const uint64_t * end = data + (len/8);

    while(data != end)
    {
        uint64_t k = *data++;

        k *= m;
        k ^= k >> r;
        k *= m;

        h ^= k;
        h *= m;
    }

    const unsigned char * data2 = reinterpret_cast<const unsigned char*>(data);

    switch(len & 7)
    {
    case 7: h ^= uint64_t(data2[6]) << 48;
        [[fallthrough]];
    case 6: h ^= uint64_t(data2[5]) << 40;
        [[fallthrough]];
    case 5: h ^= uint64_t(data2[4]) << 32;
        [[fallthrough]];
    case 4: h ^= uint64_t(data2[3]) << 24;
        [[fallthrough]];
    case 3: h ^= uint64_t(data2[2]) << 16;
        [[fallthrough]];
    case 2: h ^= uint64_t(data2[1]) << 8;
        [[fallthrough]];
    case 1: h ^= uint64_t(data2[0]);
        h *= m;
    };

    h ^= h >> r;
    h *= m;
    h ^= h >> r;

    return h;
}

//===========================================================================//
// clang-format on

#include <arba/hash/murmur_hash_2.hpp>

#include <gtest/gtest.h>

#include <cstdlib>

// murmur_hash_2_u64 (endianness_specific):

TEST(murmur_hash_2_compat_smhasher_tests, murmur_hash_2_u64__eq_data_specific__eq)
{
    std::array<std::uint8_t, 8> bytes{ 102, 26, 64, 25, 55, 224, 146, 246 };
    uint64_t hash = hash::murmur_hash_2_u64(bytes, cppx::endianness_specific);
    uint64_t hash2 = MurmurHash64A(bytes.data(), bytes.size(), hash::murmur_hash_2_default_seed);
    ASSERT_EQ(hash, hash2);
}

// murmur_hash_2_u64 (endianness_specific, multi range of bytes):

TEST(murmur_hash_2_compat_smhasher_tests, murmur_hash_2_u64__multi_range_specific__eq)
{
    std::array<std::uint8_t, 8> bytes_p1{ 102, 26, 64, 25, 55, 224, 146, 246 };
    std::array<std::uint8_t, 10> bytes_p2{ 201, 62, 46, 52, 55, 122, 141, 207, 15, 47 };
    std::array<std::span<std::uint8_t>, 2> bytes_range{ std::span(bytes_p1), std::span(bytes_p2) };
    uint64_t hash = hash::murmur_hash_2_u64(bytes_range, cppx::endianness_specific);
    std::array<std::uint8_t, 18> other_bytes{ 102, 26, 64, 25, 55,  224, 146, 246, 201,
                                              62,  46, 52, 55, 122, 141, 207, 15,  47 };
    uint64_t hash2 = MurmurHash64A(other_bytes.data(), other_bytes.size(), hash::murmur_hash_2_default_seed);
    ASSERT_EQ(hash, hash2);
}
