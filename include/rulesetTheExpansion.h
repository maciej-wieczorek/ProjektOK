#pragma once
#include <vector>
#include <SFML/Graphics/Color.hpp>

int rulesetTheExpansion(std::vector<std::vector<int> >& fields, int i, int j);
sf::Color colorTheExpansion(int value, int maxValue);
