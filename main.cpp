#include <SFML/Graphics.hpp>

class Grid : public sf::Drawable, public sf::Transformable
{
public:

	Grid(sf::Vector2u gridSize, float fieldSize, float borderSize) :
		m_gridSize { gridSize },
		m_fieldSize { fieldSize },
		m_borderSize { borderSize },
		m_fields{}
	{
		generate();
	}

	std::pair<int, int> fieldFrom2d(sf::Vector2f pos)
	{
		float tileSize = m_fieldSize + m_borderSize;
		unsigned int columnCount = m_gridSize.x / tileSize;
		int i = pos.y / tileSize;
		int j = pos.x / tileSize;
		return std::pair<int, int>(i, j);
	}

	sf::Vertex* quadFrom2d(sf::Vector2f pos)
	{
		float tileSize = m_fieldSize + m_borderSize;
		unsigned int columnCount = m_gridSize.x / tileSize;
		int i = pos.y / tileSize;
		int j = pos.x / tileSize;
		return &m_vertices[(i * columnCount + j) * 4];
	}

	void setQuadColor(sf::Vertex *quad, sf::Color color)
	{
		for (int i = 0; i < 4; i++)
			quad[i].color = color;
	}

	void generate()
	{
		float tileSize = m_fieldSize + m_borderSize;
		unsigned int columnCount = m_gridSize.x / tileSize;
		unsigned int rowCount = m_gridSize.y / tileSize;
		m_vertices.setPrimitiveType(sf::Quads);
		m_vertices.resize(columnCount * rowCount * 4);
		m_fields = std::vector<std::vector<bool> >(rowCount, std::vector<bool>(columnCount, 0));

		for (int i = 0; i < rowCount; i++)
		{
			for (int j = 0; j < columnCount; j++)
			{
				sf::Vertex* quad = &m_vertices[(i * columnCount + j) * 4];
				quad[0].position = sf::Vector2f(j * tileSize, i * tileSize);
				quad[1].position = sf::Vector2f(j * tileSize + m_fieldSize, i * tileSize);
				quad[2].position = sf::Vector2f(j * tileSize + m_fieldSize, i * tileSize + m_fieldSize);
				quad[3].position = sf::Vector2f(j * tileSize, i * tileSize + m_fieldSize);
				setQuadColor(quad, sf::Color(64, 126, 227, 255));
			}
		}
	}

	void colorQuad(sf::Vector2f pos)
	{
		std::pair<int, int> field = fieldFrom2d(pos);
		m_fields[field.first][field.second] = 1;
		setQuadColor(quadFrom2d(pos), sf::Color::Red);
	}

	void unColorQuad(sf::Vector2f pos)
	{
		std::pair<int, int> field = fieldFrom2d(pos);
		m_fields[field.first][field.second] = 0;
		setQuadColor(quadFrom2d(pos), sf::Color(64, 126, 227, 255));
	}

	int checkNeighbours(std::vector<std::vector<bool> > &fields, int i, int j)
	{
		int count{ 0 };
		if (i > 0)
		{
			if (j > 0 && fields[i - 1][j - 1])
				count++;

			if (fields[i - 1][j])
				count++;

			if (j + 1 < fields[i].size() && fields[i - 1][j + 1])
				count++;
		}

		if (j > 0 && fields[i][j - 1])
			count++;

		if (j + 1 < fields[i].size() && fields[i][j + 1])
			count++;

		if (i + 1 < fields.size())
		{
			if (j > 0 && fields[i + 1][j - 1])
				count++;

			if (fields[i + 1][j])
				count++;

			if (j + 1 < fields[i].size() && fields[i + 1][j + 1])
				count++;
		}

		return count;
	}

	void update()
	{
		std::vector<std::vector<bool> > fieldsCopy{ m_fields };
		for (int i = 0; i < m_fields.size(); i++)
		{
			for (int j = 0; j < m_fields[i].size(); j++)
			{
				int count = checkNeighbours(fieldsCopy, i, j);
				if (fieldsCopy[i][j])
				{
					if (count <= 1 || count >= 4)
					{
						m_fields[i][j] = 0;
						setQuadColor(&m_vertices[(i * m_fields[i].size() + j) * 4], sf::Color(64, 126, 227, 255));
					}
				}
				else
				{
					if (count == 3)
					{
						m_fields[i][j] = 1;
						setQuadColor(&m_vertices[(i * m_fields[i].size() + j) * 4], sf::Color::Red);
					}
				}
			}
		}
	}

	void clear()
	{
		float tileSize = m_fieldSize + m_borderSize;
		unsigned int columnCount = m_gridSize.x / tileSize;
		unsigned int rowCount = m_gridSize.y / tileSize;

		for (int i = 0; i < rowCount; i++)
			for (int j = 0; j < columnCount; j++)
			{
				m_fields[i][j] = 0;
				sf::Vertex* quad = &m_vertices[(i * columnCount + j) * 4];
				setQuadColor(quad, sf::Color(64, 126, 227, 255));
			}	
	}

private:

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		states.transform *= this->getTransform();
		target.draw(m_vertices, states);
	}

	sf::Vector2u m_gridSize;
	float m_fieldSize;
	float m_borderSize;
	sf::VertexArray m_vertices;
	std::vector<std::vector<bool> > m_fields;
};

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "Game of life");
	Grid grid(window.getSize(), 16.f, 1.f);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		sf::Vector2i mouse = sf::Mouse::getPosition(window);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			grid.colorQuad(window.mapPixelToCoords(mouse));
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
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