#pragma once
#include <SFML\System.hpp>
class bullet
{
private:
	unsigned int UniqueId;
	int radius;
	float t = 5.f;
	float speed;
	sf::Vector2f Position;
	sf::Vector2f forward;
	bool DeleteOnNextInterval = false;
	bool died = false;
	int dmg = 1;
public:
	bullet();
	bullet(unsigned int UniqueId, int radius, float speed, sf::Vector2f Position, sf::Vector2f forward);
	sf::Vector2f update(float DeltaTime);
	sf::Vector2f getPosition() const;
	sf::Vector2f getCenteredPosition() const;
	int getRadius() const;
	float getTime() const;
	void setDeleteOnNextInterval();
	bool getDeleteOnNextInterval() const;
	bool getDied() const;
	void setDied();
	float getSpeed() const;
	sf::Vector2f getForwardVector() const; 
	unsigned int getUniqueId() const;
	int getdmg() const;
};

