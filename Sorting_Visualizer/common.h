#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <random>
#include <thread>
#include <chrono>

constexpr auto WINDOW_WIDTH = 1000;
constexpr auto WINDOW_HEIGHT = 600;
constexpr auto MENU_WIDTH = 200;
constexpr auto SORT_WINDOW_WIDTH = WINDOW_WIDTH - MENU_WIDTH;
constexpr auto OUTLINE_THICKNESS = 0.75f;
constexpr auto SLEEP_TIME = 1;

#define BACKGROUND sf::Color::White
#define HIGHLIGHT_COLOR1 sf::Color::Blue
#define HIGHLIGHT_COLOR2 sf::Color::Magenta
#define DATA_COLOR sf::Color::Yellow
#define FINISH_COLOR sf::Color::Green

#define sleep() std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME))


struct data_t {
	int value = -1;
	sf::RectangleShape rect;

	bool operator>(const data_t& other) const { return this->value > other.value; }
	bool operator<(const data_t& other) const { return this->value < other.value; }
	bool operator==(const data_t& other) const { return this->value == other.value; }
	bool operator<=(const data_t& other) const { return (this->value < other.value) || (this->value == other.value); }
	bool operator>=(const data_t& other) const { return (this->value > other.value) || (this->value == other.value); }

	friend std::ostream& operator<<(std::ostream& os, const data_t& data)
	{
		os << data.value;
		return os;
	}
	data_t& operator=(const data_t& other)
	{
		this->value = other.value;
		this->rect.setSize(other.rect.getSize());
		return *this;
	}
};

void swap(data_t& a, data_t& b);

[[nodiscard("Only purpouse is to get the number of operations")]] 
unsigned int bubble_counter(std::vector<data_t> data);

[[nodiscard("Only purpouse is to get the number of operations")]]
unsigned int selection_counter(std::vector<data_t> data);

[[nodiscard("Only purpouse is to get the number of operations")]]
unsigned int insertion_counter(std::vector<data_t> data);


void show_progress(unsigned int state, unsigned int full);