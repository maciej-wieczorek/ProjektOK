#pragma once
#include "Grid.h"

class Grid1D : public Grid
{
public:

	Grid1D(sf::Vector2u gridSize, float fieldSize,
		sf::Color aliveCellColor = sf::Color::Black, sf::Color deadCellColor = sf::Color::White);

	virtual void generate();
	virtual void colorQuad(sf::Vector2f pos);
	virtual void unColorQuad(sf::Vector2f pos);
	virtual void update();
	virtual void clear();

	void colorQuad(float xPos);
	void unColorQuad(float xPos);
	int fieldFrom1d(float xPos);
	sf::Vertex* quadFrom1d(float xPos);
	void setConditionFunction(bool (*conditionFunction)(std::vector<bool>&, int, unsigned char));
	void setRule(unsigned char rule);

private:

	unsigned char mRule;
	int mCurrentRow;
	std::vector<bool> mFields;
	bool (*mConditionFunction)(std::vector<bool>&, int, unsigned char);
};
