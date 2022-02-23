#include "Grid.h"



Grid::Grid(sf::Vector2u gridSize, float fieldSize, sf::Color aliveCellColor, sf::Color deadCellColor) :
	mGridSize{ gridSize },
	mFieldsize{ fieldSize },
	mColumnsCount{ gridSize.x / static_cast<int>(fieldSize) },
	mRowsCount{ gridSize.y / static_cast<int>(fieldSize) },
	mOffset{ (gridSize.x - (fieldSize * mColumnsCount)) / 2.f,
			 (gridSize.y - (fieldSize * mRowsCount)) / 2.f },
	mAliveCellColor{ aliveCellColor },
	mDeadCellColor{ deadCellColor }
{
	setPosition(mOffset);
}

void Grid::setQuadColor(sf::Vertex* quad, sf::Color color)
{
	for (int i = 0; i < 4; i++)
		quad[i].color = color;
}

sf::Vector2f Grid::getOffset() const
{
	return mOffset;
}

void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mVertices, states);
}
