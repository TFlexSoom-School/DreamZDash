/*
 * Tristan Hilbert
 * 2/5/2020
 * This is a quick sample project with SFML to show graphics are working
 */

 #include <SFML/Graphics.hpp>

 int main()
 {
     sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
     sf::RectangleShape shape(sf::Vector2f(200.0, 150.0));
     shape.setFillColor(sf::Color::Yellow);

     while (window.isOpen())
     {
         sf::Event event;
         while (window.pollEvent(event))
         {
             if (event.type == sf::Event::Closed)
                 window.close();
         }

         window.clear();
         window.draw(shape);
         window.display();
     }

     return 0;
 }
