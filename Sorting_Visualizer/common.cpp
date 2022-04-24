#include "common.h"

void swap(data_t& a, data_t& b)
{	
	data_t temp = a;
	a = b;
	b = temp;
}

unsigned int bubble_counter(std::vector<data_t> data)
{
	unsigned int operations = 0;
	for (int i = 0; i < data.size() - 1; i++) {
		for (int j = 0; j < data.size() - i - 1; j++) {
			if (data[j] > data[j + 1]) {
				std::swap(data[j].value, data[j + 1].value);
				operations++;
			}
			operations++;
		}
	}
	return operations;
}

unsigned int selection_counter(std::vector<data_t> data)
{
	int operations = 0, min_index = 0, min_value = data[0].value;
	for (int i = 0; i < data.size() - 1; i++) {
		for (int j = i; j < data.size(); j++) {
			if (data[j].value <= min_value) {
				min_value = data[j].value;
				min_index = j;
			}
			operations++;
		}
		std::swap(data[i].value, data[min_index].value);
		operations++;
		min_value = data[i + 1].value;
	}
	return operations;
}

unsigned int insertion_counter(std::vector<data_t> data)
{
	unsigned int operations = 0;
	for (int i = 0; i < data.size(); i++) {
		int j = i;
		while ((j > 0) && (data[j - 1] > data[j])) {
			std::swap(data[j - 1].value, data[j].value);
			j--;
			operations++;
		}
	}
	return operations;
}

void show_progress(unsigned int state, unsigned int full)
{
	int progress = int(std::ceil((100 * (float)state) / (float)full));
	if (progress == 100 && state != full) progress--;
	int spaces_num = 100 - progress;
	char end = (state == full) ? '\n' : '\r';
	std::cout << "PROGRESS: [";
	for (int i = 0; i < progress; i++) {
		std::cout << "=";
	}
	while (spaces_num--) {
		std::cout << " ";
	}
	std::cout << progress << "%]" << end;
}
