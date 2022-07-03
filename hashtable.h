#pragma once

#include <bit>
#include <bitset>
#include <cstdint>
#include <memory>
#include <span>
#include <vector>

class Hashtable {
public:
  using ValType = int64_t;

  Hashtable(size_t count) : m_vals(std::bit_ceil(count)) {}

  void Add(std::span<const ValType> vals) noexcept;

  size_t Lookup(std::span<const ValType> vals) const noexcept;

  static constexpr size_t Estimate(size_t count) noexcept {
    const auto num_buckets = std::bit_ceil(count);
    return num_buckets * (sizeof(ValType) + sizeof(ValType) / WordLength);
  }

private:
  static constexpr auto WordLength = 64;

  size_t lookup(ValType val) const noexcept;

  bool is_occupied(size_t pos) const noexcept;
  void set_occupied(size_t pos) noexcept;

  std::vector<ValType> m_vals;
  size_t m_num_buckets = m_vals.size();
  std::unique_ptr<std::bitset<WordLength>[]> m_is_occupied =
      std::make_unique<std::bitset<WordLength>[]>(m_vals.size() / WordLength);
};

constexpr uint64_t Murmur64(uint64_t h) {
  h ^= h >> 33;
  h *= 0xff51afd7ed558ccdL;
  h ^= h >> 33;
  h *= 0xc4ceb9fe1a85ec53L;
  h ^= h >> 33;
  return h;
}
