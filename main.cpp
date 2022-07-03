#include <charconv>
#include <chrono>
#include <cstring>
#include <iostream>
#include <random>

#include "join.h"

std::pair<std::vector<int64_t>, std::vector<int64_t>>
GenerateRels(size_t rel1_size, size_t rel2_size, int selectivity) {
  const auto small_rel_sz = std::min(rel1_size, rel2_size);
  const auto big_rel_sz = std::max(rel1_size, rel2_size);

  std::vector<int64_t> small_rel(small_rel_sz);
  std::vector<int64_t> big_rel(big_rel_sz);
  selectivity = std::clamp(selectivity, 1, 100);

  std::mt19937_64 gen(std::random_device{}());

  std::iota(small_rel.begin(), small_rel.end(), 1);
  std::shuffle(small_rel.begin(), small_rel.end(), gen);

  std::uniform_int_distribution<size_t> small_rel_ind_dist(0, small_rel_sz - 1);
  std::uniform_int_distribution<int64_t> big_mismatch_dist(small_rel_sz + 1);
  std::uniform_int_distribution<int> select_dist(1, 100);

  for (auto &val : big_rel) {
    if (select_dist(gen) <= selectivity) {
      val = small_rel[small_rel_ind_dist(gen)];
    } else {
      val = big_mismatch_dist(gen);
    }
  }

  return {std::move(small_rel), std::move(big_rel)};
}

int main(int argc, char *argv[]) {
  size_t rel1_sz;
  size_t rel2_sz;
  int selectivity;

  std::from_chars(argv[1], argv[1] + strlen(argv[1]), rel1_sz);
  std::from_chars(argv[2], argv[2] + strlen(argv[2]), rel2_sz);
  std::from_chars(argv[3], argv[3] + strlen(argv[3]), selectivity);

  auto [rel1, rel2] = GenerateRels(rel1_sz, rel2_sz, selectivity);
  auto start = std::chrono::steady_clock::now();
  const auto num_matches = Join(rel1, rel2);
  auto end = std::chrono::steady_clock::now();

  std::cout << "# Matches = " << num_matches << "\n";
  std::cout << duration_cast<std::chrono::milliseconds>(end - start).count()
            << " ms\n";
}