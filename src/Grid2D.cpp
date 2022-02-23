#include "Grid2D.h"



Grid2D::Grid2D(sf::Vector2u gridSize, float fieldSize, sf::Color aliveCellColor, sf::Color deadCellColor) :
	Grid(gridSize, fieldSize, aliveCellColor, deadCellColor),
	mFields{},
	mConditionFunction{}
{
	generate();
}

std::pair<int, int> Grid2D::fieldFrom2d(sf::Vector2f pos)
{
	return std::pair<int, int>((pos.y - mOffset.y) / mFieldsize, (pos.x - mOffset.x) / mFieldsize);
}

sf::Vertex* Grid2D::quadFrom2d(sf::Vector2f pos)
{
	int i = (pos.y - mOffset.y) / mFieldsize;
	int j = (pos.x - mOffset.x) / mFieldsize;
	return &mVertices[(i * mColumnsCount + j) * 4];
}

void Grid2D::setConditionFunction(bool (*conditionFunction)(std::vector<std::vector<bool> >&, int, int))
{
	mConditionFunction = conditionFunction;
}

void Grid2D::generate()
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

void Grid2D::colorQuad(sf::Vector2f pos)
{
	if (pos.x < mOffset.x || pos.x > (mGridSize.x - mOffset.x) || pos.y < mOffset.y || pos.y > (mGridSize.y - mOffset.y))
		return;
	std::pair<int, int> field = fieldFrom2d(pos);
	mFields[field.first][field.second] = 1;
	setQuadColor(quadFrom2d(pos), mAliveCellColor);
}

void Grid2D::unColorQuad(sf::Vector2f pos)
{
	if (pos.x < mOffset.x || pos.x >(mGridSize.x - mOffset.x) || pos.y < mOffset.y || pos.y >(mGridSize.y - mOffset.y))
		return;
	std::pair<int, int> field = fieldFrom2d(pos);
	mFields[field.first][field.second] = 0;
	setQuadColor(quadFrom2d(pos), mDeadCellColor);
}

void Grid2D::update()
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

void Grid2D::clear()
{
	for (int i = 0; i < mRowsCount; i++)
		for (int j = 0; j < mColumnsCount; j++)
		{
			mFields[i][j] = 0;
			sf::Vertex* quad = &mVertices[(i * mColumnsCount + j) * 4];
			setQuadColor(quad, mDeadCellColor);
		}
}
