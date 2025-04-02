#include <iostream>

#include <engine.hpp>

int main(int, char **)
{
    std::cout << "Hello, from basic_library!\n";
    Engine *engine = new Engine();
    double l = engine->getLength();

    delete engine;
}
