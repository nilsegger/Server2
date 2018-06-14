#include "Powerup_Health.h"



Powerup_Health::Powerup_Health()
{
}

Powerup_Health::Powerup_Health(sf::Vector2f Position)
	:Position(Position)
{
}

int Powerup_Health::getHealingBonus() const
{
	return Healing_Bonus;
}


