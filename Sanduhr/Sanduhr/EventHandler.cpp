#include "EventHandler.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <assert.h>

#include "SceneHandler.h"
#include "ViewHandler.h"

EventHandler::EventHandler(sf::RenderWindow* window, SceneHandler* sceneHandler, ViewHandler* viewHandler)
	: m_window(window)
	, m_sceneHandler(sceneHandler)
	, m_viewHandler(viewHandler)
{
	assert(m_window);
}

EventHandler::~EventHandler()
{
}

void EventHandler::Update()
{
	sf::Event event;
	while(m_window->pollEvent(event))
	{
		switch(event.type)
		{
		case sf::Event::Closed: 
			m_window->close();
			break;
		case sf::Event::Resized: break;
		case sf::Event::LostFocus: break;
		case sf::Event::GainedFocus: break;
		case sf::Event::TextEntered: break;
		case sf::Event::KeyPressed: 
			OnKeyPressed(event.key.code);
			break;
		case sf::Event::KeyReleased: break;
		case sf::Event::MouseWheelMoved: break;
		case sf::Event::MouseWheelScrolled: break;
		case sf::Event::MouseButtonPressed: 
			OnMousePressed(event.mouseButton.x, event.mouseButton.y, event.mouseButton.button);
			break;
		case sf::Event::MouseButtonReleased: break;
		case sf::Event::MouseMoved: 
			OnMouseMoved(event.mouseMove.x, event.mouseMove.y);
			break;
		case sf::Event::MouseEntered: break;
		case sf::Event::MouseLeft: break;
		case sf::Event::JoystickButtonPressed: break;
		case sf::Event::JoystickButtonReleased: break;
		case sf::Event::JoystickMoved: break;
		case sf::Event::JoystickConnected: break;
		case sf::Event::JoystickDisconnected: break;
		case sf::Event::TouchBegan: break;
		case sf::Event::TouchMoved: break;
		case sf::Event::TouchEnded: break;
		case sf::Event::SensorChanged: break;
		case sf::Event::Count: break;
		default: break;
		}
	}
}

void EventHandler::OnKeyPressed(int key)
{
	if (key == sf::Keyboard::Add)
	{
		m_sceneHandler->IncreaseRadius();
	}
	else if (key == sf::Keyboard::Subtract)
	{
		m_sceneHandler->DecreaseRadius();
	}
	else if (key == sf::Keyboard::Q)
	{
		m_viewHandler->ZoomIn();
	}
	else if (key == sf::Keyboard::E)
	{
		m_viewHandler->ZoomOut();
	}
}

void EventHandler::OnMouseMoved(int x, int y)
{
	auto mouseCoord = m_window->mapPixelToCoords(sf::Vector2i(x, y));
	m_viewHandler->SetMousePos(mouseCoord.x, mouseCoord.y);
	m_sceneHandler->SetMousePosition(mouseCoord.x, mouseCoord.y);
}

void EventHandler::OnMousePressed(int x, int y, int button)
{
	if (button != sf::Mouse::Button::Left)
	{
		return;
	}

	auto mouseCoord = m_window->mapPixelToCoords(sf::Vector2i(x, y));
	m_sceneHandler->DeleteSand(mouseCoord.x, mouseCoord.y);
}

