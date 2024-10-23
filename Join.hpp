#include <string>
#include <vector>
#include <unordered_map>
#include <cmath>

using join_pred = std::pair<std::string, std::string>;
using scan_pred = std::string;
using card_t = std::unordered_map<std::string, int>;

class Joins
{
public:
    struct Step
    {
        private:
            short left = 0, right = 0;
            double cost = 0, rows = 0;
    };

    Joins(int n, const card_t &card, std::vector<Step> &tree);
    ~Joins();

private:
    std::vector<Step> tree;
    card_t card; // {1.a: card}
    std::vector<join_pred> join_preds;
    std::vector<scan_pred> scan_preds;
};
