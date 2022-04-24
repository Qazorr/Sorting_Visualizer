#pragma once

#include "common.h"

class Visualizer
{
	private:
		sf::RenderWindow window;
		std::string name = "SFML WORKS";
		sf::Font font;
		sf::SoundBuffer buffer;
		sf::Sound sound;
		unsigned int samples;
		std::vector<data_t> data{};
		void init();
		//change these 2 to varargs
		void highlight(data_t &a, data_t &b);
		void dehighlight(data_t& a, data_t& b);
		void swap(data_t& a, data_t& b);
		void inplacemerge(int start, int end);
		void finish_highlight();
	public:
		Visualizer();
		Visualizer(unsigned int samples);
		Visualizer(std::initializer_list<int> values);
		void generate_data();
		void visualize_data();
		void bubble();
		void selection();
		void insertion();
		void merge(int start, int end);
		void main_loop();
};

