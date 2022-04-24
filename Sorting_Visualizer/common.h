#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <random>
#include <thread>
#include <chrono>

constexpr auto WINDOW_WIDTH = 1200;
constexpr auto WINDOW_HEIGHT = 600;
constexpr auto MENU_WIDTH = 200;
constexpr auto PROGRESS_HEIGHT = 25;
constexpr auto SORT_WINDOW_WIDTH = WINDOW_WIDTH - MENU_WIDTH;
constexpr auto SORT_WINDOW_HEIGHT = WINDOW_HEIGHT - PROGRESS_HEIGHT;
constexpr auto OUTLINE_THICKNESS = 0.75f;
constexpr auto SLEEP_TIME = 0;

#define BACKGROUND sf::Color(128, 128, 128)
#define HIGHLIGHT_COLOR1 sf::Color::Blue
#define HIGHLIGHT_COLOR2 sf::Color::Magenta
#define DATA_COLOR sf::Color::Yellow
#define FINISH_COLOR sf::Color::Green
#define PROGRESS_BAR_COLOR sf::Color(0, 100, 0)

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

struct counter {
	unsigned int comparison = 0;
	unsigned int swaps = 0;
	unsigned int expected = 0;
	counter() = default;
	counter(const counter& other) { this->expected = other.comparison + other.swaps; }
	void reset() { comparison = 0; swaps = 0; }
	void full_reset() { comparison = 0; swaps = 0; expected = 0; }
	void comp() { comparison++; }
	void swap() { swaps++; }
	void combine() { expected = comparison + swaps; reset(); }
	counter& operator=(const counter& other)
	{
		this->reset();
		this->expected = other.comparison + other.swaps;
		return *this;
	}
	unsigned int operator*() { return this->comparison + this->swaps; }
	friend std::ostream& operator<<(std::ostream& os, const counter& c) { os << c.comparison + c.swaps; return os; }
};

void swap(data_t& a, data_t& b);

[[nodiscard("Only purpouse is to get the number of operations")]] 
counter& bubble_counter(std::vector<data_t> data);

[[nodiscard("Only purpouse is to get the number of operations")]]
counter& selection_counter(std::vector<data_t> data);

[[nodiscard("Only purpouse is to get the number of operations")]]
counter& insertion_counter(std::vector<data_t> data);

void inplacemerge_counter(std::vector<data_t> &data, counter& operations, int start, int end);

void merge_counter(std::vector<data_t> &data, counter &operations, int start, int end);

void show_progress(counter &operations);