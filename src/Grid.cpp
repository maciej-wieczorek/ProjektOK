#include "Grid.h"



Grid::Grid(sf::Vector2u gridSize, float fieldSize, sf::Color aliveCellColor, sf::Color deadCellColor) :
	mGridSize{ gridSize },
	mFieldsize{ fieldSize },
	mColumnsCount{ gridSize.x / static_cast<int>(fieldSize) },
	mRowsCount{ gridSize.y / static_cast<int>(fieldSize) },
	mOffset{ (gridSize.x - (fieldSize * mColumnsCount)) / 2.f,
			 (gridSize.y - (fieldSize * mRowsCount)) / 2.f },
	mAliveCellColor{ aliveCellColor },
	mDeadCellColor{ deadCellColor },
	mFields{},
	mConditionFunction{}
{
	generate();
	setPosition(mOffset);
}

std::pair<int, int> Grid::fieldFrom2d(sf::Vector2f pos)
{
	return std::pair<int, int>((pos.y - mOffset.y) / mFieldsize, (pos.x - mOffset.x) / mFieldsize);
}

sf::Vertex* Grid::quadFrom2d(sf::Vector2f pos)
{
	int i = (pos.y - mOffset.y) / mFieldsize;
	int j = (pos.x - mOffset.x) / mFieldsize;
	return &mVertices[(i * mColumnsCount + j) * 4];
}

void Grid::setQuadColor(sf::Vertex* quad, sf::Color color)
{
	for (int i = 0; i < 4; i++)
		quad[i].color = color;
}

void Grid::setConditionFunction(bool (*conditionFunction)(std::vector<std::vector<bool> >&, int, int))
{
	mConditionFunction = conditionFunction;
}

sf::Vector2f Grid::getOffset() const
{
	return mOffset;
}

void Grid::generate()
{
	mVertices.setPrimitiveType(sf::Quads);
	mVertices.resize(mColumnsCount * mRowsCount * 4);
	mFields = std::vector<std::vector<bool> >(mRowsCount, std::vector<bool>(mColumnsCount, 0));

	for (int i = 0; i < mRowsCount; i++)
	{
		for (int j = 0; j < mColumnsCount; j++)
		{
			sf::Vertex* quad = &mVertices[(i * mColumnsCount + j) * 4];
			quad[0].position = sf::Vector2f(j * mFieldsize, i * mFieldsize);
			quad[1].position = sf::Vector2f(j * mFieldsize + mFieldsize, i * mFieldsize);
			quad[2].position = sf::Vector2f(j * mFieldsize + mFieldsize, i * mFieldsize + mFieldsize);
			quad[3].position = sf::Vector2f(j * mFieldsize, i * mFieldsize + mFieldsize);
			setQuadColor(quad, mDeadCellColor);
		}
	}
}

void Grid::colorQuad(sf::Vector2f pos)
{
	if (pos.x < mOffset.x || pos.x > (mGridSize.x - mOffset.x) || pos.y < mOffset.y || pos.y > (mGridSize.y - mOffset.y))
		return;
	std::pair<int, int> field = fieldFrom2d(pos);
	mFields[field.first][field.second] = 1;
	setQuadColor(quadFrom2d(pos), mAliveCellColor);
}

void Grid::unColorQuad(sf::Vector2f pos)
{
	if (pos.x < mOffset.x || pos.x >(mGridSize.x - mOffset.x) || pos.y < mOffset.y || pos.y >(mGridSize.y - mOffset.y))
		return;
	std::pair<int, int> field = fieldFrom2d(pos);
	mFields[field.first][field.second] = 0;
	setQuadColor(quadFrom2d(pos), mDeadCellColor);
}

void Grid::update()
{
	std::vector<std::vector<bool> > fieldsCopy{ mFields };
	for (int i = 0; i < mFields.size(); i++)
	{
		for (int j = 0; j < mFields[i].size(); j++)
		{
			if (mConditionFunction(fieldsCopy, i, j))
			{
				mFields[i][j] = 1;
				setQuadColor(&mVertices[(i * mFields[i].size() + j) * 4], mAliveCellColor);
			}
			else
			{
				mFields[i][j] = 0;
				setQuadColor(&mVertices[(i * mFields[i].size() + j) * 4], mDeadCellColor);
			}

		}
	}
}

void Grid::clear()
{
	for (int i = 0; i < mRowsCount; i++)
		for (int j = 0; j < mColumnsCount; j++)
		{
			mFields[i][j] = 0;
			sf::Vertex* quad = &mVertices[(i * mColumnsCount + j) * 4];
			setQuadColor(quad, mDeadCellColor);
		}
}

void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mVertices, states);
}
