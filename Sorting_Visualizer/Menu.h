#pragma once

#include "Button.h"

class Menu
{
private:
	sf::RectangleShape menu_area;
public:
	std::vector<std::unique_ptr<Button>> sort_buttons;
	std::unique_ptr<Button> reset_button;
	std::unique_ptr<Button> shuffle_button;
	Menu();
	void render(sf::RenderWindow &window);
};