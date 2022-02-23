#pragma once
#include "Grid.h"

class Grid2D : public Grid
{
public:

	Grid2D(sf::Vector2u gridSize, float fieldSize,
		sf::Color aliveCellColor = sf::Color::Black, sf::Color deadCellColor = sf::Color::White);

	virtual void generate();
	virtual void colorQuad(sf::Vector2f pos);
	virtual void unColorQuad(sf::Vector2f pos);
	virtual void update();
	virtual void clear();

	std::pair<int, int> fieldFrom2d(sf::Vector2f pos);
	sf::Vertex* quadFrom2d(sf::Vector2f pos);
	void setConditionFunction(bool (*conditionFunction)(std::vector<std::vector<bool> >&, int, int));

private:

	std::vector<std::vector<bool> > mFields;
	bool (*mConditionFunction)(std::vector<std::vector<bool> >&, int, int);
};
