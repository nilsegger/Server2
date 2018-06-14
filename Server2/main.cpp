#include <iostream>
#include <vector>
#include <string>
#include <SFML\Network.hpp>
#include <stdlib.h>
#include <time.h>
#include "player.h"
#include "bullet.h"
#include "InputClass.h"
#include "PowerupManager.h"

#define DISCOVER 0
#define DISCOVER_CONFIRMATION 1
#define CREATE_PLAYER 2
#define CREATE_PLAYER_CONFIRMATION 3
#define GAME_INPUTS 4
#define GAME_DATA 5
#define FOLLOW_PLAYER_DATA 6
#define FOLLOW_BULLET_DATA 7
#define DELETE_PLAYER 8
#define DELETE_BULLET 9
#define SERVER_FULL 10
#define PLAYER_UNQIUE_ID 11
#define PLAYER_DIED 12
#define POWER_UP_DATA_FOLLOW 13
#define POWER_UP_DELETE 14

unsigned short PORT = 4020;
unsigned short nextPlayerSocketPort = 4021;

sf::UdpSocket MainSocket;

const int MaxPlayerSockets = 10;
sf::UdpSocket PlayerSockets[MaxPlayerSockets];

std::vector <player> PlayerVector;
std::vector <sf::IpAddress> PlayerVectorIpAddresses;
int PlayerVectorLength = 0;

std::vector <unsigned int> UniqueIds;

const int arrayAmount = 84;
sf::Vector2f SpawnPositions[arrayAmount] = { {100.f, 100.f }, {100.f, 200.f}, {100.f,300.f}, {100.f,400.f}, {100.f,500.f}, {100.f,600.f}, {100.f,700.f},{ 200.f, 100.f },{ 200.f, 200.f },{ 200.f,300.f },{ 200.f,400.f },{ 200.f,500.f },{ 200.f,600.f },{ 200.f,700.f },{ 300.f, 100.f },{ 300.f, 200.f },{ 300.f,300.f },{ 300.f,400.f },{ 300.f,500.f },{ 300.f,600.f },{ 300.f,700.f },{ 400.f, 100.f },{ 400.f, 200.f },{ 400.f,300.f },{ 400.f,400.f },{ 400.f,500.f },{ 400.f,600.f },{ 400.f,700.f },{ 100.f, 500.f },{ 500.f, 200.f },{ 500.f,300.f },{ 500.f,400.f },{ 500.f,500.f },{ 500.f,600.f },{ 500.f,700.f },{ 600.f, 100.f },{ 600.f, 200.f },{ 600.f,300.f },{ 600.f,400.f },{ 600.f,500.f },{ 600.f,600.f },{ 600.f,700.f },{ 700.f, 100.f },{ 700.f, 200.f },{ 700.f,300.f },{ 700.f,400.f },{ 700.f,500.f },{ 700.f,600.f },{ 700.f,700.f },{ 800.f, 100.f },{ 800.f, 200.f },{ 800.f,300.f },{ 800.f,400.f },{ 800.f,500.f },{ 800.f,600.f },{ 800.f,700.f },{ 900.f, 100.f },{ 900.f, 200.f },{ 900.f,300.f },{ 900.f,400.f },{ 900.f,500.f },{ 900.f,600.f },{ 900.f,700.f },{ 1000.f, 100.f },{ 1000.f, 200.f },{ 1000.f,300.f },{ 1000.f,400.f },{ 1000.f,500.f },{ 1000.f,600.f },{ 1000.f,700.f },{ 1100.f, 100.f },{ 1100.f, 200.f },{ 1100.f,300.f },{ 1100.f,400.f },{ 1100.f,500.f },{ 1100.f,600.f },{ 1100.f,700.f },{ 1200.f, 100.f },{ 1200.f, 200.f },{ 1200.f,300.f },{ 1200.f,400.f },{ 1200.f,500.f },{ 1200.f,600.f },{ 1200.f,700.f } };

bool DebugMessages = true;
PowerupManager PowerUps;
class CreatePlayer
{
public:
	CreatePlayer();
	bool execute(sf::IpAddress &player_ip, unsigned short &player_port, sf::String Nickname);
};

class SendDiscoverConfirmation {
public:
	SendDiscoverConfirmation();
	bool execute(sf::IpAddress &player_ip, unsigned short &player_port);
};
class PackageSorter {
public:
	PackageSorter();
	bool sort(sf::Packet &packet, sf::IpAddress &player_ip, unsigned short &player_port);
};

class Game {

public:
	Game();
	bool execute(const float &DeltaTime);
	bool CheckForInputs();
};

class GameDataSender {
public:
	GameDataSender();
	bool execute();
};

class Connection {
public:
	Connection();
	bool checkNewConnection();
};

CreatePlayer CreatePlayerObject;
SendDiscoverConfirmation SendDiscoverConfirmationObject;
PackageSorter PackageSorterObject;
Game GameObject;
GameDataSender GameDataSenderObject;
Connection ConnectionObject;

sf::Clock TimeStampClock;

int main() {
	while (MainSocket.bind(PORT) != sf::Socket::Done) {
		PORT++;
	}

	MainSocket.setBlocking(false);

	for (int i = 0; i < MaxPlayerSockets; i++) {

		while (PlayerSockets[i].bind(nextPlayerSocketPort) != sf::Socket::Done) {
			nextPlayerSocketPort++;
		}
		PlayerSockets[i].setBlocking(false);

		nextPlayerSocketPort++;
		UniqueIds.push_back(unsigned int(i));
	}

	std::cout << sf::IpAddress::getLocalAddress() << "|" << PORT << std::endl;

	sf::Clock ServerLoopClock;
	sf::Clock GameLoopClock;

	float ServerLoopDeltaTime = 0;
	float GameLoopDeltaTime = 0;

	float GameInterval = 0.f;
	float SendInterval = 0.f;

	while (true) {
		
			if (GameInterval <= 0.f) {
				//Do game Physiscs
				GameObject.execute(GameLoopDeltaTime);
				GameLoopDeltaTime = GameLoopClock.restart().asSeconds();
				GameInterval += .015f;
			}
			if (SendInterval <= 0.f) {
				//Send Game Data
				GameDataSenderObject.execute();
				SendInterval += .045f;
			}

			//Get Player Inputs
			GameObject.CheckForInputs();

		//Check Connection
		ConnectionObject.checkNewConnection();

		/*if(int(PlayerVector.size()) == 0)
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		*/
		GameInterval -= ServerLoopDeltaTime;
		SendInterval -= ServerLoopDeltaTime;
		ServerLoopDeltaTime = ServerLoopClock.restart().asSeconds();
	}

	return 0;
}

/*
*
*
*	Classes
*
*
*/

/*
*	Create Player Class
*/

CreatePlayer::CreatePlayer() {};
bool CreatePlayer::execute(sf::IpAddress &player_ip, unsigned short &player_port, sf::String Nickname) {

	

	/*if (player_ip != "192.168.0.1" && player_ip != "192.168.0.17") {
		sf::Packet packet;
		packet << SERVER_FULL;

		MainSocket.send(packet, player_ip, player_port);

		return false;
	}*/



	if (int(UniqueIds.size()) > 0) {

		/*for (int i = 0; i < PlayerVectorLength; i++) {
			if (PlayerVectorIpAddresses[i] == player_ip) {

				sf::Packet packet;
				packet << SERVER_FULL;

				MainSocket.send(packet, player_ip, player_port);

				return false;
			}
		}*/

		srand(unsigned int(time(NULL)));
		int randomArrayNr = rand() % arrayAmount;

		player NewPlayer(UniqueIds[0], int(UniqueIds[0]), player_ip, player_port, 1280,720, SpawnPositions[randomArrayNr]); //Add Socket Index
		NewPlayer.setNickname(Nickname);

		PlayerVector.push_back(NewPlayer);
		PlayerVectorIpAddresses.push_back(player_ip);
		sf::Packet packet;
		packet << CREATE_PLAYER_CONFIRMATION;
		packet << sf::Int32(int(UniqueIds[0]));
		for (int i = 0; i < 3; i++) {
			std::cout << PlayerSockets[int(UniqueIds[0])].getLocalPort() << std::endl;
			if (PlayerSockets[int(UniqueIds[0])].send(packet, player_ip, player_port) == sf::Socket::Done) {
				
			}
		}
		
		if (DebugMessages) {
			std::cout << player_ip << "|" << player_port << std::endl;
		}
		UniqueIds.erase(UniqueIds.begin() + 0);
		PlayerVectorLength++;

		return true;
	}
	else {

		sf::Packet packet;
		packet << SERVER_FULL;

		MainSocket.send(packet, player_ip, player_port);

		return false;
	}
}

/*
*	Send Discover Class
*/

SendDiscoverConfirmation::SendDiscoverConfirmation() {};
bool SendDiscoverConfirmation::execute(sf::IpAddress &player_ip, unsigned short &player_port) {
	sf::Packet packet;
	packet << DISCOVER_CONFIRMATION;
	if (MainSocket.send(packet, player_ip, player_port) == sf::Socket::Done) {
		return true;
	}

	return false;
}

/*
*	Package Sorter Class
*/

PackageSorter::PackageSorter(){}
bool PackageSorter::sort(sf::Packet & packet, sf::IpAddress & player_ip, unsigned short & player_port)
{
	int msgType;
	packet >> msgType;
	sf::String Nickname;
	switch (msgType)
	{
	case DISCOVER:
		SendDiscoverConfirmationObject.execute(player_ip, player_port);
		return true;
		break;
	case CREATE_PLAYER:
		packet >> Nickname;
		CreatePlayerObject.execute(player_ip, player_port, Nickname);
		return true;
		break;
	default:
		break;
	}
	return false;
}

/*
*	Game Class
*/

Game::Game(){}
bool Game::execute(const float & DeltaTime)
{

	for (int i = 0; i < int(PlayerVector.size()); i++) {

		if (PlayerVector[i].getDeleteOnNextInterval()) {
			if (DebugMessages)
			std::cout << "Player with Unique Id " << PlayerVector[i].getID() << " has been removed" << std::endl;
			PlayerVector.erase(PlayerVector.begin() + i);
			PlayerVectorIpAddresses.erase(PlayerVectorIpAddresses.begin() + i);
			PlayerVectorLength--;
			continue;
		}

		if (!PlayerVector[i].getDied()) {

			float t = PlayerVector[i].update(DeltaTime, PlayerVector);

			if (PlayerVector[i].getHealth() == 0) {
				//std::cout << "died" << std::endl;
				PlayerVector[i].setDied();
			}

			if (t >= 3.0f) {
				//player has not sent a message for 3 seconds
				PlayerVector[i].setIsAfk();
			}
		}
	}

	PowerUps.update(DeltaTime, PlayerVector);

	return true;
}

bool Game::CheckForInputs()
{
	for (int i = 0; i < PlayerVectorLength; i++) {
		sf::Packet NewPacket;
		sf::IpAddress NewIp;
		unsigned short NewPort;

		if (PlayerSockets[PlayerVector[i].getSocketIndex()].receive(NewPacket, NewIp, NewPort) == sf::Socket::Done) {
			sf::Int64 x;
			sf::Int64 y;
			bool forwardPressed;
			bool backwardsPressed;
			bool leftPressed;
			bool rightPressed;
			bool spacePressed;

			sf::Int32 target;

			NewPacket >> x;
			NewPacket >> y;
			NewPacket >> forwardPressed;
			NewPacket >> backwardsPressed;
			NewPacket >> leftPressed;
			NewPacket >> rightPressed;
			NewPacket >> spacePressed;
			NewPacket >> target;
			PlayerVector[i].insertInputs(InputClass({ float(x),float(y) }, forwardPressed, backwardsPressed, leftPressed, rightPressed, spacePressed), NewIp, NewPort);

			if (target != sf::Int32(-1)) {
				PlayerVector[i].setTarget(unsigned int(target)); ///if shoot, shoot to position of this target
			}
			else {
				//std::cout << "No target" << std::endl;
				PlayerVector[i].unsetTarget();
			}
		}
	}
	return true;
}

/*
*	Game Data Sender Class
*/

GameDataSender::GameDataSender(){}
bool GameDataSender::execute()
{

	sf::Packet GameDataPacket;
	GameDataPacket << GAME_DATA;
	GameDataPacket << TimeStampClock.getElapsedTime().asMilliseconds();
	if (TimeStampClock.getElapsedTime().asMilliseconds() > sf::Int32(999999)) {
		TimeStampClock.restart();
		if (DebugMessages)
		std::cout << "Restarting TimeStampClock" << std::endl;
	}

	for (int i = 0; i < PlayerVectorLength; i++) {

		if (PlayerVector[i].getIsAfk()) {
			GameDataPacket << DELETE_PLAYER;
			GameDataPacket << sf::Uint32(PlayerVector[i].getUniqueId());

			PlayerVector[i].setDeleteOnNextInterval();
			UniqueIds.push_back(PlayerVector[i].getUniqueId());
		}
		else if (PlayerVector[i].getDied()) {
			GameDataPacket << PLAYER_DIED;
			GameDataPacket << sf::Uint32(PlayerVector[i].getUniqueId());

			PlayerVector[i].setDeleteOnNextInterval();
			UniqueIds.push_back(PlayerVector[i].getUniqueId());
		}
		else {
			GameDataPacket << FOLLOW_PLAYER_DATA;
			GameDataPacket << sf::Uint32(PlayerVector[i].getUniqueId());
			GameDataPacket << PlayerVector[i].getNickname();
			GameDataPacket << PlayerVector[i].getPosition().x;
			GameDataPacket << PlayerVector[i].getPosition().y;
			GameDataPacket << sf::Int64(PlayerVector[i].getRadius());

			///add health
			GameDataPacket << sf::Int32(PlayerVector[i].getHealth());
			GameDataPacket << sf::Int32(PlayerVector[i].getMaxHealth());

			std::vector <bullet> PlayerBullets = PlayerVector[i].getBullets();
			int BulletLength = int(PlayerBullets.size());
			for (int b = 0; b < BulletLength; b++) {
				if (PlayerBullets[b].getDied()) {

					GameDataPacket << DELETE_BULLET;
					GameDataPacket << sf::Uint32(PlayerVector[i].getUniqueId());
					GameDataPacket << sf::Uint32(PlayerBullets[b].getUniqueId());
					PlayerVector[i].setDeleteOnNextIntervalForBullet(b);
				}
				else {
					GameDataPacket << FOLLOW_BULLET_DATA;
					GameDataPacket << sf::Uint32(PlayerVector[i].getUniqueId());
					GameDataPacket << sf::Uint32(PlayerBullets[b].getUniqueId());
					GameDataPacket << PlayerBullets[b].getPosition().x;
					GameDataPacket << PlayerBullets[b].getPosition().y;
					GameDataPacket << sf::Int64(PlayerBullets[b].getRadius());
					GameDataPacket << PlayerBullets[b].getForwardVector().x;
					GameDataPacket << PlayerBullets[b].getForwardVector().y;
					GameDataPacket << PlayerBullets[b].getSpeed();
				}
			}

		}
	}

	const int l = int(PowerUps.getPowerups().size());

	for (int i = 0; i < l; i++) {
	
		if (!PowerUps.getPowerups()[i].getDied()) {
			GameDataPacket << POWER_UP_DATA_FOLLOW;
			GameDataPacket << sf::Int32(PowerUps.getPowerups()[i].getUniqueId());
			GameDataPacket << sf::Int32(PowerUps.getPowerups()[i].getType());
			GameDataPacket << sf::Int32(PowerUps.getPowerups()[i].getRadius());
			GameDataPacket << PowerUps.getPowerups()[i].getPosition().x;
			GameDataPacket << PowerUps.getPowerups()[i].getPosition().y;
		}
		else {
			GameDataPacket << POWER_UP_DELETE;
			GameDataPacket << sf::Int32(PowerUps.getPowerups()[i].getUniqueId());
			PowerUps.setDeleteOnNextInterval(i);
		}
	
	}
	

	for (int i = 0; i < PlayerVectorLength; i++) {
		PlayerSockets[PlayerVector[i].getSocketIndex()].send(GameDataPacket, PlayerVector[i].getPlayerIp(), PlayerVector[i].getPlayerPort());
	}
	return true;
}

/*
*	Connection Class
*/

Connection::Connection(){}
bool Connection::checkNewConnection()
{
	sf::Packet NewPacket;
	sf::IpAddress newIp;
	unsigned short newPort;
	if (MainSocket.receive(NewPacket, newIp, newPort) == sf::Socket::Done) {
		PackageSorterObject.sort(NewPacket, newIp, newPort);
		return true;
	}
	return false;
}
