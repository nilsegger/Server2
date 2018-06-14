#include "bullet.h"



bullet::bullet()
{
}

bullet::bullet(unsigned int UniqueId, int radius, float speed, sf::Vector2f Position, sf::Vector2f forward)
	:UniqueId(UniqueId),
	radius(radius),
	speed(speed),
	Position(Position),
	forward(forward)
{
}

sf::Vector2f bullet::update(float DeltaTime)
{
	t -= DeltaTime;
	Position += forward * speed * DeltaTime;
	return Position;
}

sf::Vector2f bullet::getPosition() const
{
	return Position;
}

sf::Vector2f bullet::getCenteredPosition() const
{

	return {Position.x + radius, Position.y + radius};
}

int bullet::getRadius() const
{
	return radius;
}

float bullet::getTime() const
{
	return t;
}

void bullet::setDeleteOnNextInterval()
{
	DeleteOnNextInterval = true;
}

bool bullet::getDeleteOnNextInterval() const
{
	return DeleteOnNextInterval;
}

bool bullet::getDied() const
{
	return died;
}

void bullet::setDied()
{
	died = true;
}

float bullet::getSpeed() const
{
	return speed;
}

sf::Vector2f bullet::getForwardVector() const
{
	return forward;
}

unsigned int bullet::getUniqueId() const
{
	return UniqueId;
}

int bullet::getdmg() const
{
	return dmg;
}
