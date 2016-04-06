#include "Sandglass.h"

#include <assert.h>
#include <ctime>

Sandglass::Sandglass()
	: m_sandCount(0)
	, m_switch(false)
{
	srand(time(nullptr));
}


Sandglass::~Sandglass()
{
}

bool Sandglass::Initialize()
{	
	m_sandglass.resize(300u * 1000u);

	auto offset = 0u;
	for (auto row = 0u; row < 1000; ++row)
	{
		for (auto col = 0u; col < 300; ++col)
		{
			State state;

			if (col < offset || col >= 300 - offset || row < 3 || row >= 997)
			{
				state = State::BORDER;
			}
			else
			{
				if (row < 500)
				{
					state = State::SAND;
					++m_sandCount;
				}
				else
				{
					state = State::EMPTY;
				}
			}

			m_sandglass.at(row * 300u + col) = state;
		}
		if (row % 4 == 0)
		{
			if (row < 500)
			{
				++offset;
			}
			else
			{
				--offset;
			}				
		}
	}

	return true;
}

void Sandglass::Update()
{
	auto offset = 0;
	if (m_switch)
	{
		++offset;
	}

	for (auto row = 0; row < 500 - offset; ++row)
	{
		for (auto col = 0; col < 150 - offset; ++col)
		{
			std::vector<State> states(4);
			states.at(0) = m_sandglass.at((row * 2 + 0 + offset) * 300u + col * 2 + 0 + offset);
			states.at(1) = m_sandglass.at((row * 2 + 0 + offset) * 300u + col * 2 + 1 + offset);
			states.at(2) = m_sandglass.at((row * 2 + 1 + offset) * 300u + col * 2 + 0 + offset);
			states.at(3) = m_sandglass.at((row * 2 + 1 + offset) * 300u + col * 2 + 1 + offset);

			if (states.at(0) == SAND && states.at(1) == SAND &&			// OO -> XX || OO
				states.at(2) == EMPTY && states.at(3) == EMPTY)			// XX -> OO || XX
			{
				if (rand() > RAND_MAX / 2)
				{
					states.at(0) = EMPTY;
					states.at(1) = EMPTY;
					states.at(2) = SAND;
					states.at(3) = SAND;
				}
			}
			else if (states.at(0) == SAND && states.at(1) == SAND &&	// OO -> XO
					 states.at(2) == EMPTY && states.at(3) == SAND)		// XO -> OO
			{
				states.at(0) = EMPTY;
				states.at(2) = SAND;
			}
			else if (states.at(0) == SAND && states.at(1) == SAND &&	// OO -> OX
					 states.at(2) == SAND && states.at(3) == EMPTY)		// OX -> OO
			{
				states.at(1) = EMPTY;
				states.at(3) = SAND;
			}
			else if (states.at(0) == SAND && states.at(1) != SAND &&	// OX -> XX
					 states.at(2) == EMPTY && states.at(3) == SAND)		// XO -> OO
			{
				states.at(0) = EMPTY;
				states.at(2) = SAND;
			}
			else if (states.at(0) != SAND && states.at(1) == SAND &&	// XO -> XX
					 states.at(2) == SAND && states.at(3) == EMPTY)		// OX -> OO
			{
				states.at(1) = EMPTY;
				states.at(3) = SAND;
			}
			else if (states.at(0) == SAND && states.at(1) != SAND &&	// OX -> XX
					 states.at(2) != EMPTY && states.at(3) == EMPTY)	// OX -> OO
			{
				states.at(0) = EMPTY;
				states.at(3) = SAND;
			}
			else if (states.at(0) != SAND && states.at(1) == SAND &&	// XO -> XX
					 states.at(2) == EMPTY && states.at(3) != EMPTY)	// XO -> OO
			{
				states.at(1) = EMPTY;
				states.at(2) = SAND;
			}
			else if (states.at(0) == SAND && states.at(1) != SAND &&	// OX -> XX
					 states.at(2) == EMPTY && states.at(3) != SAND)		// XX -> OX
			{
				states.at(0) = EMPTY;
				states.at(2) = SAND;
			}
			else if (states.at(0) != SAND && states.at(1) == SAND &&	// XO -> XX
					 states.at(2) != SAND && states.at(3) == EMPTY)		// XX -> XO
			{
				states.at(1) = EMPTY;
				states.at(3) = SAND;
			}
			
			m_sandglass.at((row * 2 + 0 + offset) * 300u + col * 2 + 0 + offset) = states.at(0);
			m_sandglass.at((row * 2 + 0 + offset) * 300u + col * 2 + 1 + offset) = states.at(1);
			m_sandglass.at((row * 2 + 1 + offset) * 300u + col * 2 + 0 + offset) = states.at(2);
			m_sandglass.at((row * 2 + 1 + offset) * 300u + col * 2 + 1 + offset) = states.at(3);
		}
	}

	m_switch = !m_switch;
}

sf::Image Sandglass::CreateImage()
{
	sf::Image image;
	image.create(300u, 1000u);
	auto sandCount = 0;

	for (auto row = 0u; row < 1000; ++row)
	{
		for (auto col = 0u; col < 300; ++col)
		{
			sf::Color color;
			auto state = m_sandglass.at(row * 300u + col);

			switch(state)
			{
			case BORDER: 
				color = sf::Color::Blue; 
				break;
			case SAND: 
				++sandCount;
				color = sf::Color::Yellow; 
				break;
			case EMPTY: 
				color = sf::Color::Black; 
				break;
			default: 
				assert(true); 
				break;
			}

			image.setPixel(col, row, color);
		}
	}

	assert(m_sandCount == sandCount);
	
	return image;
}

void Sandglass::DeleteSand(float x, float y, float radius)
{
	auto width = 300u;
	auto height = 1000u;

	if (x < 350 || x > 650 || y < 0 || y > 1000) return;

	x -= 350.f;

	unsigned int lowerLimitX = x - radius;
	unsigned int upperLimitX = x + radius;

	unsigned int lowerLimitY = y - radius;
	unsigned int upperLimitY = y + radius;

	unsigned int sqrRadius = radius * radius;
	
	if (lowerLimitX < 0)    
		lowerLimitX = 0;
	if (upperLimitX > width - 2)  
		upperLimitX = width - 2;
	if (lowerLimitY < 0)    
		lowerLimitY = 0;
	if (upperLimitY > height - 2) 
		upperLimitY = height - 2;
		
	for (auto u = lowerLimitY; u < upperLimitY; ++u)	
	{
		for (auto l = lowerLimitX; l < upperLimitX; ++l)		
		{
			auto vx = x - l;
			auto vy = y - u;
			auto distance = vx * vx + vy * vy;
			if (distance < sqrRadius)
			{
				if (m_sandglass[u * 300 + l] == SAND)
				{
					m_sandglass[u * 300 + l] = EMPTY;
				}
			}
		}
	}
}
