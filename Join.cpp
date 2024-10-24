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
        }
    }
 }

 void Joins::print() const {
    for (auto step: tree) {
        std::cout << step.rows << "\n";
    }
 }

// double Joins::many_rows(int index_table)
// {
//     struct Step & scan = tree[index_table];
//     int sum_card = 0;
//     for(const auto& it : join_preds)        //count multi_card (card(join-preds))
//     {
//         if(atoi(it.first.c_str()) == index_table)
//             sum_card += card[it.first + '.' + it.second];   //it.first-number of tables    it.second-predicat
//     }
//     return (sum_card) ? scan.rows/sum_card : 0;         //rows(<scan_with_multi_pred>)
// }

// double Joins::all_rows(int index_join)  //Возможно нужно было использовать вектор сканов
// {
//     struct Step & result = tree[index_join];
//     int sum_card = 0, i_left = result.left, i_right = result.right;
//     std::string left, right;
//     for(const auto& it_left : join_preds)
//     {
//         if(atoi(it_left.first.c_str()) == i_left)
//         {
//             //поиск второго и макс над ними
//             for(const auto& it_right : join_preds)
//             {
//                 if(atoi(it_right.first.c_str()) == i_right)
//                     sum_card += std::max(card[it_left.first + '.' + it_left.second], card[it_right.first + '.' + it_right.second]);
//             }
//         }
//     }
//     return (sum_card) ? (tree[i_left].rows * tree[i_right].rows / sum_card) : 0;
// }

// double Joins::cost_nestloop_inner(int index_inner)
// {
//     struct Step & inner = tree[index_inner];
//     struct Step & left_subtree = tree[inner.left];
//     struct Step & right_subtree = tree[inner.right];
//     return left_subtree.cost + right_subtree.cost + right_subtree.rows * 1.1 + (left_subtree.rows - 1) * right_subtree.rows + all_rows(index_inner) * 0.1;
// }

int main() {
    int n;
    std::cin >> n;
    std::vector<Step> tree_(pow(2, n) + 1);
    for (int i = 0; i < n; i++) {
        Step tmp = Step();
        std::cin >> tmp.rows;
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

        join_preds_[(1 << (table1 - 1)) ^ (1 << (table2 -1))] = std::move(std::pair<std::string, std::string>(attr1, attr2));
    }

    Joins solver(n, std::move(card_), std::move(tree_), std::move(scan_preds_), std::move(join_preds_));

    for (int i = 1; i < pow(2, n) + 2; ++i) {
        int k = __builtin_popcount(i);
        if (k == 1) continue;
        for (int left = 1; left < left; ++left) {
            int right = i ^ left;
        }
    }

    solver.print();

    return 0;
}

