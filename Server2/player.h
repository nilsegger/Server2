#pragma once
#include <iostream>
#include <vector>
#include <SFML\Network.hpp>
#include "bullet.h"
#include "InputClass.h"
class player
{
private:
	 unsigned int UniqueId;
	 sf::String Nickname = "undefined";
	 int index; //Equals index of custom socket
	 sf::IpAddress PlayerIp;
	 unsigned short PlayerPort;

	bool DeleteOnNextInterval = false;

	sf::Vector2f MousePosition = {0.f, 0.f};
	int forwardPressedAmount = 0;
	int spacePressedAmount = 0;
	int backwardsPressedAmount = 0;
	int leftPressedAmount = 0;
	int rightPressedAmount = 0;

	sf::Vector2f Position = { 0.f,0.f };

	int radius = 40;
	float speed = 250.f;

	std::vector <bullet> bullets;
	std::vector <int> FreeBulletIds;

	float fireCooldown = 0.f;

	float extraFireCooldownTime = 0.f;

	float BulletSpeed = 1000.0f;
	int BulletRadius = 10;
	float OriginCooldown = .08f;//.095f;
	float OriginCache = .08f;

	float afk = .0f;
	bool isAfk = false;


	int health = 50;
	int maxHealth = 50;
	bool died = false;

	int windowWidth;
	int windowHeight;

	float spawnCooldown = 2.f;

	int kills = 0;

	int ShotsPerFire = 1;

	float ExtraShotsAmountTime = 0.f;

	float FasterShotsAmountTime = 0.f;

	bool hasTarget = false;
	unsigned int target = 0;

	bool DebugMessages = false;

	float angle = 5.f * 3.14f / 180.f;

	void spawnBullets(const int amount, sf::Vector2f CenterForward, const bool rotate = true);
	void spawnBullet(sf::Vector2f pos, sf::Vector2f forward);
	sf::Vector2f rotateVector(float degree, sf::Vector2f forward);

public:
	player();

	player(unsigned short UniqueId,int SocketIndex, sf::IpAddress nPlayerIp, unsigned short nPlayerPort, int windowWidth, int windowHeight, sf::Vector2f Position);

	float update(const float DeltaTime, std::vector <player> &AllPlayers);

	int getSocketIndex() const;
	sf::IpAddress getPlayerIp() const;
	unsigned short getPlayerPort() const;
	int getRadius() const;
	float getSpeed() const;
	sf::Vector2f getPosition() const;
	int getID() const;
	void shoot(const float &DeltaTime, sf::Vector2f forward, std::vector <player> &PLAYERS);
	void insertInputs(InputClass inputs, sf::IpAddress NewIp, unsigned short NewPort);
	sf::Vector2f getPositionCentered() const;
	std::vector <bullet> getBullets() const;
	bullet getBulletAtIndex(int index) const;
	unsigned short getUniqueId() const;
	void setDeleteOnNextInterval();
	bool getDeleteOnNextInterval() const;
	void setIsAfk();
	bool getIsAfk();
	void setDeleteOnNextIntervalForBullet(int index);
	bool dealDamage(int amount);
	int getHealth() const;
	int getMaxHealth() const;
	void setDied();
	bool getDied() const;

	int getKills() const;

	void setTarget(unsigned int t);
	void unsetTarget();
	bool PlayerHasTarget() const; 
	void HealPlayer(const int amount);

	void setShotsPerFire(int amount);
	void setExtraShotsAmountTime(float amount);

	void setShootCooldown(float amount);
	void setShootCooldownTime(float amount);
	//amount of time
	void setNickname(sf::String n);
	sf::String getNickname() const;
};

