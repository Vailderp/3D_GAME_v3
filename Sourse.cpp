#include "engine.h"
#include "Settings.h"

float rot_speed = 50;
int main()
{
	sf::Clock clock;
	sf::Clock fps_clock;
	sf::Font font;
	font.loadFromFile("data/fonts/PressStart2P-Regular.ttf");
	sf::Text text;
	text.setCharacterSize(30);
	text.setFont(font);
	text.setFillColor(sf::Color(255, 0, 0, 150));
	text.setPosition(10, 10);
	
	sf::RenderWindow window(sf::VideoMode(800, 800), "Sprite3d", sf::Style::Default);

	ve::camera camera = ve::camera();
	ve::rect_3d rect_3d(400, 400, 100, 200, 200);

	while (window.isOpen())
	{
		float fps_currentTime = fps_clock.getElapsedTime().asSeconds();
		sf::Event e;
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
			}
		}

		rect_3d.setFrontTexture("data/rects/2048.png");
		rect_3d.setRotation(0, clock.getElapsedTime().asMilliseconds() / rot_speed, 0);
		rect_3d.move(0.1f, 0, 0);

		// update display
		window.clear();
		window.draw(rect_3d.drawable);

		float fps_lastTime = fps_clock.getElapsedTime().asSeconds();
		float fps = 1 / (fps_lastTime - fps_currentTime);
		text.setString(std::to_string(fps));
		window.draw(text);
		window.display();
	}

	return EXIT_SUCCESS;
}
