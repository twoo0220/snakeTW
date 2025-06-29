#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Snake TW SFML");

	const sf::Texture textureRed("red.png");
	sf::Sprite spriteRed(textureRed);

	const sf::Texture textureWhite("white.png");
	sf::Sprite spriteWhite(textureWhite);

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is < sf::Event::Closed>())
			{
				window.close();
			}
		}

		window.clear();
		window.draw(spriteRed);
		window.draw(spriteWhite);
		
		//window.draw(text);
		window.display();
	}

	return 0;
}