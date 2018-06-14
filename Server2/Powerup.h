#pragma once
#include <SFML\Graphics.hpp>

class Powerup
{
private:
	bool died = false;
	int type; //0 Heal, 1 3 Shots, 2 faster shooting
	unsigned int UniqueId;
	sf::Vector2f Position;
	
	int radius = 25;
	bool DeleteOnNextInterval = false;




	int Healing_Bonus = 20;
	int AmountExtraShots = 3;
	float ExtraShotsTime = 10.f;


	float FireCooldown = .05f;
	float FireCooldownTime = 5.f;


public:
	void setUniqueId(unsigned int nUniqueId);
	Powerup();
	Powerup(int type, sf::Vector2f Position);
	int getType() const;
	
	sf::Vector2f getPosition() const;
	sf::Vector2f getCenteredPosition() const;
	int getRadius() const;
	unsigned int getUniqueId() const;
	void setDied();
	bool getDied() const;
	void setDeleteOnNextInterval();
	bool getDeleteOnNextInterval() const;

	int getHealingBonus() const;
	
	int getAmountExtraShots() const;
	float getExtraShotsTime() const;

	float getFireCooldown() const;
	float getFireCooldownTime() const;
};

