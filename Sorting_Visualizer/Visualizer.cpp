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
    if (!buffer.loadFromFile("sound.wav"))
    {
        std::cerr << "SOUNDBUFFER ERROR" << std::endl;
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
    this->sound.setBuffer(buffer);
    this->sound.setVolume(20.f);

    this->window.clear(BACKGROUND);
    this->highlight(a, b);
    this->visualize_data();
    std::swap(a, b);
    //sound.play();
    sleep();
    //sound.stop();
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

void Visualizer::inplacemerge(int start, int end)
{
    int gap = end - start + 1;
    auto nextGap = [](int gap) { return gap <= 1 ? 0 : (int)std::ceil(gap / 2.0); };
    for (gap = nextGap(gap); gap > 0; gap = nextGap(gap))
    {
        for (int i = start; i + gap <= end; i++)
        {
            int j = i + gap;
            if (this->data[i] > this->data[j])
                this->swap(this->data[i], this->data[j]);
        }
    }
}

void Visualizer::generate_data()
{
    data_t temp;
    float data_width = static_cast<float>(SORT_WINDOW_WIDTH) / this->samples;
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

void Visualizer::finish_highlight()
{
    for (auto& d : data) {
        d.rect.setFillColor(FINISH_COLOR);
        this->visualize_data();
        sleep();
    }
    sleep();
    for (auto& d : data) 
        d.rect.setFillColor(DATA_COLOR);

}

void Visualizer::visualize_data()
{
    unsigned int index = 0;
    float data_width = (float)SORT_WINDOW_WIDTH / (float)this->samples;
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
            sound.setPitch(1 + std::ceil((100 * (float)operations) / (float)operations_expected) / 200);
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
        sound.setPitch(0.5 + std::ceil((100 * (float)operations) / (float)operations_expected) / 200);
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
            sound.setPitch(0.5 + std::ceil((100 * (float)operations) / (float)operations_expected) / 200);
        }
    }
    std::cout << "INSERTION ENDED\n";
}

void Visualizer::merge(int start, int end)
{
    if (start == end)
        return;

    int mid = (start + end) / 2;

    merge(start, mid);
    merge(mid + 1, end);

    inplacemerge(start, end);
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
                        case sf::Keyboard::A: this->bubble(); finish_highlight(); break;
                        case sf::Keyboard::S: this->selection(); finish_highlight(); break;
                        case sf::Keyboard::D: this->insertion(); finish_highlight(); break;
                        case sf::Keyboard::F: this->merge(0, this->samples-1); finish_highlight(); break;
                        case sf::Keyboard::R: this->generate_data(); break;
                        case sf::Keyboard::T: 
                            for (int i = 0; i < 4; i++) {
                                this->generate_data();
                                switch (i)
                                {
                                case 0: this->bubble(); break;
                                case 1: this->selection(); break;
                                case 2: this->insertion(); break;
                                case 3: this->merge(0, this->samples - 1); break;
                                }
                                this->finish_highlight();
                            }
                            break;
                    }
                    break;
                default:
                    break;
            }
        }
        this->visualize_data();
    }
}