#pragma once
#include <vector>
#include <SFML/Graphics/Color.hpp>

int rulesetTheExpansionVonNeumann(std::vector<std::vector<int> >& fields, int i, int j);
sf::Color colorTheExpansionVonNeumann(int value, int maxValue);