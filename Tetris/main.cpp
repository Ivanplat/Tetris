#include "SFML/Graphics.hpp"
#include "boost/thread.hpp"
#include <time.h>
#include <thread>
#include <iostream>
#include "Tetris.h"

void Start() {
    Tetris* Ts = new Tetris();

    srand(time(0));
    sf::RenderWindow window(sf::VideoMode(320, 480), "Tetris");

    while (window.isOpen()) {

        Ts->UpdateTime();
        Ts->CheckForKeyboard(window);
        Ts->Move();
        Ts->Rotate();
        Ts->Tick();
        Ts->CheckLines();
        Ts->Draw(window);
    }

}

int main() {

	boost::thread_group tgroup;

	tgroup.create_thread(boost::bind(&Start));
	tgroup.join_all();

	return 0;
}