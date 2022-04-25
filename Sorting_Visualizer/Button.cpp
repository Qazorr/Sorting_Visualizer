#include "Button.h"

Button::Button(float x, float y, float width, float height, std::string btn_name, short op): operation(op)
{
	if (!this->font.loadFromFile(FONT_NAME_2))
	{
		std::cerr << "FONT ERROR" << std::endl;
		exit(-1);
	}

	button_state = idle;

	button_area.setFillColor(colors[idle]);
	button_area.setPosition(x, y);
	button_area.setSize(sf::Vector2f(width, height));
	button_area.setOutlineThickness(1.f);
	button_area.setOutlineColor(sf::Color::Black);

	this->name = sf::Text(btn_name, this->font, 25);

	sf::Vector2f center(
		(name.getGlobalBounds().width / 2.f) + name.getLocalBounds().width,
		(name.getGlobalBounds().height / 2.f) + name.getLocalBounds().height
	);
	sf::Vector2f rounded(
		std::round(center.x),
		std::round(center.y)
	);

	name.setOrigin(rounded);
	name.setPosition(
		x+button_area.getSize().x / 2 + name.getLocalBounds().width,
		y+button_area.getSize().y / 2 + name.getLocalBounds().height / 2 
	);
	name.setFillColor(sf::Color::White);

	std::cout << "\033[32m[BUTTON]\033[0m\033[33m " << btn_name << " \033[0m INITIALIZED\n";
}

Button::Button(const Button& other)
{
	std::cout << "IM BEING CALLED\n";
}

void Button::change_state(state s)
{
	if (button_state != s) {
		button_state = s;
		button_area.setFillColor(colors[s]);
		//std::cout << "\033[32m[BUTTON " << std::string(this->name.getString()) << "]\033[0m \033[33mSTATE CHANGED TO " << s << std::endl;
	}
}

void Button::update(sf::RenderWindow &window)
{
	if (button_state != click) {
		if (button_area.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
			change_state(hover);
		else
			change_state(idle);
		if (button_state == hover && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			change_state(click);
	}
}

bool Button::is_pressed() { return this->button_state == click; }

void Button::render(sf::RenderWindow &window)
{
	this->update(window);
	window.draw(this->button_area);
	window.draw(this->name);
}