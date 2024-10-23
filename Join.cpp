#include "Join.hpp"

Joins::Joins(int n, const card_t &card_, std::vector<Step> &tree_): card(std::move(card_)), tree(std::move(tree_)) {
    tree.reserve(pow(2, n) + 1);
}