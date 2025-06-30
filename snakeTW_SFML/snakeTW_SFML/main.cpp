#include <SFML/Graphics.hpp>
#include <iostream>

struct object
{
	int positionX = 0;
	int positionY = 0;
};

int main()
{
	int N = 30;
	int M = 20;
	int size = 16;
	unsigned int width = size * N;
	unsigned int height = size * M;

	sf::RenderWindow window(sf::VideoMode({ width, height }), "Snake TW SFML");

	const sf::Texture textureRed("red.png");	// since C++17
	sf::Sprite spriteRed(textureRed);

	const sf::Texture textureWhite("white.png");
	sf::Sprite spriteWhite(textureWhite);

	object fruits;
	fruits.positionX = 10;
	fruits.positionY = 10;

	object snake[100];

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

		for (int i = 0; i < width; ++i)
		{
			for (int j = 0; j < height; ++j)
			{
				sf::Vector2f pos(i * size, j * size);
				spriteRed.setPosition(pos);
				window.draw(spriteRed);
			}
		}

		for (int i = 0; i < 4; ++i)
		{
			sf::Vector2f pos(snake[i].positionX * size, snake[i].positionY * size);
			spriteWhite.setPosition(pos);
			window.draw(spriteWhite);
		}
		
		sf::Vector2f positionFruits(fruits.positionX * size, fruits.positionY * size);
		spriteWhite.setPosition(positionFruits);
		window.draw(spriteWhite);

		//window.draw(text);
		window.display();
	}

	return 0;
}