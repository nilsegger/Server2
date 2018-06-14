#include "InputClass.h"



InputClass::InputClass()
{
}

InputClass::InputClass(sf::Vector2f MousePosition, bool forwardPressed, bool backwardsPressed, bool leftPressed, bool rightPressed, bool SpacePressed)
	:MousePosition(MousePosition),
	forwardPressed(forwardPressed),
	backwardsPressed(backwardsPressed),
	leftPressed(leftPressed),
	rightPressed(rightPressed),
	SpacePressed(SpacePressed)
{
}

InputClass::InputClass(sf::Vector2f MousePosition, bool forwardPressed, bool SpacePressed)
	:MousePosition(MousePosition),
	forwardPressed(forwardPressed),
	SpacePressed(SpacePressed)
{
}

sf::Vector2f InputClass::getMousePosition() const
{
	return MousePosition;
}

bool InputClass::getForwardPressed() const
{
	return forwardPressed;
}

bool InputClass::getBackwardsPressed() const
{
	return backwardsPressed;
}

bool InputClass::getLeftPressed() const
{
	return leftPressed;
}

bool InputClass::getRightPressed() const
{
	return rightPressed;
}

bool InputClass::getSpacePressed() const
{
	return SpacePressed;
}

