#pragma once
#include "SFML/Graphics.hpp"

class Grid : public sf::Drawable, public sf::Transformable
{
public:

	Grid(sf::Vector2u gridSize, float fieldSize, 
		 sf::Color aliveCellColor = sf::Color::Black, sf::Color deadCellColor = sf::Color::White);

	std::pair<int, int> fieldFrom2d(sf::Vector2f pos);
	sf::Vertex* quadFrom2d(sf::Vector2f pos);
	void setQuadColor(sf::Vertex* quad, sf::Color color);
	void setConditionFunction(bool (*conditionFunction)(std::vector<std::vector<bool> >&, int, int));
	sf::Vector2f getOffset() const;
	void generate();
	void colorQuad(sf::Vector2f pos);
	void unColorQuad(sf::Vector2f pos);
	void update();
	void clear();

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Vector2u mGridSize;
	float mFieldsize;
	unsigned int mRowsCount;
	unsigned int mColumnsCount;
	sf::Vector2f mOffset;
	sf::VertexArray mVertices;
	std::vector<std::vector<bool> > mFields;
	sf::Color mAliveCellColor;
	sf::Color mDeadCellColor;
	bool (*mConditionFunction)(std::vector<std::vector<bool> >&, int, int);
};
