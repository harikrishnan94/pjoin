#include "join.h"
#include "hashtable.h"

size_t Join(std::span<const int64_t> rel1, std::span<const int64_t> rel2) {
  const auto small_rel = rel1.size() < rel2.size() ? rel1 : rel2;
  const auto big_rel = rel1.size() >= rel2.size() ? rel1 : rel2;
  Hashtable ht(small_rel.size());

  ht.Add(small_rel);
  return ht.Lookup(big_rel);
}
