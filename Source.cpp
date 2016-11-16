#include <SFML/Graphics.hpp>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include<string>
#include <time.h>		/* time */
using namespace sf;


std::string to_string(int val)
{
	std::string rev = "";
	while (val != 0)
	{
		rev += val % 10 + '0';
		val /= 10;
	}
	std::string ret = "";
	for (int i = rev.size() - 1; i >= 0; i--)
		ret += rev[i];
	return ret;
}

void Island(RectangleShape(&rec)[8][8]) {
	int row = 8, col = 8;
	//Island size info
	float recWidth = 100.0;
	float recHeight = 100.0;
	//Island position info
	float initialPosX = 100.0, a = 100.0;
	float initalPosY = 100.0;

	//Initializing the Island
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			rec[i][j].setSize(Vector2f(recWidth, recHeight));
			rec[i][j].setFillColor(Color::Yellow);
			rec[i][j].setPosition(Vector2f(initialPosX, initalPosY));
			initialPosX += recWidth;
		}
		initialPosX = a;
		initalPosY += recHeight;
	}
}

void Bridge(RectangleShape &bridge) {
	float recWidth = 100.0;
	float recHeight = 100.0;
	//Position of Bridge info
	float xPosBr = 900;
	float yPosBr = 500;
	//Initializing the Bridge
	bridge.setSize(Vector2f(recWidth, recHeight));
	bridge.setFillColor(Color::Black);
	bridge.setPosition(Vector2f(xPosBr, yPosBr));
}

void Cats(RectangleShape(&cat)[4], float(&xCat)[4], float(&yCat)[4]) {
	//Cat size info
	float catWidth = 100.0;
	float catHeight = 100.0;
	//To initialize for creating random number for cat movement
	int xCatRan, yCatRan;
	//Initializing the Cats and their Random Positions
	for (int j = 0; j < 4; j++) {
		xCatRan = (rand() % 5) + 3;
		yCatRan = (rand() % 5) + 3;
		xCat[j] = xCatRan * 100.0;
		yCat[j] = yCatRan * 100.0;
		cat[j].setSize(Vector2f(catWidth, catHeight));
		cat[j].setFillColor(Color::Red);
		cat[j].setPosition(Vector2f(xCat[j], yCat[j]));
	}
}

void Far(CircleShape &mouse) {
	float mouseRad = 50.0;
	//Mouse Position info
	float xPosMs = 100.0, yPosMs = 100.0;
	//Initializing the Mouse and its Position
	mouse.setRadius(mouseRad);
	mouse.setFillColor(Color::Green);
	mouse.setPosition(Vector2f(xPosMs, yPosMs));
}

int main()
{
	//To make time as the method for calling random numbers
	srand(time(NULL));
	//Number of rows and columns of rectangle shapes to make island

	int row = 8;
	int col = 8;
	//Island size info
	float recWidth = 100.0;
	float recHeight = 100.0;
	//Island position info
	float initialPosX = 100.0, a = 100.0;
	float initalPosY = 100.0;
	//Cat size info
	float xCat[4];
	float yCat[4];
	//Cat size info
	float catWidth = 100.0;
	float catHeight = 100.0;
	//Position of Bridge info
	float xPosBr = 900;
	float yPosBr = 500;
	//Degree of movement of Cats and mouse 
	float move = 100.0;
	//Mouse size info
	float mouseRad = 50.0;
	//Mouse Position info
	float xPosMs = 100.0, yPosMs = 100.0;
	//Used to end game for either Win or Lose
	bool gameStatus = false;
	bool gameWin = false;
	int status = 0;
	//Moves of Mouse Counter
	int movescounter = 0;

	//Initialize Island, Bridge, Cats, Mouse
	RectangleShape rec[8][8], cat[4], bridge;
	CircleShape mouse;
	Island(rec);
	Bridge(bridge);
	Cats(cat, xCat, yCat);
	Far(mouse);

	//Initializing the Window of Game Mode
	RenderWindow window(VideoMode(1000, 1000), "The Chase!!");

	//Initializing Time of 600ms between every movement of Cats and Mouse
	Clock clock, clock1;
	Time range = milliseconds(600);
	Time range1 = milliseconds(600);
	Time t = clock.restart();
	Time t1 = clock1.restart();

	//Initialize Counter
	Text counter;
	Font textFont;
	textFont.loadFromFile("COOPBL.TTF");
	counter.setFont(textFont);
	counter.setString("Moves: ");
	counter.setPosition(50, 50);
	counter.setCharacterSize(24);
	counter.setColor(sf::Color::Red);

	//While window is open all these will happen in a loop
	while (window.isOpen())
	{
		//If any event occurs such as key pressed this happens
		Event event;
		while (window.pollEvent(event)) {

			//If closed key is pressed, window closes
			if (event.type == Event::Closed)
				window.close();

			//Movement of mouse depending on key pressed
			if (event.type == Event::KeyPressed) {
				t1 = clock1.getElapsedTime();
				if (range1.asMilliseconds() <= t1.asMilliseconds()) {
					switch (event.key.code) {
					case Keyboard::Up:
						yPosMs -= move;
						movescounter++;
						break;
					case Keyboard::Down:
						yPosMs += move;
						movescounter++;
						break;
					case Keyboard::Right:
						xPosMs += move;
						movescounter++;
						break;
					case Keyboard::Left:
						xPosMs -= move;
						movescounter++;
						break;
					case Keyboard::Escape:
						window.close();
						break;
					}
				}
				t1 = clock1.restart();
				counter.setString("Moves:  " + to_string(movescounter));

			}
			mouse.setPosition(Vector2f(xPosMs, yPosMs));
		}

		//Movement of cats every 600ms randomly in any direction
		t = clock.getElapsedTime();
		if (range.asMilliseconds() <= t.asMilliseconds())
		{
			for (int j = 0; j < 4; j++) {
				int r = rand() % 4;
				if (xCat[j] == 100.0) {
					while (r == 3)
						r = rand() % 4;
				}
				if (xCat[j] == 700.0) {
					while (r == 1)
						r = rand() % 4;
				}
				if (yCat[j] == 100.0) {
					while (r == 0)
						r = rand() % 4;
				}
				if (yCat[j] == 700) {
					while (r == 2)
						r = rand() % 4;
				}

				switch (r) {
				case 0:
					yCat[j] -= move;
					break;
				case 1:
					xCat[j] += move;
					break;
				case 2:
					yCat[j] += move;
					break;
				case 3:
					xCat[j] -= move;
					break;
				}
				bool work = false;
				if ((xCat[j] >= 100.0) && (xCat[j] <= 800.0) && (yCat[j] >= 100.0) && (yCat[j] <= 800.0))
					work = true;
				if (work)
					cat[j].setPosition(Vector2f(xCat[j], yCat[j]));
			}
			t = clock.restart();
		}


		//Draw Screen
		//window is given blue color
		window.clear(Color::Blue);
		//Text to player to press on Keyboard every 600ms
		Text ableMove;
		Font o;
		o.loadFromFile("COOPBL.TTF");
		ableMove.setFont(o);
		ableMove.setColor(Color::Magenta);
		ableMove.setPosition(180, 50);
		ableMove.setCharacterSize(30);
		ableMove.setString("Press on Keyboard every 0.6 second to move mouse");
		window.draw(ableMove);
		//Draw counter
		window.draw(counter);
		//island is drawn
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++) {
				window.draw(rec[i][j]);
			}
		}
		//bridge is drawn
		window.draw(bridge);
		//cats are drawn
		for (int j = 0; j < 4; j++) {
			window.draw(cat[j]);
		}
		//mouse is drawn
		window.draw(mouse);
		//If mouse touches bridge
		if (((xPosMs + 38.0) >= xPosBr) && ((yPosMs + 20.0) >= yPosBr) && (yPosMs <= (yPosBr + 60))) {
			//Text is drawn
			gameStatus = true;
			gameWin = true;
		}
		//If mouse touches a cat 
		for (int k = 0; k < 4; k++) {
			if ((xPosMs == xCat[k]) && (yPosMs == yCat[k])) {
				gameStatus = true;
				status = 2;
			}
		}
		//If mouse moves out of Grid
		if ((xPosMs < 100) || (xPosMs > 800) || (yPosMs < 100) || (yPosMs > 800)) {
			gameStatus = true;
			status = 3;
		}
		//If 100 turns pass
		if (movescounter >= 100) {
			gameStatus = true;
			status = 4;
		}
		if (gameStatus) {
			window.clear(Color::Red);
			Text wrd, wrd1;
			Font o;
			o.loadFromFile("COOPBL.TTF");
			wrd.setFont(o);
			wrd1.setFont(o);
			wrd1.setColor(Color::Green);
			wrd.setColor(Color::Yellow);
			wrd.setPosition(300, 340);
			wrd1.setPosition(300, 500);
			wrd.setCharacterSize(60);
			wrd1.setCharacterSize(40);
			if (gameWin) {
				wrd.setString("You Won!!");
				wrd1.setString("You have escaped the Bridge");
			}
			else {
				wrd.setString("You Lost!!");
				switch (status) {
				case 2:
					wrd1.setString("You have been eaten by a Cat");
					break;
				case 3:
					wrd1.setString("You Drowned");
					break;
				case 4:
					wrd1.setString("You Died of Starvation");
					break;
				}
			}
			window.draw(wrd1);
			window.draw(wrd);
		}
		//window is displayed
		window.display();
	}

	return 0;
}

