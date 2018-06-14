#include "player.h"


void player::spawnBullets(const int amount, sf::Vector2f CenterForward, const bool rotate)
{
	//bullets.push_back(bullet(FreeBulletIds[0], BulletRadius, BulletSpeed, { getPositionCentered().x - 10, getPositionCentered().y - 10 }, { forward.x * cos(angle) - forward.y * sin(angle), forward.x * sin(angle) + forward.y * cos(angle) }));
	sf::Vector2f BulletCenterPos = { getPositionCentered().x - 10, getPositionCentered().y - 10 };



	if (amount % 2 != 0) {
		//Center Bullet
		spawnBullet(BulletCenterPos, CenterForward);

		const int l = (amount - 1) / 2;

		for (int i = 1; i <= l; i++) {
			spawnBullet(BulletCenterPos, rotateVector(-angle * i, CenterForward));
		//	std::cout << rotateVector(-angle * i, CenterForward).x << "/" << rotateVector(-angle * i, CenterForward).y << std::endl;
		}
		for (int i = 1; i <= l; i++) {
			spawnBullet(BulletCenterPos, rotateVector(angle * i, CenterForward));
			//std::cout << rotateVector(angle * i, CenterForward).x << "/" << rotateVector(angle * i, CenterForward).y << std::endl;
		}
	}
	else {
		spawnBullet(BulletCenterPos, CenterForward);
		const int l = amount / 2;

		for (int i = 1; i <= l; i++) {
			spawnBullet(BulletCenterPos, rotateVector(-angle * i, CenterForward));
			//std::cout << rotateVector(-angle * i, CenterForward).x << "/" << rotateVector(-angle * i, CenterForward).y << std::endl;
		}
		for (int i = 1; i <= l; i++) {
			spawnBullet(BulletCenterPos, rotateVector(angle * i, CenterForward));
			//std::cout << rotateVector(angle * i, CenterForward).x << "/" << rotateVector(angle * i, CenterForward).y << std::endl;
		}
	}

}

void player::spawnBullet(sf::Vector2f pos, sf::Vector2f forward)
{
	bullets.push_back(bullet(FreeBulletIds[0], BulletRadius, BulletSpeed, pos, forward)); //check breakpoints
	FreeBulletIds.erase(FreeBulletIds.begin() + 0);
}

sf::Vector2f player::rotateVector(float degree, sf::Vector2f forward)
{
	//degree = degree * 3.14159265359f / 180.f; // from radian to degree
	return { forward.x * cos(degree) - forward.y * sin(degree), forward.x * sin(degree) + forward.y * cos(degree) };
}

player::player()
{
}

player::player(unsigned short id, int SocketIndex, sf::IpAddress nPlayerIp, unsigned short nPlayerPort, int windowWidth, int windowHeight, sf::Vector2f Position)
	:UniqueId(id),
	index(SocketIndex),
	PlayerIp(nPlayerIp),
	PlayerPort(nPlayerPort),
	windowWidth(windowWidth),
	windowHeight(windowHeight),
	Position(Position)
{

	for (int i = 0; i < 300; i++) {
		FreeBulletIds.push_back(i);
	}

}

float player::update(const float DeltaTime, std::vector <player> &PLAYERS)
{

		afk += DeltaTime;

		/* Movement*/

		sf::Vector2f center = { Position.x + float(radius), Position.y + float(radius) };


		float dx = MousePosition.x - center.x;
		float dy = MousePosition.y - center.y;

		float distance = sqrt(fabs(dx) * fabs(dx) + fabs(dy) * fabs(dy));

		sf::Vector2f forward = { (dx) / distance , (dy) / distance };

		Position += forward * (speed * forwardPressedAmount) * DeltaTime;



		Position -= forward * (speed * backwardsPressedAmount) * DeltaTime;

		forwardPressedAmount = 0;
		backwardsPressedAmount = 0;

		sf::Vector2f left = { forward.y, forward.x*-1 };

		Position += left * (speed * leftPressedAmount) * DeltaTime;
		Position -= left * (speed * rightPressedAmount) * DeltaTime;

		leftPressedAmount = 0;
		rightPressedAmount = 0;


		/* In Bounds Check */

		if (int(Position.x) > windowWidth - radius * 2) {
			Position.x = float(windowWidth - radius * 2);
		}
		if (int(Position.y) > windowHeight - radius * 2) {
			Position.y = float(windowHeight - radius * 2);
		}
		if (Position.x < .0f) {
			Position.x = .0f;
		}
		if (Position.y < .0f) {
			Position.y = .0f;
		}

		/*if (int(Position.x) > windowWidth) {
			Position.x = float(windowWidth);
		}
		if (int(Position.y) > windowHeight) {
			Position.y = float(windowHeight);
		}
		if (Position.x < float(-radius * 2)) {
			Position.x = float(-radius * 2);
		}
		if (Position.y < float(-radius * 2)) {
			Position.y = float(-radius * 2);
		}*/

		/*
		Bullets stuff
		*/


		if (ExtraShotsAmountTime <= 0.f) {
			ShotsPerFire = 1;
		}
		else {
			ExtraShotsAmountTime -= DeltaTime;
		}
		if (extraFireCooldownTime <= 0.f) {
			OriginCooldown = OriginCache;
		}
		else {
			extraFireCooldownTime -= DeltaTime;
		}


		for (int i = 0; i < int(bullets.size()); i++) {

			if (bullets[i].getDeleteOnNextInterval() == true) {
				//erases bullets which are dead and status has been sent to client
				FreeBulletIds.push_back(bullets[i].getUniqueId());
				bullets.erase(bullets.begin() + i);
				//std::cout << "Bullet Destroyed" << std::endl;
				continue;
			}

			bullets[i].update(DeltaTime);

			if (bullets[i].getTime() < 0.f) {
				//std::cout << "Bullet died" << std::endl;
				//bullets.erase(bullets.begin() + i);
				bullets[i].setDied();
				continue;
			}

			sf::Vector2f BulletCenter = bullets[i].getCenteredPosition();

			for (int q = 0; q < int(PLAYERS.size()); q++) {
				if (PLAYERS[q].getID() != index && bullets[i].getDied() == false) {
					//Check Collision
					sf::Vector2f PlayerCentered = PLAYERS[q].getPositionCentered();

					float dx = BulletCenter.x - PlayerCentered.x;
					float dy = BulletCenter.y - PlayerCentered.y;

					if ((dx*dx + dy*dy) < ((bullets[i].getRadius() + PLAYERS[q].getRadius()) * (bullets[i].getRadius() + PLAYERS[q].getRadius()))) {
						//Bullet hit Player
						if (DebugMessages)
						std::cout << "Hit player " << PLAYERS[q].getUniqueId() << std::endl; //bullet dmg stragne wtf

						///it doesnt deal damage because PLAYERS is not a reference but a copy
						if (PLAYERS[q].dealDamage(bullets[i].getdmg())) { //kill
							/*kills++;
							ShotsPerFire++;
							health = 50;*/
							health += 5;
						}

						bullets[i].setDied();
						//std::cout << "Player hit by bullet" << std::endl;
					}
				}
			}

			if (bullets[i].getCenteredPosition().x < 0.f) {
				bullets[i].setDied();
			}
			else if (bullets[i].getCenteredPosition().y < 0.f) {
				bullets[i].setDied();
			}
			else if (bullets[i].getCenteredPosition().x > float(windowWidth)) {
				bullets[i].setDied();
			}
			else if (bullets[i].getCenteredPosition().y > float(windowHeight)) {
				bullets[i].setDied();
			}

		}


		shoot(DeltaTime, forward, PLAYERS);

		if (spawnCooldown > 0.f) {
			spawnCooldown -= DeltaTime;
		}

		return afk;
	}
	
int player::getSocketIndex() const
{
	return index;
}

sf::IpAddress player::getPlayerIp() const
{
	return PlayerIp;
}

unsigned short player::getPlayerPort() const
{
	return PlayerPort;
}

int player::getRadius() const
{
	return radius;
}

float player::getSpeed() const
{
	return speed;
}

sf::Vector2f player::getPosition() const
{
	return Position;
}

int player::getID() const
{
	return index;
}

void player::shoot(const float &DeltaTime, sf::Vector2f forward, std::vector <player> &PLAYERS)
{	
	if (spawnCooldown <= 0.f) {
		if (fireCooldown > 0.f) {
			fireCooldown -= DeltaTime;
			spacePressedAmount = 0;
		}
		else if (spacePressedAmount > 0) {
			//shoot

			if (int(FreeBulletIds.size()) > 0) {


				if (hasTarget == false) {

					spawnBullets(ShotsPerFire, forward);
				}
				else {
					///calculate forward
					bool targetFound = false;
					const int l = int(PLAYERS.size());

					for (int q = 0; q < l; q++) {
						if (PLAYERS[q].getUniqueId() == target && PLAYERS[q].getHealth() > 0) {
							if (DebugMessages)
								std::cout << "Shooting at target" << std::endl;
							sf::Vector2f center = { Position.x + float(radius), Position.y + float(radius) };


							float dx = PLAYERS[q].getPositionCentered().x - center.x;
							float dy = PLAYERS[q].getPositionCentered().y - center.y;

							float distance = sqrt(fabs(dx) * fabs(dx) + fabs(dy) * fabs(dy));

							sf::Vector2f direction = { (dx) / distance , (dy) / distance };
							spawnBullets(ShotsPerFire, direction);
							targetFound = true;
							break;
						}
						else if (PLAYERS[q].getUniqueId() == target) {
							unsetTarget();
							spawnBullets(ShotsPerFire, forward);
							break;
						}
					}

					if (targetFound == false) {
						hasTarget = false;
						spawnBullets(ShotsPerFire, forward);
					}


				}

			}


			fireCooldown = OriginCooldown;
			spacePressedAmount = 0;


		}
	}
}

void player::insertInputs(InputClass inputs, sf::IpAddress NewIp, unsigned short NewPort)
{
		if (NewIp == PlayerIp && NewPort == PlayerPort) {
			afk = .0f;
			MousePosition = inputs.getMousePosition();
			if (inputs.getForwardPressed()) {
				if(forwardPressedAmount < 5)
					forwardPressedAmount++;
				//std::cout << "Forward: " << forwardPressedAmount << std::endl;
			}
			if (inputs.getSpacePressed()) {
				spacePressedAmount++;
			}
			if (inputs.getBackwardsPressed()) {
				backwardsPressedAmount++;
			}
			if (inputs.getLeftPressed()) {
				leftPressedAmount++;
			}
			if (inputs.getRightPressed()) {
				rightPressedAmount++;
			}
		}
		else {
			if (DebugMessages)
			std::cout << "Strange Packet Received from " << NewIp << "|" << NewPort << std::endl;
		}
	
}

sf::Vector2f player::getPositionCentered() const
{
	return{Position.x + radius, Position.y + radius};
}

std::vector<bullet> player::getBullets() const
{
	return bullets;
}


bullet player::getBulletAtIndex(int index) const
{
	return bullets[index];
}

unsigned short player::getUniqueId() const
{
	return UniqueId;
}

void player::setDeleteOnNextInterval()
{
	DeleteOnNextInterval = true;
}

bool player::getDeleteOnNextInterval() const
{
	return DeleteOnNextInterval;
}

void player::setIsAfk()
{
	isAfk = true;
}

bool player::getIsAfk()
{
	return isAfk;
}

void player::setDeleteOnNextIntervalForBullet(int index)
{
	bullets[index].setDeleteOnNextInterval();
}

bool player::dealDamage(int amount)
{
	if (spawnCooldown <= 0.f) {


			health = health - amount;
			if (health <= 0) {
				health = 0;
				return true; // player got killed
			}
		}
	
	return false;
}

int player::getHealth() const
{
	return health;
}

int player::getMaxHealth() const
{
	return maxHealth;
}

void player::setDied()
{
	died = true;
}

bool player::getDied() const
{
	return died;
}

int player::getKills() const
{
	return kills;
}

void player::setTarget(unsigned int t)
{
	target = t;
	hasTarget = true;
}

void player::unsetTarget()
{
	hasTarget = false;
}

bool player::PlayerHasTarget() const
{
	return hasTarget;
}

void player::HealPlayer(const int amount)
{
	health += amount;
	if (health > maxHealth) {
		health = maxHealth;
	}
}

void player::setShotsPerFire(int amount)
{
	ShotsPerFire = amount;
}

void player::setExtraShotsAmountTime(float amount)
{
	ExtraShotsAmountTime = amount;
}

void player::setShootCooldown(float amount)
{
	OriginCooldown = amount;
}

void player::setShootCooldownTime(float amount)
{
	extraFireCooldownTime = amount;
}

void player::setNickname(sf::String n)
{
	Nickname = n;
}

sf::String player::getNickname() const
{
	return Nickname;
}
