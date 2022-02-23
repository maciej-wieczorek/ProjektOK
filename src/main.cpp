#include "Grid1D.h"
#include "Grid2D.h"
#include "ContinuousGrid2D.h"
#include "config.h"
#include "rulesetElementaryCA.h"
#include "rulesetElementaryLoopedCA.h"
#include "rulesetGameOfLifeDefault.h"
#include "rulesetGameOfLifeClosedInTorus.h"
#include "rulesetTheExpansion.h"
#include "rulesetTheExpansionVonNeumann.h"
#include "rulesetForest.h"

#include <functional>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), PROJECT_NAME);
	//sf::RenderWindow window(sf::VideoMode(1920, 1080), PROJECT_NAME);

	Grid1D elementaryCA(window.getSize(), 2.f);
	elementaryCA.setConditionFunction(&rulesetElementaryCA);
	elementaryCA.setRule(110);

	Grid1D elementaryLoopedCA(window.getSize(), 2.f);
	elementaryLoopedCA.setConditionFunction(&rulesetElementaryLoopedCA);
	elementaryLoopedCA.setRule(110);

	Grid2D gameOfLifeDefault(window.getSize(), 4.f);
	gameOfLifeDefault.setConditionFunction(&rulesetGameOfLifeDefault);

	Grid2D gameOfLifeClosedInTorus(window.getSize(), 4.f);
	gameOfLifeClosedInTorus.setConditionFunction(&rulesetGameOfLifeClosedInTorus);

	ContinuousGrid2D theExpansion(window.getSize(), 4.f);
	theExpansion.setConditionFunction(&rulesetTheExpansion);
	theExpansion.setColorFunction(&colorTheExpansion);
	theExpansion.setMaxValue(255);

	ContinuousGrid2D theExpansionVonNeumann(window.getSize(), 4.f);
	theExpansionVonNeumann.setConditionFunction(&rulesetTheExpansionVonNeumann);
	theExpansionVonNeumann.setColorFunction(&colorTheExpansionVonNeumann);
	theExpansionVonNeumann.setMaxValue(255);

	ContinuousGrid2D forest(window.getSize(), 1.f, sf::Color(10, 69, 5, 255));
	forest.setConditionFunction(&rulesetForest);
	forest.setColorFunction(&colorForest);
	forest.setMaxValue(15);

	Grid* currentCA = &elementaryCA;

	sf::Time dt{ sf::milliseconds(0) }, delay{ sf::milliseconds(0) };
	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
			currentCA = &elementaryCA;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
			currentCA = &elementaryLoopedCA;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
			currentCA = &gameOfLifeDefault;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
			currentCA = &gameOfLifeClosedInTorus;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
			currentCA = &theExpansion;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
			currentCA = &theExpansionVonNeumann;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
			currentCA = &forest;

		sf::Vector2i mouse = sf::Mouse::getPosition(window);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
		window.getViewport(window.getView()).contains(mouse))
			currentCA->colorQuad(window.mapPixelToCoords(mouse));
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right) &&
		window.getViewport(window.getView()).contains(mouse))
			currentCA->unColorQuad(window.mapPixelToCoords(mouse));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
			currentCA->clear();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
		{
			dt += clock.restart();
			if (dt >= delay)
			{
				currentCA->update();
				dt = sf::milliseconds(0);
			}
		}

		window.clear(sf::Color::Black);
		window.draw(*currentCA);
		window.display();
	}
}