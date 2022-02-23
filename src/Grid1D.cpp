#include "Grid1D.h"



Grid1D::Grid1D(sf::Vector2u gridSize, float fieldSize, sf::Color aliveCellColor, sf::Color deadCellColor) :
	Grid(gridSize, fieldSize, aliveCellColor, deadCellColor),
	mCurrentRow{ 0 },
	mFields{},
	mConditionFunction{},
	mRule{}
{
	generate();
}

int Grid1D::fieldFrom1d(float xPos)
{
	return (xPos - mOffset.x) / mFieldsize;
}

sf::Vertex* Grid1D::quadFrom1d(float xPos)
{
	int i = (xPos - mOffset.x) / mFieldsize;
	return &mVertices[(mCurrentRow * mColumnsCount + i) * 4];
}

void Grid1D::setConditionFunction(bool (*conditionFunction)(std::vector<bool>&, int, unsigned char))
{
	mConditionFunction = conditionFunction;
}

void Grid1D::setRule(unsigned char rule)
{
	mRule = rule;
}

void Grid1D::generate()
{
	mVertices.setPrimitiveType(sf::Quads);
	mVertices.resize(mColumnsCount * mRowsCount * 4);
	mFields = std::vector<bool>(mColumnsCount, 0);

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

void Grid1D::colorQuad(float xPos)
{
	if (xPos < mOffset.x || xPos >(mGridSize.x - mOffset.x))
		return;
	int field = fieldFrom1d(xPos);
	mFields[field] = 1;
	setQuadColor(quadFrom1d(xPos), mAliveCellColor);
}

void Grid1D::unColorQuad(float xPos)
{
	if (xPos < mOffset.x || xPos >(mGridSize.x - mOffset.x))
		return;
	int field = fieldFrom1d(xPos);
	mFields[field] = 0;
	setQuadColor(quadFrom1d(xPos), mDeadCellColor);
}

void Grid1D::colorQuad(sf::Vector2f pos)
{
	colorQuad(pos.x);
}

void Grid1D::unColorQuad(sf::Vector2f pos)
{
	unColorQuad(pos.x);
}

void Grid1D::update()
{
	std::vector<bool> fieldsCopy{ mFields };
	for (int i = 0; i < mFields.size(); i++)
	{
		if (mConditionFunction(fieldsCopy, i, mRule))
		{
			mFields[i] = 1;
			setQuadColor(&mVertices[(mCurrentRow * mColumnsCount + i) * 4], mAliveCellColor);
		}
		else
		{
			mFields[i] = 0;
			setQuadColor(&mVertices[(mCurrentRow * mColumnsCount + i) * 4], mDeadCellColor);
		}
	}
	mCurrentRow = (mCurrentRow + 1) % mRowsCount;
}

void Grid1D::clear()
{
	for (int i = 0; i < mRowsCount; i++)
		for (int j = 0; j < mColumnsCount; j++)
		{
			mFields[j] = 0;
			sf::Vertex* quad = &mVertices[(i * mColumnsCount + j) * 4];
			setQuadColor(quad, mDeadCellColor);
		}
	mCurrentRow = 0;
}
