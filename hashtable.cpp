#include <cassert>

#include "hashtable.h"

bool Hashtable::is_occupied(size_t pos) const noexcept {
  const auto word = pos / WordLength;
  const auto bit = pos % WordLength;

  return m_is_occupied[word][bit];
}

void Hashtable::set_occupied(size_t pos) noexcept {
  const auto word = pos / WordLength;
  const auto bit = pos % WordLength;

  m_is_occupied[word][bit] = true;
}

size_t Hashtable::lookup(ValType val) const noexcept {
  const auto hash = Murmur64(val);
  size_t bucket = hash & (m_num_buckets - 1);

  while (is_occupied(bucket) && m_vals[bucket] != val) {
    bucket = (bucket + 1) & (m_num_buckets - 1);
  }

  return bucket;
}

size_t Hashtable::Lookup(std::span<const ValType> vals) const noexcept {
  size_t num_matched = 0;

  for (auto val : vals) {
    const auto bucket = lookup(val);
    if (is_occupied(bucket))
      num_matched++;
  }

  return num_matched;
}

void Hashtable::Add(std::span<const ValType> vals) noexcept {
  for (auto val : vals) {
    const auto bucket = lookup(val);

    set_occupied(bucket);
    m_vals[bucket] = val;
  }
}