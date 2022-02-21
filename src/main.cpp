#include "Grid.h"
#include "config.h"
#include "gameRuleGameOfLifeDefault.h"
#include "gameRuleGameOfLifeClosedInTorus.h"

#include <functional>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), PROJECT_NAME);
	Grid grid(window.getSize(), 16.f);
	grid.setConditionFunction(&gameRuleGameOfLifeClosedInTorus);
	sf::Time dt{ sf::milliseconds(0) }, delay{ sf::milliseconds(100) };
	sf::Clock clock;

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
		{
			dt += clock.restart();
			if (dt >= delay)
			{
				grid.update();
				dt = sf::milliseconds(0);
			}	
		}

		window.clear(sf::Color::Blue);
		
		window.draw(grid);
		window.display();
	}
}