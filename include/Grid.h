#pragma once

#include <SFML/Graphics.hpp>

class Grid : public sf::Drawable, public sf::Transformable
{
public:

	Grid(sf::Vector2u gridSize, float fieldSize, sf::Color aliveCellColor, sf::Color deadCellColor);
	virtual ~Grid() = default;

	virtual void generate() = 0;
	virtual void colorQuad(sf::Vector2f pos) = 0;
	virtual void unColorQuad(sf::Vector2f pos) = 0;
	virtual void update() = 0;
	virtual void clear() = 0;

	void setQuadColor(sf::Vertex* quad, sf::Color color);
	sf::Vector2f getOffset() const;

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

protected:
	sf::Vector2u mGridSize;
	float mFieldsize;
	unsigned int mRowsCount;
	unsigned int mColumnsCount;
	sf::Vector2f mOffset;
	sf::VertexArray mVertices;
	sf::Color mAliveCellColor;
	sf::Color mDeadCellColor;
};

