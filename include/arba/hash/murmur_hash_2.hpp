#pragma once

#include <arba/cppx/policy/endianness_policy.hpp>

#include <array>
#include <cstdint>
#include <numeric>
#include <ranges>
#include <span>

inline namespace arba
{
namespace hash
{

constexpr uint64_t murmur_hash_2_default_seed = 6'364'136'223'846'793'005ull;

namespace private_
{
[[nodiscard]] uint64_t murmur_hash_2_u64_b_(std::size_t size, uint64_t seed);
[[nodiscard]] uint64_t murmur_hash_2_u64_e_(uint64_t h);

[[nodiscard]] uint64_t murmur_hash_2_u64_specific_h_(std::span<const std::byte> bytes, uint64_t h);
[[nodiscard]] uint64_t murmur_hash_2_u64_specific_(std::span<const std::byte> bytes, uint64_t seed);

[[nodiscard]] uint64_t murmur_hash_2_u64_neutral_h_(std::span<const std::byte> bytes, uint64_t h);
[[nodiscard]] uint64_t murmur_hash_2_u64_neutral_(std::span<const std::byte> bytes, uint64_t seed);

[[nodiscard]] std::array<uint8_t, 16> murmur_hash_2_16u8_neutral_(std::span<const std::byte> bytes, uint64_t seed);
} // namespace private_

// murmur_hash_2_u64:

[[nodiscard]] inline uint64_t murmur_hash_2_u64(std::span<const std::byte> bytes,
                                                cppx::EndiannessPolicy auto endianness_policy,
                                                uint64_t seed = murmur_hash_2_default_seed)
{
    if constexpr (std::is_same_v<decltype(endianness_policy), cppx::endianness_specific_t>)
    {
        return private_::murmur_hash_2_u64_specific_(bytes, seed);
    }
    else
    {
        return private_::murmur_hash_2_u64_neutral_(bytes, seed);
    }
}

template <std::ranges::contiguous_range crange, cppx::EndiannessPolicy EndiannessPolicyT>
    requires(sizeof(std::ranges::range_value_t<crange>) == 1)
            && std::is_convertible_v<std::ranges::range_value_t<crange>, uint8_t>
[[nodiscard]] inline uint64_t murmur_hash_2_u64(const crange& bytes, EndiannessPolicyT endianness_policy,
                                                uint64_t seed = murmur_hash_2_default_seed)
{
    return murmur_hash_2_u64(std::as_bytes(std::span(bytes)), endianness_policy, seed);
}

template <std::ranges::range RangeT, cppx::EndiannessPolicy EndiannessPolicyT>
    requires(std::ranges::contiguous_range<std::ranges::range_value_t<RangeT>>)
[[nodiscard]] inline uint64_t murmur_hash_2_u64(RangeT bytes_range, EndiannessPolicyT endianness_policy,
                                                uint64_t seed = murmur_hash_2_default_seed)
{
    const std::size_t total_size =
        std::transform_reduce(std::ranges::begin(bytes_range), std::ranges::end(bytes_range), 0, std::plus{},
                              [](const auto& bytes) { return bytes.size(); });
    uint64_t h = private_::murmur_hash_2_u64_b_(total_size, seed);
    for (auto bytes : bytes_range)
    {
        if constexpr (std::is_same_v<decltype(endianness_policy), cppx::endianness_specific_t>)
            h = private_::murmur_hash_2_u64_specific_h_(std::as_bytes(std::span(bytes)), h);
        else
            h = private_::murmur_hash_2_u64_neutral_h_(std::as_bytes(std::span(bytes)), h);
    }
    return private_::murmur_hash_2_u64_e_(h);
}

// murmur_hash_2_16u8:

[[nodiscard]] inline std::array<uint8_t, 16> murmur_hash_2_16u8(std::span<const std::byte> bytes,
                                                                cppx::endianness_neutral_t,
                                                                uint64_t seed = murmur_hash_2_default_seed)
{
    return private_::murmur_hash_2_16u8_neutral_(bytes, seed);
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
