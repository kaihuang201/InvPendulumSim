#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <sys/time.h>

#include "InvPendulumEngine.h"

using std::cout;
using std::endl;

const int ROD_LEN = 150;
const int ROD_THICKNESS = 5;
const int RAIL_Y = 400;
const int PIVOT_RADIAS = 10;
const int CART_W = 60;
const int CART_H = 40;

void drawCartAndRod(int x, float rodAngle, sf::RenderWindow& app) {
    sf::RectangleShape cart(sf::Vector2f(CART_W, CART_H));
    cart.setOrigin(CART_W/2, CART_H/2);
    cart.setPosition(x, RAIL_Y);
    app.draw(cart);

    sf::RectangleShape rod(sf::Vector2f(ROD_THICKNESS, ROD_LEN));
    rod.setOrigin(ROD_THICKNESS/2, ROD_LEN);
    rod.setPosition(x, RAIL_Y);
    rod.rotate(rodAngle);
    rod.setFillColor(sf::Color(100, 220, 50));
    app.draw(rod);

    sf::Vector2f origin = rod.getOrigin();
    sf::CircleShape pivot(PIVOT_RADIAS);
    pivot.setPosition(rod.getPosition() - sf::Vector2f(PIVOT_RADIAS,PIVOT_RADIAS));
    pivot.setFillColor(sf::Color(100, 220, 50));
    app.draw(pivot);
}

int main()
{
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(800, 600), "SFML window");

    InvPendulumEngine engine;
    engine.Set_pen_angle(45.0);

    double timestep = engine.Get_time_step();
    double accumulator = 0;
    sf::Clock clock;
    sf::Time prev_time = clock.getElapsedTime();
    sf::Time last_draw_time = prev_time;

	// Start the game loop
    while (app.isOpen())
    {
        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();
        }

        sf::Time curr_time = clock.getElapsedTime();
        sf::Time elapsed = curr_time - prev_time;
        double dt = (double)elapsed.asSeconds();
        prev_time = curr_time;
        accumulator += dt;

        while (accumulator >= timestep)
        {
            // step physics engine
            engine.step();
            accumulator -= timestep;
        }

        if (curr_time - last_draw_time > sf::seconds(0.03f))
        {
            last_draw_time = curr_time;
            // Clear screen
            app.clear();
            drawCartAndRod((int)engine.Get_cart_pos() + 500, (int)engine.Get_pen_angle(), app);
            // Update the window
            app.display();
        }
    }

    return EXIT_SUCCESS;
}
