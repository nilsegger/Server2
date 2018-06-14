#include "PowerupManager.h"



void PowerupManager::spawnPowerup()
{
	if (int(FreeUniqueIds.size()) > 0 && spawnStuff == true) {
		if (DebugMessages)
			std::cout << "Powerup spawned" << std::endl;
		spawned = true;
		cooldown = 5.f;

		srand(unsigned int(time(NULL)));
		int randomArrayNr = rand() % arrayAmount;
		int RandomType = rand() % AmountOfTypes;


		Powerup n(RandomType, SpawnPositions[randomArrayNr]);
		n.setUniqueId(FreeUniqueIds[0]);
		FreeUniqueIds.erase(FreeUniqueIds.begin() + 0);
		PowerUps.push_back(n);

	}
}

PowerupManager::PowerupManager()
{
	for (unsigned int i = 0; i < 10; i++) {
		FreeUniqueIds.push_back(i);
	}
}

void PowerupManager::update(const float DeltaTime, std::vector<player> &PLAYERS)
{

	if (int(PLAYERS.size()) > 0) {
		spawnStuff = true;
	}
	else {
		spawnStuff = false;
	}

	const int q = int(PowerUps.size());
	for (int x = q - 1; x >= 0 && q > 0; x--) {
		if (PowerUps[x].getDeleteOnNextInterval()) {
			FreeUniqueIds.push_back(PowerUps[x].getUniqueId());
			PowerUps.erase(PowerUps.begin() + x);
		}
	}


	if (spawnStuff == true) {
		cooldown -= DeltaTime;
	}
	if (cooldown <= 0.f) {
		spawnPowerup();
	}


	const int l = int(PLAYERS.size());
	
	for (int i = 0; i < l; i++) {
		if (!PLAYERS[i].getDied()) {

			

			const int q = int(PowerUps.size());
			for (int x = q - 1; x >= 0; x--) {

				if (PowerUps[x].getDied() == false) {
					float dx = PowerUps[x].getCenteredPosition().x - PLAYERS[i].getPositionCentered().x;
					float dy = PowerUps[x].getCenteredPosition().y - PLAYERS[i].getPositionCentered().y;

					if ((dx*dx + dy*dy) < ((PowerUps[x].getRadius() + PLAYERS[i].getRadius()) * (PowerUps[x].getRadius() + PLAYERS[i].getRadius()))) {

						switch (PowerUps[x].getType())
						{
						case 0: //heal
							if (DebugMessages)
								std::cout << "Player healed" << std::endl;
							PLAYERS[i].HealPlayer(PowerUps[x].getHealingBonus());
							break;
						case 1: //3 shots
							PLAYERS[i].setExtraShotsAmountTime(PowerUps[x].getExtraShotsTime());
							PLAYERS[i].setShotsPerFire(PowerUps[x].getAmountExtraShots());
							break;
						case 2:
							PLAYERS[i].setShootCooldown(PowerUps[x].getFireCooldown());
							PLAYERS[i].setShootCooldownTime(PowerUps[x].getFireCooldownTime());
							break;
						default:
							break;
						}
						PowerUps[x].setDied();

					}

				}

			}

		}
	}


}

std::vector<Powerup> PowerupManager::getPowerups() const
{
	return PowerUps;
}

void PowerupManager::setDeleteOnNextInterval(int index)
{
	PowerUps[index].setDeleteOnNextInterval();
}
