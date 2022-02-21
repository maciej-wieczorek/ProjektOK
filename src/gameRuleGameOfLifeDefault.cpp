#include "gameRuleGameOfLifeDefault.h"

bool gameRuleGameOfLifeDefault(std::vector<std::vector<bool> > &fields, int i, int j)
{
	int count{ 0 };
	if (i > 0)
	{
		if (j > 0 && fields[i - 1][j - 1])
			count++;

		if (fields[i - 1][j])
			count++;

		if (j + 1 < fields[i].size() && fields[i - 1][j + 1])
			count++;
	}

	if (j > 0 && fields[i][j - 1])
		count++;

	if (j + 1 < fields[i].size() && fields[i][j + 1])
		count++;

	if (i + 1 < fields.size())
	{
		if (j > 0 && fields[i + 1][j - 1])
			count++;

		if (fields[i + 1][j])
			count++;

		if (j + 1 < fields[i].size() && fields[i + 1][j + 1])
			count++;
	}

	if (fields[i][j])
	{
		if (count <= 1 || count >= 4)
			return false;
		return true;
	}
	else if (count == 3)
	{
		return true;
	}
	return false;
}