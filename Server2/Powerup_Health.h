#pragma once
#include <SFML\Graphics.hpp>
class Powerup_Health
{
private:
	sf::Vector2f Position;
	int Healing_Bonus = 20;
	int radius = 25;

public:
	Powerup_Health();
	Powerup_Health(sf::Vector2f Position);
	int getHealingBonus() const;
};

