#pragma once

#include "common.h"
#include "Menu.h"

class Visualizer
{
	private:
		sf::RenderWindow window;
		std::string name = "SFML WORKS";
		sf::Font font;
		sf::SoundBuffer buffer;
		sf::Sound sound;
		Menu menu;
		unsigned int samples;
		std::vector<data_t> data{};
		counter operations;
		void init();
		void highlight(data_t &a, data_t &b);
		void dehighlight(data_t& a, data_t& b);
		void progress_bar();
		void finish_highlight();

		void swap(data_t& a, data_t& b);
		void inplacemerge(int start, int end);
		void heapify(int n, int i);
	public:
		Visualizer();
		Visualizer(unsigned int samples);
		Visualizer(std::initializer_list<int> values);

		void generate_data();
		void shuffle_data();
		void visualize_data();
		void bubble();
		void selection();
		void insertion();
		void merge(int start, int end);
		void heap();


		void main_loop();
};

