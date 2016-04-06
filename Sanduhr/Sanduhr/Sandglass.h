#pragma once
#include <SFML/Graphics/Image.hpp>

enum State
{
	BORDER	= 0,
	SAND	= 1,
	EMPTY	= 2
};


class Sandglass
{
public:
	Sandglass();
	~Sandglass();

	bool Initialize();
	void Update();
	sf::Image CreateImage();
	void DeleteSand(float x, float y, float radius);

private:
	std::vector<State> m_sandglass;
	int m_sandCount;
	bool m_switch;
};

