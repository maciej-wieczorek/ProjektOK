#pragma once
#include <SFML/Graphics/Color.hpp>
#include <vector>

int rulesetForest(std::vector<std::vector<int> >& fields, int i, int j);
sf::Color colorForest(int value, int maxValue);