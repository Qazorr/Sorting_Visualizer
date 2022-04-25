#include <iostream>
#include <SFML/Graphics.hpp>

#include "Visualizer.h"

int main()
{
	Visualizer visualizer(SAMPLES);
	visualizer.main_loop();
}