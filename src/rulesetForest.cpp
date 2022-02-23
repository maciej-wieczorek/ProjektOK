#include "rulesetForest.h"
#include "Utility.h"

int rulesetForest(std::vector<std::vector<int>>& fields, int i, int j)
{

	// wartosci: 0 - brak drzewa, 1-15 - wiek drzewa, 16 - drzewo sie pali

	if (fields[i][j] == 16)
		return 0;

    bool burningNeighbour{ false };
    // sprawdz czy ktorys sasiad sie pali
	if (i > 0)
	{
		if (j > 0 && fields[i - 1][j - 1] == 16)
			burningNeighbour = true;

		if (fields[i - 1][j] == 16)
			burningNeighbour = true;

		if (j + 1 < fields[i].size() && fields[i - 1][j + 1] == 16)
			burningNeighbour = true;
	}

	if (j > 0 && fields[i][j - 1] == 16)
		burningNeighbour = true;

	if (j + 1 < fields[i].size() && fields[i][j + 1] == 16)
		burningNeighbour = true;

	if (i + 1 < fields.size())
	{
		if (j > 0 && fields[i + 1][j - 1] == 16)
			burningNeighbour = true;

		if (fields[i + 1][j] == 16)
			burningNeighbour = true;

		if (j + 1 < fields[i].size() && fields[i + 1][j + 1] == 16)
			burningNeighbour = true;
	}

	if (fields[i][j])
	{
		if (burningNeighbour)
			return 16;

		float f = 0.00002; // szansa uderzenia przez piorun
		if (randomInt(1 / f) == 0)
			return 16;
		else if (fields[i][j] < 15)
			return fields[i][j] + 1;

		return 15;
	}
	else
	{
		float p = 0.002; // szansa powstania nowego drzewa
		if (randomInt(1 / p) == 0)
			return 1;

		return 0;
	}
}

sf::Color colorForest(int value, int maxValue)
{
	sf::Color color = sf::Color(10, 69, 5, 255);
	if (value == 16)
		return sf::Color::Red;
	else
	{
		int alpha = ((float)value / (float)maxValue) * 255;
		color = sf::Color(color.r, color.g, color.b, alpha);
		return color;
	}
}