#include "Planet.h"

#include <iostream>
#include <random>

Planet::Planet()
	: m_Position(Vector3f()), m_Velocity(Vector3f()), m_Force(Vector3f()), m_Radius(0), m_Mass(0), m_Distance(0), m_Angle(0)
{
}

Planet::Planet(float x, float y, float distance, uint32_t angle, float orbitSpeed, float z)
	: m_Position(x, y, z), m_Distance(distance), m_Angle(angle), m_Velocity(Vector3f()), m_Force(Vector3f()), m_Radius(0), m_Mass(0), m_OrbitSpeed(orbitSpeed)
{
}

Planet::~Planet()
{
}

void Planet::SpawnMoons(const uint16_t& number)
{
	int lowBounds = 30, highBounds = 150;
	int lowAngle = 0, highAngle = 180;
	int lowDirs = 0, highDirs = 1;

	int directions[2] = { 1, -1 };

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrDistance(lowBounds, highBounds);
	std::uniform_int_distribution<> distrAngle(lowAngle, highAngle);
	std::uniform_int_distribution<> distrDirections(lowDirs, highDirs);

	for (int i = 0; i < number; i++)
	{
		int randomDistance = distrDistance(gen); // Random distance of the moons from planet.
		int randomAngle = distrAngle(gen);
		int randomDirectionX = distrDirections(gen);
		int randomDirectionY = distrDirections(gen);

		std::cout << "random angle " << randomAngle << ", random distance " << randomDistance << " random dir x : " << directions[randomDirectionX] << " random dir y : " << directions[randomDirectionY] << std::endl;

		int posX = m_Position.x + (directions[randomDirectionX] * randomDistance);
		int posY = m_Position.y + (directions[randomDirectionY] * randomDistance);
		m_ChildPlanets.push_back(Planet(posX, posY, randomDistance, randomAngle, 0.3));
	}
}

void Planet::Draw(sf::RenderWindow &window)
{
	sf::CircleShape planet(100.f);
	planet.setFillColor(sf::Color(253, 184, 19));	// Sun
	planet.setPosition(m_Position.x, m_Position.y);
	planet.rotate(m_Angle);
	window.draw(planet);

	if (!m_ChildPlanets.empty())
	{
		for (const auto& moon : m_ChildPlanets)
		{
			sf::CircleShape moonShape(30.f);
			moonShape.setFillColor(sf::Color(204, 204, 204));	// Moon
			moonShape.setPosition(moon.m_Position.x, moon.m_Position.y);
			moonShape.rotate(moon.m_Angle);
			window.draw(moonShape);
		}
	}
}

void Planet::Orbit()
{
	float& angle = m_Angle;
	float orbitSpeed = m_OrbitSpeed;

	angle += orbitSpeed;

	if (!m_ChildPlanets.empty())
	{
		for (auto& moon : m_ChildPlanets)
		{
			moon.Orbit();
		}
	}
}
