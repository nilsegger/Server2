#pragma once
#include "Powerup.h"
#include "player.h"
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>
class PowerupManager
{
	bool DebugMessages = false;

	

	bool spawned = true;
	int AmountOfTypes = 3;

	float cooldown = 1.f;

	std::vector<unsigned int> FreeUniqueIds;
	void spawnPowerup();
	std::vector <Powerup> PowerUps;

	const int arrayAmount = 74;
	sf::Vector2f SpawnPositions[74] = { { 100.f, 100.f },{ 100.f, 200.f },{ 100.f,300.f },{ 100.f,400.f },{ 100.f,500.f },{ 100.f,600.f },{ 200.f, 100.f },{ 200.f, 200.f },{ 200.f,300.f },{ 200.f,400.f },{ 200.f,500.f },{ 200.f,600.f },{ 300.f, 100.f },{ 300.f, 200.f },{ 300.f,300.f },{ 300.f,400.f },{ 300.f,500.f },{ 300.f,600.f },{ 400.f, 100.f },{ 400.f, 200.f },{ 400.f,300.f },{ 400.f,400.f },{ 400.f,500.f },{ 400.f,600.f },{ 100.f, 500.f },{ 500.f, 200.f },{ 500.f,300.f },{ 500.f,400.f },{ 500.f,500.f },{ 500.f,600.f },{ 600.f, 100.f },{ 600.f, 200.f },{ 600.f,300.f },{ 600.f,400.f },{ 600.f,500.f },{ 600.f,600.f },{ 700.f, 100.f },{ 700.f, 200.f },{ 700.f,300.f },{ 700.f,400.f },{ 700.f,500.f },{ 700.f,600.f },{ 800.f, 100.f },{ 800.f, 200.f },{ 800.f,300.f },{ 800.f,400.f },{ 800.f,500.f },{ 800.f,600.f },{ 800.f,700.f },{ 900.f, 100.f },{ 900.f, 200.f },{ 900.f,300.f },{ 900.f,400.f },{ 900.f,500.f },{ 900.f,600.f },{ 900.f,700.f },{ 1000.f, 100.f },{ 1000.f, 200.f },{ 1000.f,300.f },{ 1000.f,400.f },{ 1000.f,500.f },{ 1000.f,600.f },{ 1100.f, 100.f },{ 1100.f, 200.f },{ 1100.f,300.f },{ 1100.f,400.f },{ 1100.f,500.f },{ 1100.f,600.f },{ 1200.f, 100.f },{ 1200.f, 200.f },{ 1200.f,300.f },{ 1200.f,400.f },{ 1200.f,500.f },{ 1200.f,600.f } };

	bool spawnStuff = false;
public:
	
	PowerupManager();
	void update(const float DeltaTime, std::vector<player> &PLAYERS);
	std::vector <Powerup> getPowerups() const;
	void setDeleteOnNextInterval(int index);
};

