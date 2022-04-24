#include "Visualizer.h"

void Visualizer::init()
{
    srand(time(NULL));
    this->window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), this->name);
    if (!this->font.loadFromFile("arial.ttf"))
    {
        std::cerr << "FONT ERROR" << std::endl;
        exit(-1);
    }
}

void Visualizer::highlight(data_t& a, data_t& b)
{
    a.rect.setFillColor(HIGHLIGHT_COLOR1);
    b.rect.setFillColor(HIGHLIGHT_COLOR2);
}

void Visualizer::dehighlight(data_t& a, data_t& b)
{
    a.rect.setFillColor(DATA_COLOR);
    b.rect.setFillColor(DATA_COLOR);
}

void Visualizer::swap(data_t& a, data_t& b)
{
    this->window.clear(BACKGROUND);
    this->highlight(a, b);
    this->visualize_data();
    std::swap(a, b);
    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME));

    this->window.clear(BACKGROUND);
    this->highlight(a, b);
    this->visualize_data();
    this->dehighlight(a, b);
}

Visualizer::Visualizer(): samples(100) { this->init(); }

Visualizer::Visualizer(unsigned int samples) : samples(samples)
{
    this->init();
    this->generate_data();
    this->samples = samples;
}

Visualizer::Visualizer(std::initializer_list<int> values)
{
    this->init();
    data_t temp;
    this->samples = values.size();
    float data_width = static_cast<float>(WINDOW_WIDTH) / this->samples;
    unsigned int i = 0;
    for (auto& x : values) {
        temp.value = x;
        temp.rect.setSize(sf::Vector2f(data_width - 2.f * OUTLINE_THICKNESS, -temp.value));
        temp.rect.setFillColor(DATA_COLOR);
        temp.rect.setOutlineThickness(OUTLINE_THICKNESS);
        temp.rect.setOutlineColor(sf::Color::Black);
        temp.rect.setPosition(sf::Vector2f(
            i * data_width,
            WINDOW_HEIGHT
        ));
        data.push_back(temp);
        i++;
    }
}

void Visualizer::generate_data()
{
    data_t temp;
    float data_width = static_cast<float>(WINDOW_WIDTH) / this->samples;
    this->data.clear();
    for (unsigned i = 0; i < this->samples; i++) {
        temp.value = (rand() % (WINDOW_HEIGHT - 10)) + 10;
        temp.rect.setSize(sf::Vector2f(data_width - 2.f * OUTLINE_THICKNESS, -temp.value));
        temp.rect.setFillColor(DATA_COLOR);
        temp.rect.setOutlineThickness(OUTLINE_THICKNESS);
        temp.rect.setOutlineColor(sf::Color::Black);
        temp.rect.setPosition(sf::Vector2f(
            i * data_width,
            WINDOW_HEIGHT
        ));
        data.push_back(temp);
    }
}

void Visualizer::visualize_data()
{
    unsigned int index = 0;
    float data_width = (float)WINDOW_WIDTH / (float)this->samples;
    sf::RectangleShape rect;
    this->window.clear(BACKGROUND);
    for (auto& val : this->data) {
        this->window.draw(val.rect);
        index++;
    }
    this->window.display();
}

void Visualizer::bubble()
{
    unsigned int operations = 0, operations_expected = bubble_counter(this->data);
    std::cout << "BUBBLE STARTED\n";
    for (int i = 0; i < data.size() - 1; i++) {
        for (int j = 0; j < data.size() - i - 1; j++) {
            if (data[j] > data[j + 1]) {
                this->swap(data[j], data[j + 1]);
                operations++;
            }
            operations++;
            show_progress(operations, operations_expected);
        }
    }
    std::cout << "BUBBLE ENDED\n";
}

void Visualizer::selection()
{
    unsigned int operations = 0, min_index = 0, operations_expected = selection_counter(this->data);
    int min_value = data[0].value;
    std::cout << "SELECTION STARTED\n";
    for (int i = 0; i < data.size() - 1; i++) {
        for (int j = i; j < data.size(); j++) {
            if (data[j].value <= min_value) {
                min_value = data[j].value;
                min_index = j;
            }
            operations++;
        }
        this->swap(data[i], data[min_index]);
        operations++;
        show_progress(operations, operations_expected);
        min_value = data[i + 1].value;
    }
    std::cout << "SELECTION ENDED\n";
}

void Visualizer::insertion()
{
    unsigned int operations = 0, operations_expected = insertion_counter(this->data);
    std::cout << "INSERTION STARTED\n";
    for (int i = 0; i < this->data.size(); i++) {
        int j = i;
        while ((j > 0) && (data[j - 1] > data[j])) {
            this->swap(data[j - 1], data[j]);
            j--;
            operations++;
            show_progress(operations, operations_expected);
        }
    }
    std::cout << "INSERTION ENDED\n";
}

void Visualizer::main_loop()
{
    while (this->window.isOpen())
    {
        sf::Event event;
        while (this->window.pollEvent(event))
        {
            switch(event.type) 
            {
                case sf::Event::Closed:
                    this->window.close();
                    break;
                case sf::Event::KeyPressed:
                    switch (event.key.code)
                    {
                        case sf::Keyboard::Escape: this->window.close(); break;
                        case sf::Keyboard::A: this->bubble(); break;
                        case sf::Keyboard::S: this->selection(); break;
                        case sf::Keyboard::D: this->insertion(); break;
                        case sf::Keyboard::R: this->generate_data(); break;
                    }
                    break;
                default:
                    break;
            }
        }
        this->visualize_data();
    }
}

