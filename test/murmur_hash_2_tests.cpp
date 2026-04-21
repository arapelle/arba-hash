#include <arba/hash/murmur_hash_2.hpp>
#include <arba/hash/murmur_hash.hpp>

#include <gtest/gtest.h>

#include <cstdlib>

// murmur_hash_2_u64 (endianness_specific):

TEST(murmur_hash_2_tests, murmur_hash_2_u64__eq_data_specific__eq)
{
    std::array<std::uint8_t, 8> bytes{ 102, 26, 64, 25, 55, 224, 146, 246 };
    uint64_t hash = hash::murmur_hash_2_u64(bytes, cppx::endianness_specific);
    uint64_t hash2 = hash::murmur_hash_2_u64(bytes, cppx::endianness_specific);
    ASSERT_EQ(hash, hash2);
}

TEST(murmur_hash_2_tests, murmur_hash_2_u64__compat_specific__eq)
{
    std::array<std::uint8_t, 8> bytes{ 102, 26, 64, 25, 55, 224, 146, 246 };
    uint64_t hash = hash::murmur_hash_2_u64(bytes, cppx::endianness_specific);
    uint64_t hash2 = hash::murmur_hash_64(bytes);
    ASSERT_EQ(hash, hash2);
}

TEST(murmur_hash_2_tests, murmur_hash_2_u64__ne_data_specific__ne)
{
    std::array<std::uint8_t, 8> bytes{ 102, 26, 64, 25, 55, 224, 146, 246 };
    uint64_t hash = hash::murmur_hash_2_u64(bytes, cppx::endianness_specific);
    std::array<std::uint8_t, 8> other_bytes{ 103, 26, 64, 25, 55, 224, 146, 246 };
    uint64_t hash2 = hash::murmur_hash_2_u64(other_bytes, cppx::endianness_specific);
    ASSERT_NE(hash, hash2);
}

TEST(murmur_hash_2_tests, murmur_hash_2_u64__neq_seed_specific__ne)
{
    std::array<std::uint8_t, 8> bytes{ 102, 26, 64, 25, 55, 224, 146, 246 };
    uint64_t hash = hash::murmur_hash_2_u64(bytes, cppx::endianness_specific);
    uint64_t hash2 = hash::murmur_hash_2_u64(bytes, cppx::endianness_specific, 8'467'930'056'364'136'223ULL);
    ASSERT_NE(hash, hash2);
}

TEST(murmur_hash_2_tests, murmur_hash_2_u64__eq_ranges_specific__eq)
{
    std::array<std::uint8_t, 8> a_bytes{ 102, 26, 64, 25, 55, 224, 146, 246 };
    std::vector<std::uint8_t> v_bytes{ 102, 26, 64, 25, 55, 224, 146, 246 };
    uint64_t hash = hash::murmur_hash_2_u64(a_bytes, cppx::endianness_specific);
    uint64_t hash2 = hash::murmur_hash_2_u64(v_bytes, cppx::endianness_specific);
    ASSERT_EQ(hash, hash2);
}

// murmur_hash_2_u64 (endianness_specific, multi range of bytes):

TEST(murmur_hash_2_tests, murmur_hash_2_u64__multi_range_specific__eq)
{
    std::array<std::uint8_t, 8> bytes_p1{ 102, 26, 64, 25, 55, 224, 146, 246 };
    std::array<std::uint8_t, 10> bytes_p2{ 201, 62, 46, 52, 55, 122, 141, 207, 15, 47 };
    std::array<std::span<std::uint8_t>, 2> bytes_range{ std::span(bytes_p1), std::span(bytes_p2) };
    uint64_t hash = hash::murmur_hash_2_u64(bytes_range, cppx::endianness_specific);
    std::array<std::uint8_t, 18> other_bytes{ 102, 26, 64, 25, 55, 224, 146, 246, 201, 62, 46, 52, 55, 122, 141, 207, 15, 47 };
    uint64_t hash2 = hash::murmur_hash_2_u64(other_bytes, cppx::endianness_specific);
    ASSERT_EQ(hash, hash2);
}

// murmur_hash_2_u64 (endianness_neutral):

TEST(murmur_hash_2_tests, murmur_hash_2_u64__eq_data_neutral__eq)
{
    std::array<std::uint8_t, 8> bytes{ 102, 26, 64, 25, 55, 224, 146, 246 };
    uint64_t hash = hash::murmur_hash_2_u64(bytes, cppx::endianness_neutral);
    uint64_t hash2 = hash::murmur_hash_2_u64(bytes, cppx::endianness_neutral);
    ASSERT_EQ(hash, hash2);
    ASSERT_EQ(hash, 8'424'698'443'104'796'602ull);
}

TEST(murmur_hash_2_tests, murmur_hash_2_u64__ne_data_neutral__ne)
{
    std::array<std::uint8_t, 8> bytes{ 102, 26, 64, 25, 55, 224, 146, 246 };
    uint64_t hash = hash::murmur_hash_2_u64(bytes, cppx::endianness_neutral);
    std::array<std::uint8_t, 8> other_bytes{ 103, 26, 64, 25, 55, 224, 146, 246 };
    uint64_t hash2 = hash::murmur_hash_2_u64(other_bytes, cppx::endianness_neutral);
    ASSERT_NE(hash, hash2);
}

TEST(murmur_hash_2_tests, murmur_hash_2_u64__ne_seed_neutral__ne)
{
    std::array<std::uint8_t, 8> bytes{ 102, 26, 64, 25, 55, 224, 146, 246 };
    uint64_t hash = hash::murmur_hash_2_u64(bytes, cppx::endianness_neutral);
    uint64_t hash2 = hash::murmur_hash_2_u64(bytes, cppx::endianness_neutral, 8'467'930'056'364'136'223ULL);
    ASSERT_NE(hash, hash2);
}

TEST(murmur_hash_2_tests, murmur_hash_2_u64__eq_ranges_neutral__eq)
{
    std::array<std::uint8_t, 8> a_bytes{ 102, 26, 64, 25, 55, 224, 146, 246 };
    std::vector<std::uint8_t> v_bytes{ 102, 26, 64, 25, 55, 224, 146, 246 };
    uint64_t hash = hash::murmur_hash_2_u64(a_bytes, cppx::endianness_neutral);
    uint64_t hash2 = hash::murmur_hash_2_u64(v_bytes, cppx::endianness_neutral);
    ASSERT_EQ(hash, hash2);
}

// murmur_hash_2_u64 (endianness_neutral, multi range of bytes):

TEST(murmur_hash_2_tests, murmur_hash_2_u64__multi_range_neutral__eq)
{
    std::array<std::uint8_t, 8> bytes_p1{ 102, 26, 64, 25, 55, 224, 146, 246 };
    std::array<std::uint8_t, 10> bytes_p2{ 201, 62, 46, 52, 55, 122, 141, 207, 15, 47 };
    std::array<std::span<std::uint8_t>, 2> bytes_range{ std::span(bytes_p1), std::span(bytes_p2) };
    uint64_t hash = hash::murmur_hash_2_u64(bytes_range, cppx::endianness_neutral);
    std::array<std::uint8_t, 18> other_bytes{ 102, 26, 64, 25, 55, 224, 146, 246, 201, 62, 46, 52, 55, 122, 141, 207, 15, 47 };
    uint64_t hash2 = hash::murmur_hash_2_u64(other_bytes, cppx::endianness_neutral);
    ASSERT_EQ(hash, hash2);
}

// murmur_hash_2_16u8 (endianness_neutral):

TEST(murmur_hash_2_tests, murmur_hash_2_16u8__eq_data_neutral__eq)
{
    std::array<std::uint8_t, 8> bytes{ 102, 26, 64, 25, 55, 224, 146, 246 };
    std::array<std::uint8_t, 16> hash = hash::murmur_hash_2_16u8(bytes, cppx::endianness_neutral);
    std::array<std::uint8_t, 16> hash2 = hash::murmur_hash_2_16u8(bytes, cppx::endianness_neutral);
    ASSERT_EQ(hash, hash2);
    for (uint8_t i = 0; i < 8; ++i)
        ASSERT_NE(hash[i], hash[i + 8]);
}

TEST(murmur_hash_2_tests, murmur_hash_2_16u8__ne_data_neutral__ne)
{
    std::array<std::uint8_t, 8> bytes{ 102, 26, 64, 25, 55, 224, 146, 246 };
    std::array<std::uint8_t, 16> hash = hash::murmur_hash_2_16u8(bytes, cppx::endianness_neutral);
    std::array<std::uint8_t, 8> other_bytes{ 103, 26, 64, 25, 55, 224, 146, 246 };
    std::array<std::uint8_t, 16> hash2 = hash::murmur_hash_2_16u8(other_bytes, cppx::endianness_neutral);
    ASSERT_NE(hash, hash2);
}

TEST(murmur_hash_2_tests, murmur_hash_2_16u8__ne_seed_neutral__ne)
{
    std::array<std::uint8_t, 8> bytes{ 102, 26, 64, 25, 55, 224, 146, 246 };
    std::array<std::uint8_t, 16> hash = hash::murmur_hash_2_16u8(bytes, cppx::endianness_neutral);
    std::array<std::uint8_t, 16> hash2 = hash::murmur_hash_2_16u8(bytes, cppx::endianness_neutral, 8'467'930'056'364'136'223ULL);
    ASSERT_NE(hash, hash2);
}

TEST(murmur_hash_2_tests, murmur_hash_2_16u8__eq_ranges_neutral__eq)
{
    std::array<std::uint8_t, 8> a_bytes{ 102, 26, 64, 25, 55, 224, 146, 246 };
    std::vector<std::uint8_t> v_bytes{ 102, 26, 64, 25, 55, 224, 146, 246 };
    std::array<std::uint8_t, 16> hash = hash::murmur_hash_2_16u8(a_bytes, cppx::endianness_neutral);
    std::array<std::uint8_t, 16> hash2 = hash::murmur_hash_2_16u8(v_bytes, cppx::endianness_neutral);
    ASSERT_EQ(hash, hash2);
}
