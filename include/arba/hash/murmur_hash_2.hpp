#pragma once

#include <arba/cppx/policy/endianness_policy.hpp>

#include <array>
#include <span>
#include <cstdint>
#include <ranges>

inline namespace arba
{
namespace hash
{

constexpr uint64_t murmur_hash_2_default_seed = 6'364'136'223'846'793'005ull;

namespace private_
{
constexpr uint64_t murmur_hash_2_m = 0xc6a4a7935bd1e995ull;

[[nodiscard]] uint64_t murmur_hash_2_u64_specific_(std::span<const std::byte> bytes, uint64_t start);
[[nodiscard]] uint64_t murmur_hash_2_u64_neutral_(std::span<const std::byte> bytes, uint64_t start);
[[nodiscard]] std::array<uint8_t, 16> murmur_hash_2_16u8_neutral_(std::span<const std::byte> bytes, uint64_t seed);
}

// murmur_hash_2_u64:

[[nodiscard]] inline uint64_t murmur_hash_2_u64(std::span<const std::byte> bytes,
                                                cppx::EndiannessPolicy auto endianness_policy,
                                                uint64_t seed = murmur_hash_2_default_seed)
{
    const uint64_t start = seed ^ (bytes.size() * private_::murmur_hash_2_m);
    if constexpr (std::is_same_v<decltype(endianness_policy), cppx::endianness_specific_t>)
    {
        return private_::murmur_hash_2_u64_specific_(bytes, start);
    }
    else
    {
        return private_::murmur_hash_2_u64_neutral_(bytes, start);
    }
}

template <std::ranges::contiguous_range crange, cppx::EndiannessPolicy EndiannessPolicyT>
    requires(sizeof(std::ranges::range_value_t<crange>) == 1)
    && std::is_convertible_v<std::ranges::range_value_t<crange>, uint8_t>
    [[nodiscard]] inline uint64_t murmur_hash_2_u64(const crange& bytes,
                                                    EndiannessPolicyT endianness_policy,
                                                    uint64_t seed = murmur_hash_2_default_seed)
{
    return murmur_hash_2_u64(std::as_bytes(std::span(bytes)), endianness_policy, seed);
}

// murmur_hash_2_16u8:

[[nodiscard]] inline std::array<uint8_t, 16> murmur_hash_2_16u8(std::span<const std::byte> bytes,
                                                                cppx::endianness_neutral_t,
                                                                uint64_t seed = murmur_hash_2_default_seed)
{
    const uint64_t start = seed ^ (bytes.size() * private_::murmur_hash_2_m);
    return private_::murmur_hash_2_16u8_neutral_(bytes, start);
}

template <std::ranges::contiguous_range crange>
    requires(sizeof(std::ranges::range_value_t<crange>) == 1)
    && std::is_convertible_v<std::ranges::range_value_t<crange>, uint8_t>
    [[nodiscard]] inline std::array<uint8_t, 16> murmur_hash_2_16u8(const crange& bytes,
                                                                    cppx::endianness_neutral_t endianness_policy,
                                                                    uint64_t seed = murmur_hash_2_default_seed)
{
    return murmur_hash_2_16u8(std::as_bytes(std::span(bytes)), endianness_policy, seed);
}

} // namespace hash
} // namespace arba
