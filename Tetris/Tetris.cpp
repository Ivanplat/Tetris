#include "Tetris.h"

Tetris::Tetris()
{

    t1.loadFromFile("images/tiles.png");
    t2.loadFromFile("images/background.png");
    t3.loadFromFile("images/frame.png");



    dx = 0;
    rotate = false;
    colorNum = 1;
    timer = 0.0f;
    delay =  0.3f;


    s = sf::Sprite(t1);
    background = sf::Sprite(t2);
    frame = sf::Sprite(t3);
}

bool Tetris::Check()
{
    for (int i = 0; i < 4; i++) {
        if (a[i].x < 0 || a[i].x >= N || a[i].y >= M){
            return 0;
        }
        else if (field[a[i].y][a[i].x]) {
            return 0;
        }
    }
    return 1;
}

void Tetris::Start()
{
    srand(time(0));
    sf::RenderWindow window(sf::VideoMode(320, 480), "The Game!");

    while (window.isOpen()) {

       UpdateTime();
       CheckForKeyboard(window);
       Move();
       Rotate();
       Tick();
       CheckLines();
       Draw(window);
    }

}

void Tetris::UpdateTime()
{
    float time = clock.getElapsedTime().asSeconds();
    clock.restart();
    timer += time;
}

void Tetris::Move()
{
    for (int i = 0; i < 4; i++) {
     b[i] = a[i]; a[i].x += dx;
    }
    if (!Check()) {
        for (int i = 0; i < 4; i++){
        a[i] = b[i];
        }
    }
}

void Tetris::Rotate()
{
    if (rotate)
    {
        Point p = a[1]; //center of rotation
        for (int i = 0; i < 4; i++)
        {
            int x = a[i].y - p.y;
            int y = a[i].x - p.x;
            a[i].x = p.x - x;
            a[i].y = p.y + y;
        }
        if (!Check()) {
            for (int i = 0; i < 4; i++) { 
                a[i] = b[i]; }
        }
    }
}

void Tetris::Tick()
{
    if (timer > delay)
    {
        for (int i = 0; i < 4; i++) {
            b[i] = a[i]; a[i].y += 1; 
        }

        if (!Check())
        {
            for (int i = 0; i < 4; i++) {
                field[b[i].y][b[i].x] = colorNum; 
            }

            colorNum = 1 + rand() % 7;
            int n = rand() % 7;
            for (int i = 0; i < 4; i++)
            {
                a[i].x = figures[n][i] % 2;
                a[i].y = figures[n][i] / 2;
            }
        }

        timer = 0;
    }
}

void Tetris::CheckLines()
{
    int k = M - 1;
    for (int i = M - 1; i > 0; i--)
    {
        int count = 0;
        for (int j = 0; j < N; j++)
        {
            if (field[i][j]) count++;
            field[k][j] = field[i][j];
        }
        if (count < N) k--;
    }

    dx = 0;
    rotate = 0;
    delay = 0.3;
}

void Tetris::Draw(sf::RenderWindow& window)
{
    window.clear(sf::Color::White);
    window.draw(background);

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++)
        {
            if (field[i][j] == 0) {
                continue;
            }
            s.setTextureRect(sf::IntRect(field[i][j] * 18, 0, 18, 18));
            s.setPosition(j * 18, i * 18);
            s.move(28, 31); //offset
            window.draw(s);
        }
    }

    for (int i = 0; i < 4; i++)
    {
        s.setTextureRect(sf::IntRect(colorNum * 18, 0, 18, 18));
        s.setPosition(a[i].x * 18, a[i].y * 18);
        s.move(28, 31); //offset
        window.draw(s);
    }

    window.draw(frame);
    window.display();
}

void Tetris::CheckForKeyboard(sf::RenderWindow& window)
{
    while (window.pollEvent(e))
    {
        if (e.type == sf::Event::Closed)
            window.close();

        if (e.type == sf::Event::KeyPressed)
            if (e.key.code == sf::Keyboard::Up) rotate = true;
            else if (e.key.code == sf::Keyboard::Left) dx = -1;
            else if (e.key.code == sf::Keyboard::Right) dx = 1;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) delay = 0.05;
}
