#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
using namespace sf;

//g++ main.cpp -o main -I/opt/homebrew/Cellar/sfml/2.6.1/include -L/opt/homebrew/Cellar/sfml/2.6.1/lib -lsfml-graphics -lsfml-window -lsfml-system
const int M = 20;
const int N = 10;

int field[M][N] = {0};

struct Point {
    int x, y;
} a[4], b[4];

int figures[7][4] = {
    1, 3, 5, 7, // I
    2, 4, 5, 7, // Z
    3, 5, 4, 6, // S
    3, 5, 4, 7, // T
    2, 3, 5, 7, // L
    3, 5, 7, 6, // J
    2, 3, 4, 5, // O
};

bool isValidMove() {
    for (int i = 0; i < 4; i++)
        if (a[i].x < 0 || a[i].x >= N || a[i].y >= M || field[a[i].y][a[i].x]) 
            return false;
    return true;
};

int main() {
    srand(time(0));
    RenderWindow window(VideoMode(320, 480), "Tetris");

    // Load textures
    Texture textureTiles, textureBackground, textureFrame;
    textureTiles.loadFromFile("images/tiles.png");
    textureBackground.loadFromFile("images/background.png");
    textureFrame.loadFromFile("images/frame.png");

    Sprite spriteTiles(textureTiles), spriteBackground(textureBackground), spriteFrame(textureFrame);

    int dx = 0;
    bool needRotate = false;
    int tileColor = 1;
    float timer = 0, delay = 0.3;

    Clock clock;

    // Initialize score and font
    int score = 0;
    Font font;
    if (!font.loadFromFile("images/font.ttf")) {
        std::cerr << "Error loading font" << std::endl;
        return 1;
    }

    Text textScore;
    textScore.setFont(font);
    textScore.setCharacterSize(24);
    textScore.setFillColor(Color::White);
    textScore.setPosition(320, 20);

    while (window.isOpen()) {
        float timeElapsed = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += timeElapsed;

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Up) needRotate = true;
                else if (event.key.code == Keyboard::Left) dx = -1;
                else if (event.key.code == Keyboard::Right) dx = 1;
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Down)) delay = 0.05;

        // Move
        for (int i = 0; i < 4; i++) {
            b[i] = a[i];
            a[i].x += dx;
        }
        if (!isValidMove()) for (int i = 0; i < 4; i++) a[i] = b[i];

        // Rotate
        if (needRotate) {
            Point center = a[1];
            for (int i = 0; i < 4; i++) {
                int x = a[i].y - center.y;
                int y = a[i].x - center.x;
                a[i].x = center.x - x;
                a[i].y = center.y + y;
            }
            if (!isValidMove()) for (int i = 0; i < 4; i++) a[i] = b[i];
        }

        // Tick
        if (timer > delay) {
            for (int i = 0; i < 4; i++) {
                b[i] = a[i];
                a[i].y += 1;
            }

            if (!isValidMove()) {
                for (int i = 0; i < 4; i++) field[b[i].y][b[i].x] = tileColor;

                tileColor = 1 + rand() % 7;
                int n = rand() % 7;
                for (int i = 0; i < 4; i++) {
                    a[i].x = figures[n][i] % 2;
                    a[i].y = figures[n][i] / 2;
                }
            }

            timer = 0;
        }

        // Check lines
        int k = M - 1;
        for (int i = M - 1; i > 0; i--) {
            int count = 0;
            for (int j = 0; j < N; j++) {
                if (field[i][j]) count++;
                field[k][j] = field[i][j];
            }
            if (count < N) k--;
            else score += 100;
        }

        dx = 0;
        needRotate = false;
        delay = 0.3;

        // Draw
        window.clear(Color::White);
        window.draw(spriteBackground);

        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++) {
                if (field[i][j] == 0) continue;
                spriteTiles.setTextureRect(IntRect(field[i][j] * 18, 0, 18, 18));
                spriteTiles.setPosition(j * 18, i * 18);
                spriteTiles.move(28, 31); //offset
                window.draw(spriteTiles);
            }

        for (int i = 0; i < 4; i++) {
            spriteTiles.setTextureRect(IntRect(tileColor * 18, 0, 18, 18));
            spriteTiles.setPosition(a[i].x * 18, a[i].y * 18);
            spriteTiles.move(28, 31); //offset
            window.draw(spriteTiles);
        }

        // Display Score
        textScore.setString("Score: " + std::to_string(score));
        window.draw(textScore);

        window.draw(spriteFrame);
        window.display();
    }

    return 0;
}
