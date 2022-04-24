#include "common.h"

void swap(data_t& a, data_t& b)
{	
	data_t temp = a;
	a = b;
	b = temp;
}

counter& bubble_counter(std::vector<data_t> data)
{
	counter operations;
	for (int i = 0; i < data.size() - 1; i++) {
		for (int j = 0; j < data.size() - i - 1; j++) {
			if (data[j] > data[j + 1]) {
				std::swap(data[j].value, data[j + 1].value);
				operations.swap();
			}
			operations.comp();
		}
	}
	return operations;
}

counter& selection_counter(std::vector<data_t> data)
{
	counter operations;
	int min_index = 0, min_value = data[0].value;
	for (int i = 0; i < data.size() - 1; i++) {
		for (int j = i; j < data.size(); j++) {
			if (data[j].value <= min_value) {
				min_value = data[j].value;
				min_index = j;
			}
			operations.comp();
		}
		std::swap(data[i].value, data[min_index].value);
		operations.swap();

		min_value = data[i + 1].value;
	}
	std::cout << operations << "|" << operations.expected << std::endl;
	return operations;
}

counter& insertion_counter(std::vector<data_t> data)
{
	counter operations;
	for (int i = 0; i < data.size(); i++) {
		int j = i;
		while ((j > 0) && (data[j - 1] > data[j])) {
			std::swap(data[j - 1].value, data[j].value);
			j--;
			operations.swap();
		}
	}
	return operations;
}

void inplacemerge_counter(std::vector<data_t> &v, counter &operations, int start, int end)
{
	int gap = end - start + 1;
	auto nextGap = [](int gap) { return gap <= 1 ? 0 : (int)std::ceil(gap / 2.0); };
	for (gap = nextGap(gap); gap > 0; gap = nextGap(gap))
	{
		for (int i = start; i + gap <= end; i++)
		{
			int j = i + gap;
			if (v[i].value > v[j].value) {
				std::swap(v[i].value, v[j].value);
				operations.swap();
			}
			operations.comp();
		}
	}
}

void merge_counter(std::vector<data_t> &v, counter &operations, int start, int end)
{
	if (start == end)
		return;

	int mid = (start + end) / 2;

	merge_counter(v, operations, start, mid);
	merge_counter(v, operations, mid + 1, end);

	inplacemerge_counter(v, operations, start, end);
}

void show_progress(counter &operations)
{
	int progress = int(std::ceil(
		(100 * (float)(*operations)) / (float)operations.expected));
	bool finished = *operations == operations.expected ? true : false;
	if (progress == 100 && !finished) progress--;
	int spaces_num = 100 - progress;
	char end = (finished) ? '\n' : '\r';
	std::cout << "PROGRESS: [";
	for (int i = 0; i < progress; i++) {
		std::cout << "=";
	}
	while (spaces_num--) {
		std::cout << " ";
	}
	std::cout << progress << "%]" << end;
}