#include "ContinuousGrid2D.h"

ContinuousGrid2D::ContinuousGrid2D(sf::Vector2u gridSize, float fieldSize, sf::Color aliveCellColor, sf::Color deadCellColor) :
	Grid(gridSize, fieldSize, aliveCellColor, deadCellColor),
	mMaxValue{},
	mFields{},
	mConditionFunction{},
	mColorFunction{}
{
	generate();
}

std::pair<int, int> ContinuousGrid2D::fieldFrom2d(sf::Vector2f pos)
{
	return std::pair<int, int>((pos.y - mOffset.y) / mFieldsize, (pos.x - mOffset.x) / mFieldsize);
}

sf::Vertex* ContinuousGrid2D::quadFrom2d(sf::Vector2f pos)
{
	int i = (pos.y - mOffset.y) / mFieldsize;
	int j = (pos.x - mOffset.x) / mFieldsize;
	return &mVertices[(i * mColumnsCount + j) * 4];
}

void ContinuousGrid2D::setConditionFunction(int (*conditionFunction)(std::vector<std::vector<int> >&, int, int))
{
	mConditionFunction = conditionFunction;
}

void ContinuousGrid2D::setColorFunction(sf::Color(*colorFunction)(int, int))
{
	mColorFunction = colorFunction;
}

void ContinuousGrid2D::setMaxValue(unsigned int value)
{
	mMaxValue = value;
}

void ContinuousGrid2D::generate()
{
	mVertices.setPrimitiveType(sf::Quads);
	mVertices.resize(mColumnsCount * mRowsCount * 4);
	mFields = std::vector<std::vector<int> >(mRowsCount, std::vector<int>(mColumnsCount, 0));

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

void ContinuousGrid2D::colorQuad(sf::Vector2f pos)
{
	if (pos.x < mOffset.x || pos.x >(mGridSize.x - mOffset.x) || pos.y < mOffset.y || pos.y >(mGridSize.y - mOffset.y))
		return;
	std::pair<int, int> field = fieldFrom2d(pos);
	mFields[field.first][field.second] = mMaxValue;
	setQuadColor(quadFrom2d(pos), mAliveCellColor);
}

void ContinuousGrid2D::unColorQuad(sf::Vector2f pos)
{
	if (pos.x < mOffset.x || pos.x >(mGridSize.x - mOffset.x) || pos.y < mOffset.y || pos.y >(mGridSize.y - mOffset.y))
		return;
	std::pair<int, int> field = fieldFrom2d(pos);
	mFields[field.first][field.second] = 0;
	setQuadColor(quadFrom2d(pos), mDeadCellColor);
}

void ContinuousGrid2D::update()
{
	std::vector<std::vector<int> > fieldsCopy{ mFields };
	for (int i = 0; i < mFields.size(); i++)
	{
		for (int j = 0; j <mColumnsCount; j++)
		{
			mFields[i][j] = mConditionFunction(fieldsCopy, i, j);
			setQuadColor(&mVertices[(i * mColumnsCount + j) * 4], mColorFunction(mFields[i][j], mMaxValue));
		}
	}
}

void ContinuousGrid2D::clear()
{
	for (int i = 0; i < mRowsCount; i++)
		for (int j = 0; j < mColumnsCount; j++)
		{
			mFields[i][j] = 0;
			sf::Vertex* quad = &mVertices[(i * mColumnsCount + j) * 4];
			setQuadColor(quad, mDeadCellColor);
		}
}
