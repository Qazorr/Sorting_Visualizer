#include "common.h"

std::string get_name(int sort)
{
	switch (sort)
	{
		case bubble: return "BUBBLE";
		case selection: return "SELECTION";
		case insertion: return "INSERTION";
		case merge: return "MERGE";
		case heap: return "HEAP";
		default: return "EMPTY";
	}
	return "EMPTY";
}

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

void heapify_counter(std::vector<data_t>& data, counter& ops, int n, int i)
{
	int largest = i, left = 2 * i + 1, right = 2 * i + 2;

	if (left < n && data[left] > data[largest])
		largest = left;
	ops.comp();

	if (right < n && data[right] > data[largest])
		largest = right;
	ops.comp();

	if (largest != i) {
		ops.comp();
		std::swap(data[i], data[largest]);
		ops.swap();
		heapify_counter(data, ops, n, largest);
	}
}

counter& heap_counter(std::vector<data_t>& data)
{
	counter operations;
	for (int i = data.size() / 2 - 1; i >= 0; i--)
		heapify_counter(data, operations, data.size(), i);

	for (int i = data.size() - 1; i > 0; i--) {
		std::swap(data[0], data[i]);
		operations.swap();
		heapify_counter(data, operations, i, 0);
	}
	return operations;
}

void show_progress(counter &operations)
{
	int progress = int(std::ceil(
		(100 * (float)(*operations)) / (float)operations.expected));
	bool finished = *operations == operations.expected ? true : false;
	if (progress == 100 && !finished) progress--;
	int spaces_num = 100 - progress;
	char end = (finished) ? '\n' : '\r';
	std::cout << "PROGRESS: [\033[1;35m";
	for (int i = 0; i < progress; i++) {
		std::cout << "=";
	}
	std::cout << "\033[0m";
	while (spaces_num--) {
		std::cout << " ";
	}
	std::cout << "\033[1;32m" << progress << "%\033[0m]" << end;
}