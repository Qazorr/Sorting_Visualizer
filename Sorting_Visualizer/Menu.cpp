#include "Menu.h"

Menu::Menu()
{
	this->menu_area.setSize(sf::Vector2f(MENU_WIDTH, WINDOW_HEIGHT));
	this->menu_area.setPosition(SORT_WINDOW_WIDTH, WINDOW_HEIGHT);
	this->menu_area.setFillColor(sf::Color(100, 0, 0));
	int i = 0;
	for (; i <= COUNT; i++) {
		sort_buttons.push_back(
			std::unique_ptr<Button>(
				new Button(
					SORT_WINDOW_WIDTH + BTN_OFFSET,
					BTN_OFFSET * (2.25f * i + 1),
					MENU_WIDTH - 2 * BTN_OFFSET,
					BTN_HEIGHT,
					get_name(i),
					i
				))
		);
	}
	shuffle_button = std::unique_ptr<Button>(new Button(
		SORT_WINDOW_WIDTH + BTN_OFFSET,
		BTN_OFFSET * (2.25f * (i++ + 1)),
		MENU_WIDTH - 2 * BTN_OFFSET,
		BTN_HEIGHT,
		"SHUFFLE",
		COUNT+1
	));
	reset_button = std::unique_ptr<Button>(new Button(
		SORT_WINDOW_WIDTH + BTN_OFFSET,
		BTN_OFFSET * (2.25f * (i++ + 1)),
		MENU_WIDTH - 2 * BTN_OFFSET,
		BTN_HEIGHT,
		"RESET",
		COUNT + 1
	));
	std::cout << "\033[32m[MENU]\033[0m INITIALIZED\n";
}

void Menu::render(sf::RenderWindow& window)
{
	window.draw(menu_area);
	for (auto& button : sort_buttons)
		button->render(window);
	reset_button->render(window);
	shuffle_button->render(window);
}
