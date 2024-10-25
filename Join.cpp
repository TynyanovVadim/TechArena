#include "Join.hpp"
#include <iostream>
#include <bits/stdc++.h>

Joins::Joins(int n, card_t &&card_, std::vector<Step> &&tree_, scan_pred &&scan_preds_, join_pred &&join_preds_):
 tree(tree_), card(card_), join_preds(join_preds_), scan_preds(scan_preds_) {
    if (scan_preds.size() != 0) {
        for (auto attr: scan_preds) {
            int i = attr.find('.');
            int table_num = atoi(attr.substr(0, i).c_str());
            tree[1 << (table_num - 1)].rows /= card[attr];
            tree[1 << (table_num - 1)].cost *= 2;
        }
    }
 }

void Joins::print() const {
    for (auto step: tree) {
        std::cout << step.rows << '\t' << step.cost << "\n";
    }
 }


void Joins::all_rows(int index_left, int index_right)
{
    int result_index = index_left ^ index_right;
    struct Step & result = tree[result_index];
    result.left = index_left;
    result.right = index_right;
    int sum_card = 0;
    std::string pred_left, pred_right;

    std::vector<std::pair<std::string, std::string>> & vec_join = join_preds[result_index];
    for(const auto& item : vec_join)
    {
        pred_left = std::to_string(index_left) + '.' + item.first;
        pred_right = std::to_string(index_right) + '.' + item.second;
        sum_card += std::max(card[pred_left], card[pred_right]);
    }
    result.rows = tree[index_left].rows * tree[index_right].rows / sum_card;
}

void Joins::cost_nestloop_inner(int index_left, int index_right)
{
    int inner_index = index_left ^ index_right;
    struct Step & inner = tree[inner_index];
    struct Step & left_subtree = tree[index_left];
    struct Step & right_subtree = tree[index_right];

    inner.cost = left_subtree.cost + right_subtree.cost + right_subtree.rows * 1.1 + (left_subtree.rows - 1) * right_subtree.rows + inner.rows * 0.1;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<Step> tree_(pow(2, n) + 1);
    for (int i = 0; i < n; i++) {
        Step tmp = Step();
        std::cin >> tmp.rows;
        tmp.cost = tmp.rows;
        tree_[1 << i] = std::move(tmp);
    }

    int m;
    std::cin >> m;

    card_t card_;
    for (int i = 0; i < m; ++i) {
        std::string table, attr;
        int card;
        std::cin >> table >> attr >> card;
        card_[table + '.' + attr] = card;
    }


    std::cin >> m;
    scan_pred scan_preds_;
    for (int i = 0; i < m; ++i) {
        std::string table, attr;
        std::cin >> table >> attr;

        scan_preds_.push_back(std::move(table + '.' + attr));
    }

    std::cin >> m;
    join_pred join_preds_;
    join_preds_.reserve(m);
    for (int i = 0; i < m; ++i) {
        std::string attr1, attr2;
        int table1, table2;
        std::cin >> table1 >> table2 >> attr1 >> attr2;

        join_preds_[(1 << (table1 - 1)) ^ (1 << (table2 -1))].push_back(std::move(std::pair<std::string, std::string>(attr1, attr2)));
    }

    Joins solver(n, std::move(card_), std::move(tree_), std::move(scan_preds_), std::move(join_preds_));
    //test for inner 1^2
    solver.all_rows(1, 2);
    solver.cost_nestloop_inner(1, 2);

    solver.print();

    return 0;
}

/*4
10 12 15 8
5
1 a 3
2 b 5
3 b 10
2 c 1
4 d 5
0
3
1 2 a b
1 3 a b
2 4 c d*/