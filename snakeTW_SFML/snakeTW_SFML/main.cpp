#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>

int gN = 30;
int gM = 20;
int num = 4;

struct object
{
	int positionX = 0;
	int positionY = 0;
};

void Tick(object* snake, object& fruit)
{
	for (int i = num; i > 0; --i)
	{
		snake[i].positionX = snake[i - 1].positionX;
		snake[i].positionY = snake[i - 1].positionY;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		snake[0].positionY += 1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		snake[0].positionY -= 1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		snake[0].positionX -= 1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		snake[0].positionX += 1;
	}

	if ((snake[0].positionX == fruit.positionX) && (snake[0].positionY == fruit.positionY))
	{
		num++;
		fruit.positionX = rand() % gN;
		fruit.positionY = rand() % gM;
	}

	if (snake[0].positionX > gN) { snake[0].positionX = 0; }
	if (snake[0].positionX < 0) { snake[0].positionX = gN; }
	if (snake[0].positionY > gM) { snake[0].positionY = 0; }	
	if (snake[0].positionY < 0) { snake[0].positionY = gM; }

	for (int i = 1; i < num; ++i)
	{
		if ((snake[0].positionX == snake[i].positionX) && (snake[0].positionY == snake[i].positionY))
		{
			num = i;
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
	std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();
	using dsec = std::chrono::duration<double>;
	std::chrono::system_clock::duration invFpsLimit = std::chrono::duration_cast<std::chrono::system_clock::duration>(dsec(1.0 / 30.0)); // 60 FPS limit
	std::chrono::system_clock::time_point beginFrame = std::chrono::system_clock::now();
	std::chrono::system_clock::time_point endFrame = beginFrame + invFpsLimit;
	std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds> prevTimeInSeconds = std::chrono::time_point_cast<std::chrono::seconds>(beginFrame);
	
	unsigned int frameCountPerSecond = 0;
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
		std::cout << num;
		
		sf::Vector2f positionFruits(fruits.positionX * size, fruits.positionY * size);
		spriteRed.setPosition(positionFruits);
		window.draw(spriteRed);

		//window.draw(text);
		window.display();
		
		auto timeInSeconds = std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::system_clock::now());
		++frameCountPerSecond;
		if (timeInSeconds > prevTimeInSeconds)
		{
			frameCountPerSecond = 0;
			prevTimeInSeconds = timeInSeconds;
		}

		std::this_thread::sleep_until(endFrame);
		beginFrame = endFrame;
		endFrame = beginFrame + invFpsLimit;
	}

	return 0;
}