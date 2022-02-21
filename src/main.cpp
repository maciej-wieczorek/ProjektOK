#include <SFML/Graphics.hpp>
#include <functional>
#include "gameRuleGameOfLifeDefault.h"
#include "gameRuleGameOfLifeClosedInTorus.h"

class Grid : public sf::Drawable, public sf::Transformable
{
public:

	Grid(sf::Vector2u gridSize, float fieldSize, float borderSize) :
		mGridSize { gridSize },
		mFieldsize { fieldSize },
		mBorderSize { borderSize },
		mFields{},
		mConditionFunction{}
	{
		generate();
	}

	std::pair<int, int> fieldFrom2d(sf::Vector2f pos)
	{
		float tileSize = mFieldsize + mBorderSize;
		unsigned int columnCount = mGridSize.x / tileSize;
		int i = pos.y / tileSize;
		int j = pos.x / tileSize;
		return std::pair<int, int>(i, j);
	}

	sf::Vertex* quadFrom2d(sf::Vector2f pos)
	{
		float tileSize = mFieldsize + mBorderSize;
		unsigned int columnCount = mGridSize.x / tileSize;
		int i = pos.y / tileSize;
		int j = pos.x / tileSize;
		return &mVertices[(i * columnCount + j) * 4];
	}

	void setQuadColor(sf::Vertex *quad, sf::Color color)
	{
		for (int i = 0; i < 4; i++)
			quad[i].color = color;
	}

	void setConditionFunction(bool (*conditionFunction)(std::vector<std::vector<bool> >&, int, int))
	{
		mConditionFunction = conditionFunction;
	}

	void generate()
	{
		float tileSize = mFieldsize + mBorderSize;
		unsigned int columnCount = mGridSize.x / tileSize;
		unsigned int rowCount = mGridSize.y / tileSize;
		mVertices.setPrimitiveType(sf::Quads);
		mVertices.resize(columnCount * rowCount * 4);
		mFields = std::vector<std::vector<bool> >(rowCount, std::vector<bool>(columnCount, 0));

		for (int i = 0; i < rowCount; i++)
		{
			for (int j = 0; j < columnCount; j++)
			{
				sf::Vertex* quad = &mVertices[(i * columnCount + j) * 4];
				quad[0].position = sf::Vector2f(j * tileSize, i * tileSize);
				quad[1].position = sf::Vector2f(j * tileSize + mFieldsize, i * tileSize);
				quad[2].position = sf::Vector2f(j * tileSize + mFieldsize, i * tileSize + mFieldsize);
				quad[3].position = sf::Vector2f(j * tileSize, i * tileSize + mFieldsize);
				setQuadColor(quad, sf::Color(64, 126, 227, 255));
			}
		}
	}

	void colorQuad(sf::Vector2f pos)
	{
		std::pair<int, int> field = fieldFrom2d(pos);
		mFields[field.first][field.second] = 1;
		setQuadColor(quadFrom2d(pos), sf::Color::Red);
	}

	void unColorQuad(sf::Vector2f pos)
	{
		std::pair<int, int> field = fieldFrom2d(pos);
		mFields[field.first][field.second] = 0;
		setQuadColor(quadFrom2d(pos), sf::Color(64, 126, 227, 255));
	}

	void update()
	{
		std::vector<std::vector<bool> > fieldsCopy{ mFields };
		for (int i = 0; i < mFields.size(); i++)
		{
			for (int j = 0; j < mFields[i].size(); j++)
			{
				if (mConditionFunction(fieldsCopy, i ,j))
				{
					mFields[i][j] = 1;
					setQuadColor(&mVertices[(i * mFields[i].size() + j) * 4], sf::Color::Red);
				}
				else
				{
					mFields[i][j] = 0;
					setQuadColor(&mVertices[(i * mFields[i].size() + j) * 4], sf::Color(64, 126, 227, 255));
				}
				
			}
		}
	}

	void clear()
	{
		float tileSize = mFieldsize + mBorderSize;
		unsigned int columnCount = mGridSize.x / tileSize;
		unsigned int rowCount = mGridSize.y / tileSize;

		for (int i = 0; i < rowCount; i++)
			for (int j = 0; j < columnCount; j++)
			{
				mFields[i][j] = 0;
				sf::Vertex* quad = &mVertices[(i * columnCount + j) * 4];
				setQuadColor(quad, sf::Color(64, 126, 227, 255));
			}	
	}

private:

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		states.transform *= this->getTransform();
		target.draw(mVertices, states);
	}

	sf::Vector2u mGridSize;
	float mFieldsize;
	float mBorderSize;
	sf::VertexArray mVertices;
	std::vector<std::vector<bool> > mFields;
	bool (*mConditionFunction)(std::vector<std::vector<bool> >&, int, int);
	
};

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Game of life");
	Grid grid(window.getSize(), 16.f, 1.f);
	grid.setConditionFunction(&gameRuleGameOfLifeClosedInTorus);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		sf::Vector2i mouse = sf::Mouse::getPosition(window);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
		window.getViewport(window.getView()).contains(mouse))
			grid.colorQuad(window.mapPixelToCoords(mouse));
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right) &&
		window.getViewport(window.getView()).contains(mouse))
			grid.unColorQuad(window.mapPixelToCoords(mouse));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
			grid.clear();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
			grid.update();

		window.clear();
		window.draw(grid);
		window.display();
	}
}