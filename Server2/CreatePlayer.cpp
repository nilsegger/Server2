#include "CreatePlayer.h"



CreatePlayer::CreatePlayer()
{
}

bool CreatePlayer::execute(sf::IpAddress & player_ip, unsigned short & player_port)
{
	if (int(UniqueIds.size()) > 0) {
		player NewPlayer(UniqueIds[0], int(UniqueIds[0]), player_ip, player_port); //Add Socket Index

		PlayerVector.push_back(NewPlayer);
		sf::Packet packet;
		packet << CREATE_PLAYER_CONFIRMATION;
		packet << sf::Int32(int(UniqueIds[0]));
		PlayerSockets[int(UniqueIds[0])].send(packet, player_ip, player_port);
		std::cout << player_ip << "|" << player_port << std::endl;

		UniqueIds.erase(UniqueIds.begin() + 0);
	}
	else {

		sf::Packet packet;
		packet << SERVER_FULL;

		MainSocket.send(packet, player_ip, player_port);

		// Server is full
	}
}

