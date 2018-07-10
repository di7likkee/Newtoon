#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "map.h"
#include <sstream>

using namespace sf;
using namespace std;

float offsetX = 0, offsetY = 0;
String TileMap[HEIGHT_MAP];

class PLAYER {
public:

	short countApple = 0;
	float dx, dy;
	FloatRect coordinate, firstCoordinateTp, secondCoordinateTp;
	bool onGround, check;
	Sprite spritePlayer;
	float currentFrame;

	void init(Texture &image, float time) {
		spritePlayer.setTexture(image);
		//coordinate = FloatRect(70 * 32, 2 * 32, 60, 97);
		coordinate = FloatRect(3 * 32, 12 * 32, 60, 97);

		dx = dy = 0.1;
		currentFrame = 0;
		offsetX = 0;
	}

	PLAYER(Texture &image, float time) {
		init(image, time);
	}
	

};

short startMenu(RenderWindow &window);
short startGame(RenderWindow &window, short countAllApple);
void update(PLAYER &player, float time);
void collision(PLAYER &player, bool variables);
short showEndGameMenu(RenderWindow &window, short countAllApple);


void update(PLAYER &player, float time) {

	player.coordinate.left += player.dx * time; // Перемещение по x
	collision(player, true); // x

	if (!player.onGround) {
		player.dy = player.dy + 0.0005*time; // Падение с ускорением
	}
	player.coordinate.top += player.dy*time;
	player.onGround = false;
	collision(player, false); // y

	player.currentFrame += 0.005*time;
	if (player.currentFrame > 6) player.currentFrame -= 6;

	if (player.dx == 0) {
		player.spritePlayer.setTextureRect(IntRect(30, 19, 60, 97));
	}
	if (player.dx > 0) {
		player.spritePlayer.setTextureRect(IntRect(180 + (150 * int(player.currentFrame)), 19, 60, 97));
	}
	if (player.dx < 0) {
		player.spritePlayer.setTextureRect(IntRect(180 + (150 * int(player.currentFrame)) + 60, 19, -60, 97));
	}

	player.spritePlayer.setPosition(player.coordinate.left - offsetX, player.coordinate.top - offsetY);

	player.dx = 0;
}

void collision(PLAYER &player, bool variables) {
	Clock clock;
	for (int i(player.coordinate.top / 32); i < (player.coordinate.top + player.coordinate.height) / 32; i++) {
		for (int j(player.coordinate.left / 32); j < (player.coordinate.left + player.coordinate.width) / 32; j++) {
			if ((TileMap[i][j] == '0') || (TileMap[i][j] == 'b') || (TileMap[i][j] == 'p') || (TileMap[i][j] == 'd')) {
				if ((player.dx > 0) && (variables == true)) {
					player.coordinate.left = j * 32 - player.coordinate.width;
				}
				if ((player.dx < 0) && (variables == true)) {
					player.coordinate.left = j * 32 + 32;
				}
				if ((player.dy > 0) && (variables == false)) {
					player.coordinate.top = i * 32 - player.coordinate.height;
					player.dy = 0;
					player.onGround = true;
				}
				if ((player.dy < 0) && (variables == false)) {
					player.coordinate.top = i * 32 + 32;
					player.dy = 0;
				}
			}
			if (TileMap[i][j] == '1') {
				player.coordinate = player.firstCoordinateTp;
				update(player, 0);

			}
			if (TileMap[i][j] == '3') {
				player.coordinate = player.secondCoordinateTp;
				update(player, 0);
			}
			if (TileMap[i][j] == 'a') {
				TileMap[i][j] = ' ';
				player.countApple++;
			}

		}
	}
}

short startMenu(RenderWindow &window) {
	
	short elementMenu(0);
	
	Texture tMenuBackground, tMenuStartGame, tMenuRecords, tMenuExit, tMenuImageChoice, tMenuRecordsBackground;
	tMenuBackground.loadFromFile("images/menuBackground.png");
	tMenuStartGame.loadFromFile("images/menuStartGame.png");
	tMenuImageChoice.loadFromFile("images/menuImageChoice.png");
	tMenuExit.loadFromFile("images/menuExit.png");
	tMenuRecords.loadFromFile("images/menuRecords.png");
	tMenuRecordsBackground.loadFromFile("images/menuRecordsBackground.png");

	Sprite sMenuBackground(tMenuBackground), sMenuStartGame(tMenuStartGame), sMenuRecords(tMenuRecords), sMenuExit(tMenuExit), sMenuImageChoice(tMenuImageChoice), sMenuRecordsBackground(tMenuRecordsBackground);
	sMenuBackground.setPosition(0, 0);
	sMenuStartGame.setPosition(145, 423);
	sMenuRecords.setPosition(168, 476);
	sMenuExit.setPosition(145, 530);
	sMenuRecordsBackground.setPosition(0, 0);
	
	while (window.isOpen()) {
		
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}
		window.draw(sMenuBackground);
			
		sMenuStartGame.setColor(Color(86, 59, 56));
		sMenuRecords.setColor(Color(86, 59, 56));
		sMenuExit.setColor(Color(86, 59, 56));

		elementMenu = 0;

		if (IntRect(145, 423, 143, 23).contains(Mouse::getPosition(window))) {
			sMenuStartGame.setColor(Color(164, 72, 68));
			sMenuImageChoice.setPosition(89, 405);
			window.draw(sMenuImageChoice);
			elementMenu = 1;
		}
		if (IntRect(166, 476, 96, 23).contains(Mouse::getPosition(window))) {
			sMenuRecords.setColor(Color(164, 72, 68)); 
			sMenuImageChoice.setPosition(111, 458);
			window.draw(sMenuImageChoice);
			elementMenu = 2;
		}
		if (IntRect(145, 530, 71, 18).contains(Mouse::getPosition(window))) {
			sMenuExit.setColor(Color(164, 72, 68)); 
			sMenuImageChoice.setPosition(89, 511);
			window.draw(sMenuImageChoice);
			elementMenu = 3;
		}

		if (Mouse::isButtonPressed(Mouse::Left)) {
			switch (elementMenu) {
			case 1: {
				return elementMenu;
				break;
			}
			case 2: {
				window.draw(sMenuRecordsBackground);
				window.display();
				while (!Keyboard::isKeyPressed(Keyboard::Escape));
				break;
			}
			case 3: {
				return elementMenu;
				break;
			}
			default:
				break;
			}
		}
			
		window.draw(sMenuStartGame);
		window.draw(sMenuRecords);
		window.draw(sMenuExit);

		window.display();
	}
}


short startGame(RenderWindow &window, short countAllApple) {

	View view;

	Font font;
	font.loadFromFile("adominorevobl_bold.ttf");

	Text textCountApple("", font, 24), textTimer("", font, 24);
	textCountApple.setFillColor(Color(255, 255, 255));
	textCountApple.setStyle(Text::Bold);
	textTimer.setFillColor(Color(255, 255, 255));
	textTimer.setStyle(Text::Bold);


	Texture texturePlayer, bg, tGround, tTiles, tApple, tDoorOpen, tDoorClosed, tTimer;
	texturePlayer.loadFromFile("images/newton-sheet.png");
	bg.loadFromFile("images/bg.png");
	tGround.loadFromFile("images/ground.png");
	tTiles.loadFromFile("images/tiles.png");
	tApple.loadFromFile("images/apple.png");
	tDoorClosed.loadFromFile("images/door_closed.png");
	tDoorOpen.loadFromFile("images/door_open.png");
	tTimer.loadFromFile("images/timer_32.png");

	texturePlayer.setSmooth(true);
	bg.setSmooth(true);
	tGround.setSmooth(true);
	tTiles.setSmooth(true);
	tApple.setSmooth(true);
	tDoorClosed.setSmooth(true);
	tDoorOpen.setSmooth(true);
	tTimer.setSmooth(true);

	Sprite sBg(bg), sGround(tGround), sTiles(tTiles), sApple(tApple), sDoorOpen(tDoorOpen), sDoorClosed(tDoorClosed), sTimer(tTimer);

	copy(begin(TileMapOrigin), end(TileMapOrigin), begin(TileMap)); // Копирование начальной карты

	PLAYER p(texturePlayer, 0);

	SoundBuffer buffer;
	buffer.loadFromFile("sounds/jump.ogg");
	Sound sound(buffer);


	Music music;
	music.openFromFile("sounds/Monkeys_Spinning_Monkeys.ogg");
	music.play();
	music.setLoop(true);


	Clock clock;
	float currentFrame(0); 
	int timer(20000 * 6); // 10 sec ~ 20000
	
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		time /= 500;

		if (time > 20) {
			time = 20;
		}

		timer -= time;
		if (timer < 0) {
			countAllApple = p.countApple;
			return countAllApple;
		}

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
		{
			p.dx = -0.1;

		}

		if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
		{
			p.dx = 0.1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Space)) {
			if (p.onGround) {
				p.dy = -0.4;
				p.onGround = false;
				sound.play();
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::R))
		{
			music.play();
			music.setLoop(true);
		}
		if (Keyboard::isKeyPressed(Keyboard::F))
		{
			music.stop();
		}

		if (Keyboard::isKeyPressed(Keyboard::G)) { // Перемещение в начало
			p.init(texturePlayer, time);
		}

		update(p, time);

		if ((p.coordinate.left > 400) && ((880 < 150 * 32 - p.coordinate.left))) {
			offsetX = p.coordinate.left - 400;
		}

		window.clear(Color::White);
		window.draw(sBg);

		for (int i(0); i < HEIGHT_MAP; i++) {
			for (int j(0); j < WIDTH_MAP; j++) {
				if (TileMap[i][j] == '0') {
					continue;
				}
				if (TileMap[i][j] == ' ') {
					continue;
				}
				if (TileMap[i][j] == 'b') {
					sGround.setTextureRect(IntRect(6 * 32, 2 * 32, 32, 16));
				}
				if (TileMap[i][j] == 'p') {
					sGround.setTextureRect(IntRect(160, 288, 32, 32));
				}
				if (TileMap[i][j] == '1' || TileMap[i][j] == '3') {
					sDoorOpen.setTextureRect(IntRect(0, 0, 64, 128));
					sDoorOpen.setPosition(j * 32 - offsetX, i * 32 - 32 - offsetY);
					window.draw(sDoorOpen);
				}
				if (TileMap[i][j] == '2') {
					sDoorClosed.setTextureRect(IntRect(0, 0, 64, 128));
					sDoorClosed.setPosition(j * 32 - offsetX, i * 32 - 32 - offsetY);
					p.firstCoordinateTp = FloatRect(j * 32, i * 32 - 32, 60, 97);
					window.draw(sDoorClosed);
				}
				if (TileMap[i][j] == '4') {
					sDoorClosed.setTextureRect(IntRect(0, 0, 64, 128));
					sDoorClosed.setPosition(j * 32 - offsetX, i * 32 - 32 - offsetY);
					p.secondCoordinateTp = FloatRect(j * 32 , i * 32 - 32, 60, 97);
					window.draw(sDoorClosed);

				}
				if (TileMap[i][j] == 'a') {
					sApple.setTextureRect(IntRect(0, 0, 32, 32));
					sApple.setPosition(j * 32 - offsetX, i * 32 - offsetY);
					window.draw(sApple);
				}
				if (TileMap[i][j] == 'd') {
					sGround.setTextureRect(IntRect(1 * 32, 10 * 32, 32, 16));
				}

				if (!((TileMap[i][j] == '1') || (TileMap[i][j] == '2') || (TileMap[i][j] == 'a') || (TileMap[i][j] == '3') || (TileMap[i][j] == '4'))) {
					sGround.setPosition(j * 32 - offsetX, i * 32 - offsetY);
					window.draw(sGround);
				}
			}
		}
		
		ostringstream countAppleString, timerString;
		
		// Отображение кол-ва яблок
		sApple.setTextureRect(IntRect(0, 0, 32, 32));
		sApple.setPosition(view.getCenter().x - 446, view.getCenter().y - 473);
		window.draw(sApple);

		countAppleString << p.countApple;
		textCountApple.setString(": " + countAppleString.str());
		textCountApple.setPosition(view.getCenter().x - 410, view.getCenter().y - 471);
		window.draw(textCountApple);

		//Таймер
		sTimer.setTextureRect(IntRect(0, 0, 35, 35));
		sTimer.setPosition(view.getCenter().x + 50, view.getCenter().y - 473);
		window.draw(sTimer);

		timerString << (timer / 2000);
		textTimer.setString(": " + timerString.str());
		textTimer.setPosition(view.getCenter().x + 87, view.getCenter().y - 470);
		window.draw(textTimer);

		window.draw(p.spritePlayer);
		window.display();
	}

}

short showEndGameMenu(RenderWindow &window, short countAllApple) {
	View view;

	Font font;
	font.loadFromFile("PT_SANS-WEB-BOLDITALIC.TTF");

	wstring strRepeatGame = L"Начать заново", strBackToMainMenu = L"Выйти в главное меню";

	Text textRepeatGame(strRepeatGame, font, 36), textBackToMainMenu(strBackToMainMenu, font, 36), textCountAllApple("", font, 42);
	textRepeatGame.setFillColor(Color(86, 59, 56));
	textBackToMainMenu.setFillColor(Color(86, 59, 56));
	textCountAllApple.setFillColor(Color(86, 59, 56));

	Texture tMenuBackground;
	tMenuBackground.loadFromFile("images/menuRepeatBackground.png");

	Sprite sMenuBackground(tMenuBackground);
	sMenuBackground.setPosition(0, 0);

	short elementMenu(0);

	while (window.isOpen()) {

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}
		window.draw(sMenuBackground);

		ostringstream countAllAppleString;

		countAllAppleString << countAllApple;
		textCountAllApple.setString(countAllAppleString.str());
		
		if (countAllApple < 10 && countAllApple > -10) {
			textCountAllApple.setPosition(view.getCenter().x + 130, view.getCenter().y - 350);
		}
		if (countAllApple > 9 || countAllApple < -9) {
			textCountAllApple.setPosition(view.getCenter().x + 120, view.getCenter().y - 350);
		}
		textCountAllApple.setStyle(Text::Bold);
		window.draw(textCountAllApple);

		textRepeatGame.setPosition(view.getCenter().x + 25, view.getCenter().y - 150);
		window.draw(textRepeatGame);
		textBackToMainMenu.setPosition(view.getCenter().x - 40, view.getCenter().y - 100);
		window.draw(textBackToMainMenu);

		textRepeatGame.setStyle(Text::Regular);
		textBackToMainMenu.setStyle(Text::Regular);


		elementMenu = 0;

		if (IntRect(523, 355, 231, 30).contains(Mouse::getPosition(window))) {
			textRepeatGame.setStyle(Text::Underlined);
			elementMenu = 1;
		}
		if (IntRect(460, 410, 360, 26).contains(Mouse::getPosition(window))) {
			textBackToMainMenu.setStyle(Text::Underlined);
			elementMenu = 2;
		}

		if (Mouse::isButtonPressed(Mouse::Left)) {
			return elementMenu;
		}
			window.display();
	}
}


int main(){
	RenderWindow window(VideoMode(1280, 720), "Newton [1.0]");
	window.setFramerateLimit(100);
	short elementMenu(2);
	short countAllApple(0);
	
	while (elementMenu != 3) {
		if (elementMenu == 2) { 
			elementMenu = startMenu(window); 
		}
		
		if (elementMenu == 1) {
			countAllApple = startGame(window, countAllApple);

			elementMenu = showEndGameMenu(window, countAllApple);

		}
	}
	window.close();

}