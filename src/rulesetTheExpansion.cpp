#include "rulesetTheExpansion.h"

int rulesetTheExpansion(std::vector<std::vector<int> >& fields, int i, int j)
{
	int comparisonNum = 70;
	int sum{ 0 };
	int newValue{};
	float avg{};

	if (i > 0)
	{
		if (j > 0)
			sum += fields[i-1][j-1];

		sum += fields[i - 1][j];

		if (j + 1 < fields[i].size())
			sum += fields[i - 1][j + 1];
	}

	if (j > 0)
		sum += fields[i][j - 1];

	if (j + 1 < fields[i].size())
		sum += fields[i][j + 1];

	if (i + 1 < fields.size())
	{
		if (j > 0)
			sum += fields[i + 1][j - 1];

		sum += fields[i + 1][j];

		if (j + 1 < fields[i].size())
			sum += fields[i + 1][j + 1];
	}

	avg = static_cast<float>(sum) / 8.f;

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

sf::Color colorTheExpansion(int value, int maxValue)
{
	int alpha = ((float)value / (float)maxValue) * 255;
	return sf::Color(255, 255, 255, alpha);
}