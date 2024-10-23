#include "Join.hpp"
#define MAX(i,j) ((i > j) ? i : j)

Joins::Joins(int n, const card_t &card_, std::vector<Step> &tree_): card(std::move(card_)), tree(std::move(tree_)) {
    tree.reserve(pow(2, n) + 1);
}

double Joins::many_rows(int index_table)
{
    struct Step & scan = tree[index_table];
    int sum_card = 0;
    for(const auto& it : join_preds)        //count multi_card (card(join-preds))
    {
        if(atoi(it.first.c_str()) == index_table)
            sum_card += card[it.first + '.' + it.second];   //it.first-number of tables    it.second-predicat
    }
    return (sum_card) ? scan.rows/sum_card : 0;         //rows(<scan_with_multi_pred>)
}

double Joins::all_rows(int index_join)  //Возможно нужно было использовать вектор сканов
{
    struct Step & result = tree[index_join];
    int sum_card = 0, i_left = result.left, i_right = result.right;
    std::string left, right;
    for(const auto& it_left : join_preds)
    {
        if(atoi(it_left.first.c_str()) == i_left)
        {
            //поиск второго и макс над ними
            for(const auto& it_right : join_preds)
            {
                if(atoi(it_right.first.c_str()) == i_right)
                    sum_card += MAX(card[it_left.first + '.' + it_left.second], card[it_right.first + '.' + it_right.second]);
            }
        }
    }
    return (sum_card) ? (tree[i_left].rows * tree[i_right].rows / sum_card) : 0;
}

double Joins::cost_nestloop_inner(int index_inner)
{
    struct Step & inner = tree[index_inner];
    struct Step & left_subtree = tree[inner.left];
    struct Step & right_subtree = tree[inner.right];
    return left_subtree.cost + right_subtree.cost + right_subtree.rows * 1.1 + (left_subtree.rows - 1) * right_subtree.rows + all_rows(index_inner) * 0.1;
}