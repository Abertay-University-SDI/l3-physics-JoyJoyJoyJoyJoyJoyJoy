#include "Sheep.h"

Sheep::Sheep()
{
	// initialise animations
	for (int i = 0; i < 4; i++)
		m_walkDown.addFrame({ { 64 * i, 0 }, { 64, 64 } });
	m_walkDown.setLooping(true);
	m_walkDown.setFrameSpeed(0.25f);

	for (int i = 0; i < 4; i++)
		m_walkUp.addFrame({ { (64 * (i + 4)), 0 }, { 64, 64 } });
	m_walkUp.setLooping(true);
	m_walkUp.setFrameSpeed(0.25f);

	for (int i = 0; i < 4; i++)
		m_walkUpRight.addFrame({ { 64 * i, 64 }, { 64, 64 } });
	m_walkUpRight.setLooping(true);
	m_walkUpRight.setFrameSpeed(0.25f);

	for (int i = 0; i < 4; i++)
		m_walkRight.addFrame({ { (64 * (i + 4)), 64 }, { 64, 64 } });
	m_walkRight.setLooping(true);
	m_walkRight.setFrameSpeed(0.25f);

	for (int i = 0; i < 4; i++)
		m_walkDownRight.addFrame({ { 64 * i, 128 }, { 64, 64 } });
	m_walkDownRight.setLooping(true);
	m_walkDownRight.setFrameSpeed(0.25f);

	// the next 4 animations go clockwise from Up through Right to Down.

	m_currentAnimation = &m_walkDown;
	setTextureRect(m_currentAnimation->getCurrentFrame());

	setCollisionBox(2, 2, 60, 60);
}

Sheep::~Sheep()
{
}

void Sheep::handleInput(float dt)
{
	sf::Vector2f inputDir = { 0,0 };

	if(m_input->isKeyDown(sf::Keyboard::Scancode::W))
	{
		inputDir.y -= 1;
	}
	if (m_input->isKeyDown(sf::Keyboard::Scancode::A))
	{
		inputDir.x -= 1;
	}
	if (m_input->isKeyDown(sf::Keyboard::Scancode::S))
	{
		inputDir.y += 1;
	}
	if (m_input->isKeyDown(sf::Keyboard::Scancode::D))
	{
		inputDir.x += 1;
	}

	m_acceleration = inputDir * ACCELERATION;
}


void Sheep::update(float dt)
{
	m_velocity += m_acceleration * dt; 
	m_velocity *= DRAG_FACTOR;
	move(m_velocity);
	checkWallAndBounce();
}

void Sheep::setWorldSize(sf::Vector2f worldSize)
{
	m_worldSize = worldSize;
}

void Sheep::checkWallAndBounce()
{
	float currentPosx = getPosition().x;
	float currentPosy = getPosition().y;

	if (currentPosx > m_worldSize.x)
	{
		m_velocity *= -COEFF_OF_RESTITUTION;

	}
	if (currentPosy > m_worldSize.y)
	{
		m_velocity *= -COEFF_OF_RESTITUTION;
	}
	if (currentPosx < 0)
	{
		m_velocity *= -COEFF_OF_RESTITUTION;
	}
	if (currentPosy < 0)
	{
		m_velocity *= -COEFF_OF_RESTITUTION;
	}
}