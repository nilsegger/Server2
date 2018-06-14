#pragma once
#include <SFML\System.hpp>

class InputClass
{
private:
	sf::Vector2f MousePosition;
	bool forwardPressed;
	bool backwardsPressed;
	bool leftPressed;
	bool rightPressed;
	bool SpacePressed;
public:
	InputClass();
	InputClass(sf::Vector2f MousePosition, bool forwardPressed,	bool backwardsPressed, bool leftPressed, bool rightPressed, bool SpacePressed);
	InputClass(sf::Vector2f MousePosition, bool forwardPressed, bool SpacePressed);

	sf::Vector2f getMousePosition() const;
	bool getForwardPressed() const;
	bool getBackwardsPressed() const;
	bool getLeftPressed() const;
	bool getRightPressed() const;
	bool getSpacePressed() const;
};

