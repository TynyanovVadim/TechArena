#include <string>
#include <vector>
#include <unordered_map>
#include <cmath>

using join_pred = std::unordered_map<int, std::vector<std::pair<std::string, std::string>>>; // {101: [a, b]}
using scan_pred = std::vector<std::string>; // [1.a, 1.b, ... ]
using card_t = std::unordered_map<std::string, int>; // {1.a: card}

class Step
{
    public:
        short left = 0, right = 0;
        double cost = 0, rows = 0;
};

class Joins
{
public:

    Joins(int n, card_t &&card_, std::vector<Step> &&tree_, scan_pred &&scan_preds_, join_pred &&join_preds_);

    void all_rows(int index_left, int index_right);

    void cost_nestloop_inner(int index_left, int index_right);

    void print() const;

    // ~Joins();

private:
    std::vector<Step> tree;
    card_t card; // {1.a: card}
    join_pred join_preds;
    scan_pred scan_preds;
};
