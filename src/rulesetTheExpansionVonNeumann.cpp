#include "rulesetTheExpansionVonNeumann.h"

#include <cmath>

int rulesetTheExpansionVonNeumann(std::vector<std::vector<int> >& fields, int i, int j)
{
	int comparisonNum = 70;
	int sum{ 0 };
	int newValue{};
	float avg{};

	int r = 3;

	for (int x = -r; x <= r; x++)
	{
		for (int y = -r; y <= r; y++)
		{
			int a = i - x;
			int b = j - y;
			if (abs(x) + abs(y) <= r)
				if (a >= 0 && a < fields.size() && b >= 0 && b < fields[i].size())
					sum += fields[a][b];
		}
	}

	avg = static_cast<float>(sum) / 24.f;

	if (fields[i][j] < comparisonNum) // dead
	{
		if (avg >= 15.f && avg <= 35.f)
			newValue = fields[i][j] + 2;
		else
			newValue = 0;
	}
	else // alive
	{
		if (avg >= 70.f && avg <= 255.f)
			newValue = 0;
		else
			newValue = fields[i][j] + 2;
	}
	if (newValue > 255)
		return 255;
	return newValue;
}

sf::Color colorTheExpansionVonNeumann(int value, int maxValue)
{
	int alpha = ((float)value / (float)maxValue) * 255;
	return sf::Color(255, 255, 255, alpha);
}