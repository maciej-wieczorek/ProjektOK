#include "rulesetElementaryCA.h"

#include <cmath>

bool rulesetElementaryCA(std::vector<bool>& fields, int i, unsigned char rule)
{
    bool l, c, r;
    if (i > 0)
        l = fields[i - 1];
    else
        l = 0;
    c = fields[i];
    if (i < (fields.size() - 1))
        r = fields[i + 1];
    else
        r = 0;

    return rule & static_cast<unsigned char>(pow(2, (l * 4) + (2 * c) + r));
}