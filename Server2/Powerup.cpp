#include "Powerup.h"



void Powerup::setUniqueId(unsigned int nUniqueId)
{
	UniqueId = nUniqueId;
}

Powerup::Powerup()
{
}

Powerup::Powerup(int type, sf::Vector2f Position)
	:type(type), Position(Position)
{
}

int Powerup::getType() const
{
	return type;
}

int Powerup::getHealingBonus() const
{
	return Healing_Bonus;
}

int Powerup::getAmountExtraShots() const
{
	return AmountExtraShots;
}

float Powerup::getExtraShotsTime() const
{
	return ExtraShotsTime;
}

float Powerup::getFireCooldown() const
{
	return FireCooldown;
}

float Powerup::getFireCooldownTime() const
{
	return FireCooldownTime;
}

sf::Vector2f Powerup::getPosition() const
{
	return Position;
}

sf::Vector2f Powerup::getCenteredPosition() const
{
	return {Position.x + float(radius) , Position.y + float(radius) };
}

int Powerup::getRadius() const
{
	return radius;
}

unsigned int Powerup::getUniqueId() const
{
	return UniqueId;
}

void Powerup::setDied()
{
	died = true;
}

bool Powerup::getDied() const
{
	return died;
}

void Powerup::setDeleteOnNextInterval()
{
	DeleteOnNextInterval = true;
}

bool Powerup::getDeleteOnNextInterval() const
{
	return DeleteOnNextInterval;
}

