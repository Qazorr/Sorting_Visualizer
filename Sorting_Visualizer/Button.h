#pragma once

#include "common.h"

enum state {
	idle,
	hover,
	click
};

class Button
{
private:
	sf::RectangleShape button_area;
	sf::Font font;
	sf::Text name;
	state button_state;
	short operation;
	sf::Color colors[3] = { sf::Color(0, 100, 0), sf::Color(0, 0, 100), sf::Color::Green };
public:
	Button() = default;
	Button(const Button& other);
	Button(float x, float y, float width, float height, std::string btn_name, short op);
	void change_state(state s);
	bool is_pressed();
	void update(sf::RenderWindow &window);
	void render(sf::RenderWindow &window);
};

