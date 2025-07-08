#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>

int gN = 30;
int gM = 20;
int num = 4;
enum class Direction { Up, Down, Left, Right };
Direction currentDir = Direction::Left;

struct object
{
	int positionX = 0;
	int positionY = 0;
};

void Tick(object* snake, object& fruit)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && currentDir != Direction::Up)
	{
		currentDir = Direction::Down;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && currentDir != Direction::Down)
	{
		currentDir = Direction::Up;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && currentDir != Direction::Right)
	{
		currentDir = Direction::Left;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && currentDir != Direction::Left)
	{
		currentDir = Direction::Right;
	}

	for (int i = num - 1; i > 0; --i)
	{
		snake[i].positionX = snake[i - 1].positionX;
		snake[i].positionY = snake[i - 1].positionY;
	}

	switch (currentDir)
	{
	case Direction::Up:    --snake[0].positionY; break;
	case Direction::Down:  ++snake[0].positionY; break;
	case Direction::Left:  --snake[0].positionX; break;
	case Direction::Right: ++snake[0].positionX; break;
	}

	if (snake[0].positionX > gN) { snake[0].positionX = 0; }
	if (snake[0].positionX < 0) { snake[0].positionX = gN; }
	if (snake[0].positionY > gM) { snake[0].positionY = 0; }	
	if (snake[0].positionY < 0) { snake[0].positionY = gM; }

	if ((snake[0].positionX == fruit.positionX) && (snake[0].positionY == fruit.positionY))
	{
		num++;
		fruit.positionX = rand() % gN;
		fruit.positionY = rand() % gM;
	}

	for (int i = 1; i < num; ++i)
	{
		if ((snake[0].positionX == snake[i].positionX) && (snake[0].positionY == snake[i].positionY))
		{
			num = i;
			break;
		}
	}
}

int main()
{
	int size = 16;
	unsigned int width = size * gN;
	unsigned int height = size * gM;

	sf::RenderWindow window(sf::VideoMode({ width, height }), "Snake TW SFML");

	const sf::Texture textureRed("red.png");	// since C++17
	sf::Sprite spriteRed(textureRed);

	const sf::Texture textureWhite("white.png");
	sf::Sprite spriteWhite(textureWhite);

	object fruits;
	fruits.positionX = 10;
	fruits.positionY = 10;

	object snake[100];
	const double fps = 20.0;
	const auto invFps = std::chrono::duration<double>(1.0 / fps);
	auto nextFrame = std::chrono::steady_clock::now() + invFps;

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent()) // since C++17
		{
			if (event->is < sf::Event::Closed>())
			{
				window.close();
			}
		}
		
		Tick(snake, fruits);
		window.clear();

		for (int i = 0; i < gN; ++i)
		{
			for (int j = 0; j < gM; ++j)
			{
				sf::Vector2f pos(i * size, j * size);
				spriteWhite.setPosition(pos);
				window.draw(spriteWhite);
			}
		}

		for (int i = 0; i < num; ++i)
		{
			sf::Vector2f pos(snake[i].positionX * size, snake[i].positionY * size);
			spriteRed.setPosition(pos);
			window.draw(spriteRed);
		}
		
		sf::Vector2f positionFruits(fruits.positionX * size, fruits.positionY * size);
		spriteRed.setPosition(positionFruits);
		window.draw(spriteRed);

		window.display();
		std::this_thread::sleep_until(nextFrame);
		nextFrame += invFps;
	}

	return 0;
}