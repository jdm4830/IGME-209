#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>

using namespace std;
using namespace sf;

// window size
unsigned int win_W = 800;
unsigned int win_H = 800;

// deltaTime
Time g_preDeltaTime;
Clock g_deltaClock;

// define a ball
float ballRadius = 50.f;
CircleShape ball(ballRadius);
Vector2f velocity;

// define the gravity
Vector2f gravity = Vector2f(0, -9.8f);

void Init(sf::RenderWindow& window) {
    // set up ball 
    ball.setOrigin(ballRadius, ballRadius);
    ball.setFillColor(Color::Blue);
    ball.setPosition(win_W / 2, win_H / 2);

    // randomly initialize velocity
    srand(time(NULL));
    velocity.x = rand() % 400 + 100;
    velocity.y = rand() % 400 + 100;
}

void Update(sf::RenderWindow& window) {
    // calculate deltaTime
    Time currentTime = g_deltaClock.getElapsedTime();
    Time deltaTime = currentTime - g_preDeltaTime;
    float deltaSeconds = deltaTime.asSeconds();
    g_preDeltaTime = currentTime;

    // Write your code below

     //Update Position
    velocity += gravity * deltaSeconds;
    ball.setPosition(ball.getPosition() + velocity * deltaSeconds);

    //Force of gravity on the ball, keeping the ball from bouncing all around window
    //Makes it actually "bounce"
    velocity -= gravity;

    //Boundary for Window Sides
    if (ball.getPosition().x - ballRadius < 0 || ball.getPosition().x + ballRadius > win_W)
    {
        velocity.x *= -1;
    }
    //Make sure it bounces when it hits the ground
    if (ball.getPosition().y - ballRadius < 0 ) {
        velocity.y = abs(velocity.y);
    }
    if (ball.getPosition().y + ballRadius > win_H) {
        velocity.y = -abs(velocity.y);
    }

    // Write your code above
}

void Render(sf::RenderWindow& window) {
    // draw the ball
    window.draw(ball);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(win_W, win_H), "IGME209-E09");

    window.setFramerateLimit(60);

    Init(window);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(255, 255, 255)); // clear the window with color(255,255,255)

        Update(window);
        Render(window);

        window.display(); // display the window
    }

    return 0;
}