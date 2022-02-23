#pragma once
#include "Grid.h"

class ContinuousGrid2D : public Grid
{
public:

	ContinuousGrid2D(sf::Vector2u gridSize, float fieldSize,
		sf::Color aliveCellColor = sf::Color::White, sf::Color deadCellColor = sf::Color::Black);

	virtual void generate();
	virtual void colorQuad(sf::Vector2f pos);
	virtual void unColorQuad(sf::Vector2f pos);
	virtual void update();
	virtual void clear();
	
	std::pair<int, int> fieldFrom2d(sf::Vector2f pos);
	sf::Vertex* quadFrom2d(sf::Vector2f pos);
	void setConditionFunction(int (*conditionFunction)(std::vector<std::vector<int> >&, int, int));
	void setColorFunction(sf::Color(*colorFunction)(int, int));
	void setMaxValue(unsigned int value);

private:

	std::vector<std::vector<int> > mFields;
	unsigned int mMaxValue;
	int (*mConditionFunction)(std::vector<std::vector<int> >&, int, int);
	sf::Color (*mColorFunction)(int, int);
};
