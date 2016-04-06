#include "ViewHandler.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <sstream>
#include <iomanip>


ViewHandler::ViewHandler(sf::RenderWindow* window)
	: m_window(window)
{
	m_font.loadFromFile("tahoma.ttf");
	m_infoText.setFont(m_font);
	m_infoText.setCharacterSize(14u);
	m_infoText.setPosition(10.0f, 10.0f);
}

void ViewHandler::Render()
{
	auto fps = static_cast<int>(1.0f / m_fpsClock.getElapsedTime().asSeconds());
	auto lastFrame = static_cast<float>(m_fpsClock.getElapsedTime().asMicroseconds()) / 1000.f;
	
	std::stringstream stream;
	stream << "FPS: " << fps << "\n";
	stream << "LastFame: " << std::fixed << std::setprecision(2) << lastFrame << "ms\n";
	stream << "Mouse: " << std::fixed << std::setprecision(2) << m_mouseX << "x " << m_mouseY << "y\n";
	
	m_infoText.setString(stream.str());

	m_window->draw(m_infoText);

	m_fpsClock.restart();
}

void ViewHandler::SetMousePos(float x, float y)
{
	m_mouseX = x;
	m_mouseY = y;
}

void ViewHandler::ZoomIn()
{
	auto view = m_window->getView();
	view.zoom(0.8f);
	m_window->setView(view);
}

void ViewHandler::ZoomOut()
{
	auto view = m_window->getView();
	view.zoom(1.2f);
	m_window->setView(view);
}

