#define _CRT_SECURE_NO_WARNINGS
#include <GL/glut.h>
#include <SOIL2.h>
#include <FMOD/fmod.hpp>
#include <time.h>
#include <string>
#include "Sprite.h"
#include "Input.h"

#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

GLfloat screenWidth;
GLfloat screenHeight;

float deltaTime = 0.0;
int previousTime;
int refresh = 30;
int particleTime = 500;

int boostTime = 5000;
bool boostReady;
float boostClock;
float boostThreshold;
float boostTrack;

float uiTimer;
const float UI_THRESHOLD = 0.01f;
float splashDisplayTimer;
float splashDisplayThreshold;
float completeDisplayTimer;
float completeDisplayThreshold;

int orangesCollected;
int orangesCollectedTotal;
int orangesCollectedReal;
int orangesCollectedThresholdOne; 
int orangesCollectedThresholdTwo;
int bananasCollected;
int shoesCollected;
float levelTimer;

float movement;

std::string name;
std::string nameFinal;

enum GameState
{
	GS_Splash,
	GS_Loading,
	GS_Menu,
	GS_HighScore,
	GS_Credits,
	GS_Identification,
	GS_Level,
	GS_LevelTwo,
	GS_BetweenLevels,
	GS_Paused,
	GS_GameOver,
	GS_Finished
};

GameState current_GameState;
Input* inputManager;

Sprite* backgroundScreen;
Sprite* splashScreen;
Sprite* menuScreen;
Sprite* highScoreScreen;
Sprite* creditsScreen;
Sprite* gameOverScreen;
Sprite* levelCompleteScreen;
Sprite* identificationScreen;
Sprite* finishScreen;

Sprite* playButton;
Sprite* highScoreButton;
Sprite* creditsButton;
Sprite* exitButton;
Sprite* backButton;
Sprite* continueButton;
Sprite* pauseButton;
Sprite* resumeButton;
Sprite* menuButton;

Sprite* playerRightIdle;
Sprite* playerRightRun;
Sprite* playerLeftIdle;
Sprite* playerLeftRun;
Sprite* player;

Sprite* orange;
Sprite* banana;
Sprite* shoe;

Sprite* effectHearts;
Sprite* effectFlames;
Sprite* particlesOrange;
Sprite* particlesBanana;

Sprite* orangeIcon;
Sprite* orangeIconTwo;
Sprite* clockIcon;
Sprite* playerIcon;
Sprite* shoeIcon;
Sprite* orangeFinishIcon;
Sprite* bananaFinishIcon;
Sprite* shoeFinishIcon;

FMOD::System* audioManager;
FMOD::Channel* channelRunning;
FMOD::Sound* soundAmbience;
FMOD::Sound* soundRunning;
FMOD::Sound* soundPickup;
FMOD::Sound* soundButton;
FMOD::Sound* soundVictory;
FMOD::Sound* soundDefeat;
FMOD::Sound* soundFruitCrack;

void LoadSplash()
{
	current_GameState = GameState::GS_Splash;

	splashScreen = new Sprite(1);
	splashScreen->SetFrameSize(1200.0f, 600.0f);
	splashScreen->SetNumberOfFrames(1);
	splashScreen->AddTexture("Assets/splash.jpg", false);
	splashScreen->IsActive(true);
	splashScreen->IsVisible(true);

}

const bool LoadTextures() 
{
	// main menu
	menuScreen = new Sprite(1);
	menuScreen->SetFrameSize(1200.0f, 600.0f);
	menuScreen->SetNumberOfFrames(1);
	menuScreen->AddTexture("Assets/mainmenu.png", false);
	menuScreen->IsActive(true);
	menuScreen->IsVisible(true);

	// background
	backgroundScreen = new Sprite(1);
	backgroundScreen->SetFrameSize(1200.0f, 600.0f); // 1877.0f
	backgroundScreen->SetNumberOfFrames(1);
	backgroundScreen->AddTexture("Assets/background.png", false);
	backgroundScreen->IsActive(true);
	backgroundScreen->IsVisible(true);

	// high score
	highScoreScreen = new Sprite(1);
	highScoreScreen->SetFrameSize(1200.0f, 600.0f);
	highScoreScreen->SetNumberOfFrames(1);
	highScoreScreen->AddTexture("Assets/highscore.png", false);
	highScoreScreen->IsActive(true);
	highScoreScreen->IsVisible(true);

	// credits
	creditsScreen = new Sprite(1);
	creditsScreen->SetFrameSize(1200.0f, 600.0f);
	creditsScreen->SetNumberOfFrames(1);
	creditsScreen->AddTexture("Assets/credits.png", false);
	creditsScreen->IsActive(true);
	creditsScreen->IsVisible(true);

	// game over
	gameOverScreen = new Sprite(1);
	gameOverScreen->SetFrameSize(1200.0f, 600.0f);
	gameOverScreen->SetNumberOfFrames(1);
	gameOverScreen->AddTexture("Assets/gameover.jpg", false);
	gameOverScreen->IsActive(true);
	gameOverScreen->IsVisible(true);

	// level complete
	levelCompleteScreen = new Sprite(1);
	levelCompleteScreen->SetFrameSize(1200.0f, 600.0f);
	levelCompleteScreen->SetNumberOfFrames(1);
	levelCompleteScreen->AddTexture("Assets/levelComplete.jpg", false);
	levelCompleteScreen->IsActive(true);
	levelCompleteScreen->IsVisible(true);

	// game finish
	finishScreen = new Sprite(1);
	finishScreen->SetFrameSize(1200.0f, 600.0f);
	finishScreen->SetNumberOfFrames(1);
	finishScreen->AddTexture("Assets/gameFinish.jpg", false);
	finishScreen->IsActive(true);
	finishScreen->IsVisible(true);

	// identification
	identificationScreen = new Sprite(1);
	identificationScreen->SetFrameSize(1200.0f, 600.0f);
	identificationScreen->SetNumberOfFrames(1);
	identificationScreen->AddTexture("Assets/identification.png", false);
	identificationScreen->IsActive(true);
	identificationScreen->IsVisible(true);

	// play button
	playButton = new Sprite(1);
	playButton->SetFrameSize(75.0f, 38.0f);
	playButton->SetNumberOfFrames(1);
	playButton->SetPosition(560.0f, 150.0f);
	playButton->AddTexture("Assets/Buttons/playButton.png");
	playButton->IsVisible(true);
	playButton->IsActive(false);
	inputManager->AddUiElement(playButton);

	// high score button
	highScoreButton = new Sprite(1);
	highScoreButton->SetFrameSize(75.0f, 38.0f);
	highScoreButton->SetNumberOfFrames(1);
	highScoreButton->SetPosition(560.0f, 200.0f);
	highScoreButton->AddTexture("Assets/Buttons/scoreButton.png");
	highScoreButton->IsVisible(true);
	highScoreButton->IsActive(false);
	inputManager->AddUiElement(highScoreButton);

	// credits button
	creditsButton = new Sprite(1);
	creditsButton->SetFrameSize(75.0f, 38.0f);
	creditsButton->SetNumberOfFrames(1);
	creditsButton->SetPosition(560.0f, 250.0f);
	creditsButton->AddTexture("Assets/Buttons/creditsButton.png");
	creditsButton->IsVisible(true);
	creditsButton->IsActive(false);
	inputManager->AddUiElement(creditsButton);

	// exit button
	exitButton = new Sprite(1);
	exitButton->SetFrameSize(75.0f, 38.0f);
	exitButton->SetNumberOfFrames(1);
	exitButton->SetPosition(560.0f, 300.0f);
	exitButton->AddTexture("Assets/Buttons/exitButton.png");
	exitButton->IsVisible(true);
	exitButton->IsActive(false);
	inputManager->AddUiElement(exitButton);

	// back button;
	backButton = new Sprite(1);
	backButton->SetFrameSize(75.0f, 38.0f);
	backButton->SetNumberOfFrames(1);
	backButton->SetPosition(0.0f, 560.0f);
	backButton->AddTexture("Assets/Buttons/backButton.png");
	backButton->IsVisible(true);
	backButton->IsActive(false);
	inputManager->AddUiElement(backButton);

	// continue button
	continueButton = new Sprite(1);
	continueButton->SetFrameSize(75.0f, 38.0f);
	continueButton->SetNumberOfFrames(1);
	continueButton->SetPosition(390.0f, 300.0f);
	continueButton->AddTexture("Assets/Buttons/continueButton.png");
	continueButton->IsVisible(true);
	continueButton->IsActive(false);
	inputManager->AddUiElement(continueButton);

	// pause button
	pauseButton = new Sprite(1);
	pauseButton->SetFrameSize(75.0f, 38.0f);
	pauseButton->SetNumberOfFrames(1);
	pauseButton->SetPosition(0.0f, 0.0f);
	pauseButton->AddTexture("Assets/Buttons/pauseButton.png");
	pauseButton->IsVisible(true);
	pauseButton->IsActive(true);
	inputManager->AddUiElement(pauseButton);

	// resume button
	resumeButton = new Sprite(1);
	resumeButton->SetFrameSize(75.0f, 38.0f);
	resumeButton->SetNumberOfFrames(1);
	resumeButton->SetPosition(0.0f, 0.0f);
	resumeButton->AddTexture("Assets/Buttons/resumeButton.png");
	inputManager->AddUiElement(resumeButton);

	// menu button
	menuButton = new Sprite(1);
	menuButton->SetFrameSize(75.0f, 38.0f);
	menuButton->SetNumberOfFrames(1);
	menuButton->SetPosition(560.0f, 250.0f);
	menuButton->AddTexture("Assets/Buttons/menuButton.png");
	menuButton->IsVisible(true);
	menuButton->IsActive(false);
	inputManager->AddUiElement(menuButton);

	// player
	playerRightIdle = new Sprite(1);
	playerRightIdle->SetFrameSize(125.0f, 100.0f);
	playerRightIdle->SetNumberOfFrames(4);
	playerRightIdle->SetPosition(500.0f, 430.0f);
	playerRightIdle->AddTexture("Assets/hyena_idle_right.png");
	playerRightIdle->IsCollideable(true);

	playerLeftIdle = new Sprite(1);
	playerLeftIdle->SetFrameSize(125.0f, 100.0f);
	playerLeftIdle->SetNumberOfFrames(4);
	playerLeftIdle->SetPosition(500.0f, 430.0f);
	playerLeftIdle->AddTexture("Assets/hyena_idle_left.png");
	playerLeftIdle->IsCollideable(true);

	playerRightRun = new Sprite(1);
	playerRightRun->SetFrameSize(125.0f, 100.0f);
	playerRightRun->SetNumberOfFrames(6);
	playerRightRun->SetPosition(500.0f, 430.0f);
	playerRightRun->AddTexture("Assets/hyena_right.png");
	playerRightRun->IsCollideable(true);

	playerLeftRun = new Sprite(1);
	playerLeftRun->SetFrameSize(125.0f, 100.0f);
	playerLeftRun->SetNumberOfFrames(6);
	playerLeftRun->SetPosition(500.0f, 430.0f);
	playerLeftRun->AddTexture("Assets/hyena_left.png");
	playerLeftRun->IsCollideable(true);

	Sprite::Rect playerCollision;
	playerCollision.left = 25.0f;
	playerCollision.right = -25.0f;
	playerCollision.top = 25.0f;
	playerCollision.bottom = -25.0f;
	playerRightIdle->SetCollisionRectOffset(playerCollision);
	playerLeftIdle->SetCollisionRectOffset(playerCollision);
	playerRightRun->SetCollisionRectOffset(playerCollision);
	playerLeftRun->SetCollisionRectOffset(playerCollision);

	playerRightIdle->IsActive(true);
	playerRightIdle->IsVisible(true);

	player = playerRightIdle;
	player->IsActive(true);
	player->IsVisible(true);

	// orange pickup
	orange = new Sprite(1);
	orange->SetFrameSize(50.0f, 50.0f);
	orange->SetNumberOfFrames(1);
	orange->AddTexture("Assets/orange.png");
	orange->IsVisible(false);
	orange->IsActive(false);
	orange->IsCollideable(true);

	Sprite::Rect orangeCollision;
	orangeCollision.left = 25.0f;
	orangeCollision.right = -25.0f;
	orangeCollision.top = 25.0f;
	orangeCollision.bottom = -25.0f;
	orange->SetCollisionRectOffset(orangeCollision);

	// banana pickup
	banana = new Sprite(1);
	banana->SetFrameSize(50.0f, 50.0f);
	banana->SetNumberOfFrames(1);
	banana->AddTexture("Assets/banana.png");
	banana->IsVisible(false);
	banana->IsActive(false);
	banana->IsCollideable(true);

	Sprite::Rect bananaCollision;
	bananaCollision.left = 25.0f;
	bananaCollision.right = -25.0f;
	bananaCollision.top = 25.0f;
	bananaCollision.bottom = -25.0f;
	banana->SetCollisionRectOffset(bananaCollision);

	// shoe pickup
	shoe = new Sprite(1);
	shoe->SetFrameSize(50.0f, 40.0f);
	shoe->SetNumberOfFrames(1);
	shoe->AddTexture("Assets/sneakers.png");
	shoe->IsVisible(false);
	shoe->IsActive(false);
	shoe->IsCollideable(true);

	Sprite::Rect shoeCollision;
	shoeCollision.left = 25.0f;
	shoeCollision.right = -25.0f;
	shoeCollision.top = 25.0f;
	shoeCollision.bottom = -25.0f;
	shoe->SetCollisionRectOffset(shoeCollision);

	// hearts effect
	effectHearts = new Sprite(1);
	effectHearts->SetFrameSize(75.0f, 75.0f);
	effectHearts->SetNumberOfFrames(4);
	effectHearts->AddTexture("Assets/hearts.png");
	effectHearts->IsVisible(false);
	effectHearts->IsActive(false);

	// flames effect
	effectFlames = new Sprite(1);
	effectFlames->SetFrameSize(75.0f, 75.0f);
	effectFlames->SetNumberOfFrames(4);
	effectFlames->AddTexture("Assets/flames.png");
	effectFlames->IsVisible(false);
	effectFlames->IsActive(false);

	// orange particles
	particlesOrange = new Sprite(1);
	particlesOrange->SetFrameSize(75.0f, 75.0f);
	particlesOrange->SetNumberOfFrames(4);
	particlesOrange->AddTexture("Assets/particles_orange.png");
	particlesOrange->IsVisible(false);
	particlesOrange->IsActive(false);

	// banana particles
	particlesBanana = new Sprite(1);
	particlesBanana->SetFrameSize(75.0f, 75.0f);
	particlesBanana->SetNumberOfFrames(4);
	particlesBanana->AddTexture("Assets/particles_banana.png");
	particlesBanana->IsVisible(false);
	particlesBanana->IsActive(false);

	// pickup icon
	orangeIcon = new Sprite(1);
	orangeIcon->SetFrameSize(50.0f, 50.0f);
	orangeIcon->SetNumberOfFrames(1);
	orangeIcon->SetPosition(1100.0f, 0.0f);
	orangeIcon->AddTexture("Assets/orangeIcon.png");
	orangeIcon->IsVisible(true);
	orangeIcon->IsActive(true);

	// clock icon
	clockIcon = new Sprite(1);
	clockIcon->SetFrameSize(25.0f, 25.0f);
	clockIcon->SetNumberOfFrames(1);
	clockIcon->SetPosition(1113.0f, 50.0f);
	clockIcon->AddTexture("Assets/clock.png");
	clockIcon->IsVisible(true);
	clockIcon->IsActive(true);

	// shoe icon
	shoeIcon = new Sprite(1);
	shoeIcon->SetFrameSize(25.0f, 25.0f);
	shoeIcon->SetNumberOfFrames(1);
	shoeIcon->SetPosition(1118.0f, 80.0f);
	shoeIcon->AddTexture("Assets/sneakers.png");
	shoeIcon->IsVisible(false);
	shoeIcon->IsActive(false);

	// hyena icon for finish screen
	playerIcon = new Sprite(1);
	playerIcon->SetFrameSize(125.0f, 100.0f);
	playerIcon->SetNumberOfFrames(1);
	playerIcon->SetPosition(900.0f, 70.0f);
	playerIcon->AddTexture("Assets/hyenaIcon.png");
	playerIcon->IsVisible(true);
	playerIcon->IsActive(true);

	// pickup icon for finish screen
	orangeIconTwo = new Sprite(1);
	orangeIconTwo->SetFrameSize(50.0f, 50.0f);
	orangeIconTwo->SetNumberOfFrames(1);
	orangeIconTwo->SetPosition(950.0f, 200.0f);
	orangeIconTwo->AddTexture("Assets/orangeIcon.png");
	orangeIconTwo->IsVisible(true);
	orangeIconTwo->IsActive(true);

	// orange icon for finish screen
	orangeFinishIcon = new Sprite(1);
	orangeFinishIcon->SetFrameSize(50.0f, 50.0f);
	orangeFinishIcon->SetNumberOfFrames(1);
	orangeFinishIcon->SetPosition(950.0f, 300.0f);
	orangeFinishIcon->AddTexture("Assets/orange.png");
	orangeFinishIcon->IsVisible(true);
	orangeFinishIcon->IsActive(true);

	// banana icon for finish screen
	bananaFinishIcon = new Sprite(1);
	bananaFinishIcon->SetFrameSize(50.0f, 50.0f);
	bananaFinishIcon->SetNumberOfFrames(1);
	bananaFinishIcon->SetPosition(950.0f, 400.0f);
	bananaFinishIcon->AddTexture("Assets/banana.png");
	bananaFinishIcon->IsVisible(true);
	bananaFinishIcon->IsActive(true);

	// shoe icon for finish screen
	shoeFinishIcon = new Sprite(1);
	shoeFinishIcon->SetFrameSize(50.0f, 50.0f);
	shoeFinishIcon->SetNumberOfFrames(1);
	shoeFinishIcon->SetPosition(950.0f, 500.0f);
	shoeFinishIcon->AddTexture("Assets/sneakers.png");
	shoeFinishIcon->IsVisible(true);
	shoeFinishIcon->IsActive(true);

	return true;
}

bool InitFMOD()
{
	FMOD_RESULT result;
	result = FMOD::System_Create(&audioManager);
	if (result != FMOD_OK)
		return false;

	result = audioManager->init(50, FMOD_INIT_NORMAL, NULL);
	if (result != FMOD_OK)
		return false;

	return true;
}

const bool LoadAudio()
{
	FMOD_RESULT result;
	result = audioManager->createSound("Assets/Audio/pickup.mp3", FMOD_DEFAULT, 0, &soundPickup);
	result = audioManager->createSound("Assets/Audio/fruit_crack.wav", FMOD_DEFAULT, 0, &soundFruitCrack);
	result = audioManager->createSound("Assets/Audio/button.wav", FMOD_DEFAULT, 0, &soundButton);
	result = audioManager->createSound("Assets/Audio/victory.wav", FMOD_DEFAULT, 0, &soundVictory);
	result = audioManager->createSound("Assets/Audio/defeat.wav", FMOD_DEFAULT, 0, &soundDefeat);
	result = audioManager->createSound("Assets/Audio/running.wav", FMOD_LOOP_NORMAL | FMOD_2D, 0, &soundRunning);
	result = audioManager->playSound(soundRunning, 0, true, &channelRunning);

	result = audioManager->createSound("Assets/Audio/ambience.mp3", FMOD_LOOP_NORMAL | FMOD_2D, 0, &soundAmbience);
	FMOD::Channel* channel;
	result = audioManager->playSound(soundAmbience, 0, false, &channel);
	channel->setVolume(0.3);

	return true;
}

void DrawBitmapText(const char* string, float x, float y, const float r, const float g, const float b)  // BItmap Font
{
	glDisable(GL_TEXTURE_2D);
	glColor3f(r, g, b);
	glLineWidth(4.0);
	const char* c;
	glRasterPos3f(x, y, 0.0);

	for (c = string; *c != '\0'; c++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}

	glColor3f(1.0f, 1.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
}

void DrawHighScore()
{
	float startX = 520.0f;
	float startY = 220.0f;
	float spaceY = -30.0f;

	string s;
	char* c;
	ifstream hsfile("Assets/highscore.txt");

	if (hsfile.is_open()) 
	{
		while (getline(hsfile, s)) 
		{
			c = &s[0];
			spaceY += 30.0f;
			DrawBitmapText(c, startX, startY + spaceY, 1.0f, 1.0f, 0.0f);
		}
	}
	hsfile.close();
}

void ChangeHighScore()
{
	string helpOne, helpTwo, helpThree, helpFour, helpFive;
	string nickOne, nickTwo, nickThree, nickFour, nickFive;
	string nickOnePts, nickTwoPts, nickThreePts, nickFourPts, nickFivePts;
	int onePts, twoPts, threePts, fourPts, fivePts;

	ifstream hsfile("Assets/highscore.txt");
	if (hsfile.is_open())
	{
		getline(hsfile, helpOne);
		getline(hsfile, helpTwo);
		getline(hsfile, helpThree);
		getline(hsfile, helpFour);
		getline(hsfile, helpFive);
	}
	hsfile.close();

	std::stringstream ss(helpOne);
	ss >> nickOne >> nickOnePts;
	onePts = stoi(nickOnePts);

	std::stringstream ssTwo(helpTwo);
	ssTwo >> nickTwo >> nickTwoPts;
	twoPts = stoi(nickTwoPts);

	std::stringstream ssThree(helpThree);
	ssThree >> nickThree >> nickThreePts;
	threePts = stoi(nickThreePts);

	std::stringstream ssFour(helpFour);
	ssFour >> nickFour >> nickFourPts;
	fourPts = stoi(nickFourPts);

	std::stringstream ssFive(helpFive);
	ssFive >> nickFive >> nickFivePts;
	fivePts = stoi(nickFivePts);

	ofstream scoreFile("Assets/highscore.txt");
	string playerPoints = to_string(orangesCollectedTotal);

	if (orangesCollectedTotal > fivePts)
	{
		if (scoreFile.is_open())
		{
			if (orangesCollectedTotal > onePts)
			{
				scoreFile << nameFinal << " " << playerPoints << endl;
				scoreFile << nickOne << " " << nickOnePts << endl;
				scoreFile << nickTwo << " " << nickTwoPts << endl;
				scoreFile << nickThree << " " << nickThreePts << endl;
				scoreFile << nickFour << " " << nickFourPts << endl;
			}
			else if (orangesCollectedTotal > twoPts)
			{
				scoreFile << nickOne << " " << nickOnePts << endl;
				scoreFile << nameFinal << " " << playerPoints << endl;
				scoreFile << nickTwo << " " << nickTwoPts << endl;
				scoreFile << nickThree << " " << nickThreePts << endl;
				scoreFile << nickFour << " " << nickFourPts << endl;
			}
			else if (orangesCollectedTotal > threePts)
			{
				scoreFile << nickOne << " " << nickOnePts << endl;
				scoreFile << nickTwo << " " << nickTwoPts << endl;
				scoreFile << nameFinal << " " << playerPoints << endl;
				scoreFile << nickThree << " " << nickThreePts << endl;
				scoreFile << nickFour << " " << nickFourPts << endl;
			}
			else if (orangesCollectedTotal > fourPts)
			{
				scoreFile << nickOne << " " << nickOnePts << endl;
				scoreFile << nickTwo << " " << nickTwoPts << endl;
				scoreFile << nickThree << " " << nickThreePts << endl;
				scoreFile << nameFinal << " " << playerPoints << endl;
				scoreFile << nickFour << " " << nickFourPts << endl;
			}
			else if (orangesCollectedTotal > fivePts)
			{
				scoreFile << nickOne << " " << nickOnePts << endl;
				scoreFile << nickTwo << " " << nickTwoPts << endl;
				scoreFile << nickThree << " " << nickThreePts << endl;
				scoreFile << nickFour << " " << nickFourPts << endl;
				scoreFile << nameFinal << " " << playerPoints << endl;
			}
		}
		scoreFile.close();
	}
	// bugfix 09/12/2023
	else 
	{
		if (scoreFile.is_open()) 
		{
			scoreFile << nickOne << " " << nickOnePts << endl;
			scoreFile << nickTwo << " " << nickTwoPts << endl;
			scoreFile << nickThree << " " << nickThreePts << endl;
			scoreFile << nickFour << " " << nickFourPts << endl;
			scoreFile << nickFive << " " << nickFivePts << endl;
		}
		scoreFile.close();
	}
	
}

void CheckHorizontalBoundaries(Sprite* p_sprite)
{
	Sprite::Rect check = p_sprite->GetCollisionRect();
	float offset;
	float x;
	float y;
	if (check.left < 0.0f)
	{
		p_sprite->SetVelocity(0.0f);
		offset = check.left;
		x = p_sprite->GetPosition().x - offset;
		y = p_sprite->GetPosition().y;
		p_sprite->SetPosition(x, y);
	}
	else if (check.right > screenWidth)
	{
		p_sprite->SetVelocity(0.0f);
		offset = screenWidth - check.right;
		x = p_sprite->GetPosition().x + offset;
		y = p_sprite->GetPosition().y;
		p_sprite->SetPosition(x, y);
	}
}

void particleTimer(int value)
{
	effectHearts->IsVisible(false);
	effectHearts->IsActive(false);

	particlesOrange->IsVisible(false);
	particlesOrange->IsActive(false);

	particlesBanana->IsVisible(false);
	particlesBanana->IsActive(false);
}

void boostTimer(int value)
{
	if (current_GameState == GameState::GS_Level)
	{
		movement = 250;
	}
	else if (current_GameState == GameState::GS_LevelTwo)
	{
		movement = 150;
	}

	effectFlames->IsVisible(false);
	effectFlames->IsActive(false);
	shoeIcon->IsVisible(false);
	shoeIcon->IsActive(false);

	boostReady = true;
	boostClock = 0.0f;
}


void CheckCollisions()
{
	// orange
	if (player->IntersectsRect(orange))
	{
		FMOD::Channel* channel;
		audioManager->playSound(soundPickup, 0, false, &channel);

		orange->IsVisible(false);
		orange->IsActive(false);

		orangesCollected += 1;
		orangesCollectedReal += 1;

		effectHearts->SetPosition(orange->GetPosition().x, orange->GetPosition().y);
		effectHearts->IsVisible(true);
		effectHearts->IsActive(true);
		glutTimerFunc(particleTime, particleTimer, 0);
	}

	// banana
	if (player->IntersectsRect(banana))
	{
		FMOD::Channel* channel;
		audioManager->playSound(soundPickup, 0, false, &channel);

		banana->IsVisible(false);
		banana->IsActive(false);

		orangesCollected += 2;
		bananasCollected += 1;

		effectHearts->SetPosition(banana->GetPosition().x, banana->GetPosition().y);
		effectHearts->IsVisible(true);
		effectHearts->IsActive(true);
		glutTimerFunc(particleTime, particleTimer, 0);
	}

	// shoe
	if (player->IntersectsRect(shoe))
	{
		FMOD::Channel* channel;

		shoe->IsVisible(false);
		shoe->IsActive(false);

		effectFlames->IsVisible(true);
		effectFlames->IsActive(true);
		shoeIcon->IsVisible(true);
		shoeIcon->IsActive(true);

		shoesCollected += 1;

		if (current_GameState == GameState::GS_Level)
		{
			movement = 350;
		}
		else if (current_GameState == GameState::GS_LevelTwo)
		{
			movement = 250;
		}

		boostTrack = 5.0f;
		glutTimerFunc(boostTime, boostTimer, 0);
	}
}

void PickupControl(float p)
{
	// orange
	if (orange->GetPosition().y > 480) // 600
	{
		orange->IsVisible(false);

		particlesOrange->SetPosition(orange->GetPosition().x, orange->GetPosition().y);
		particlesOrange->IsVisible(true);
		particlesOrange->IsActive(true);
		glutTimerFunc(particleTime, particleTimer, 0);

		FMOD::Channel* channel;
		audioManager->playSound(soundFruitCrack, 0, false, &channel);
	}

	if (orange->IsVisible() == false)
	{
		float marginX = orange->GetSize().width;
		float spawnX = (rand() % (int)(screenWidth - (marginX * 2))) + marginX;
		orange->SetPosition(spawnX, 0);
		orange->IsVisible(true);
		orange->IsActive(true);
	}
	else
	{
		float x, y, fall;
		fall = 5.0f; // 3.0 
		x = orange->GetPosition().x;
		y = orange->GetPosition().y + fall;
		orange->SetPosition(x, y);
	}

	// banana
	if (banana->GetPosition().y > 480) // 600
	{
		banana->IsVisible(false);

		particlesBanana->SetPosition(banana->GetPosition().x, banana->GetPosition().y);
		particlesBanana->IsVisible(true);
		particlesBanana->IsActive(true);
		glutTimerFunc(particleTime, particleTimer, 0);

		FMOD::Channel* channel;
		audioManager->playSound(soundFruitCrack, 0, false, &channel);
	}

	if (banana->IsVisible() == false)
	{
		float marginX = banana->GetSize().width;
		float spawnX = (rand() % (int)(screenWidth - (marginX * 2))) + marginX;
		banana->SetPosition(spawnX, 0);
		banana->IsVisible(true);
		banana->IsActive(true);
	}
	else
	{
		float x, y, fall;
		fall = 8.0f; // 3.0 
		x = banana->GetPosition().x;
		y = banana->GetPosition().y + fall;
		banana->SetPosition(x, y);
	}

	// shoe
	if (boostReady && boostClock > boostThreshold)
	{
		float marginX = shoe->GetSize().width;
		float spawnX = (rand() % (int)(screenWidth - (marginX * 2))) + marginX;
		shoe->SetPosition(spawnX, 480);
		shoe->IsVisible(true);
		shoe->IsActive(true);

		boostReady = false;
	}
}

void NextLevel()
{
	if (orangesCollected < orangesCollectedThresholdOne)
	{
		FMOD::Channel* channel;
		audioManager->playSound(soundDefeat, 0, false, &channel);
		channelRunning->setPaused(true);

		current_GameState = GameState::GS_GameOver;
	}
	else
	{
		channelRunning->setPaused(true);

		current_GameState = GameState::GS_BetweenLevels;
	}
}

void FinishGame()
{
	orangesCollectedTotal += orangesCollected;

	FMOD::Channel* channel;
	if (orangesCollected < orangesCollectedThresholdTwo)
	{
		audioManager->playSound(soundDefeat, 0, false, &channel);
		channelRunning->setPaused(true);

		current_GameState = GameState::GS_GameOver;
	}
	else
	{
		audioManager->playSound(soundVictory, 0, false, &channel);
		channelRunning->setPaused(true);
		ChangeHighScore();

		current_GameState = GameState::GS_Finished;
	}
}

void StartGame()
{
	FMOD_RESULT result;
	result = audioManager->release();

	LoadSplash();
	inputManager = new Input();

	srand(time(NULL));

	uiTimer = 0.0f;
	splashDisplayTimer = 0.0f;
	splashDisplayThreshold = 5.0f;
	completeDisplayTimer = 0.0f;
	completeDisplayThreshold = 5.0f;

	levelTimer = 30.0f;
	orangesCollected = 0;
	orangesCollectedTotal = 0;
	orangesCollectedThresholdOne = 6;
	orangesCollectedThresholdTwo = 10;
	bananasCollected = 0;
	orangesCollectedReal = 0;
	shoesCollected = 0;

	boostReady = true;
	boostClock = 0.0f;
	boostThreshold = 10.0f;
	boostTrack = 0.0f;

	movement = 250.0f;
	name = "";
	nameFinal = "";
}

void ProcessInput()
{
	Input::Command command = inputManager->GetCommand();
	switch (current_GameState) 
	{
	case GameState::GS_Splash:
	case GameState::GS_Loading:
	{
		return;
	}
	break;
	case GameState::GS_Menu:
	case GameState::GS_HighScore:
	case GameState::GS_Credits:
	case GameState::GS_Identification:
	case GameState::GS_Paused:
	case GameState::GS_BetweenLevels:
	case GameState::GS_GameOver:
	case GameState::GS_Finished:
	{
		command = Input::Command::CM_UI;
	}
	break;
	case GameState::GS_Level:
	case GameState::GS_LevelTwo:
	{

	}
	break;
	}

	//
	uiTimer += deltaTime;
	if (uiTimer > UI_THRESHOLD)
	{
		uiTimer = 0.0f;
		switch (command)
		{
		case Input::Command::CM_STOP:
		{
			channelRunning->setPaused(true);

			player->IsActive(true);
			player->IsVisible(true);
			player->SetVelocity(0.0f);

			if (player->GetVelocity() == 0.0f)
			{
				if (player == playerLeftRun)
				{
					playerLeftRun->IsActive(false);
					playerLeftRun->IsVisible(false);

					playerLeftIdle->SetPosition(playerLeftRun->GetPosition());
					playerLeftIdle->SetValue(playerLeftRun->GetValue());

					player = playerLeftIdle;
				}

				if (player == playerRightRun)
				{
					playerRightRun->IsActive(false);
					playerRightRun->IsVisible(false);

					playerRightIdle->SetPosition(playerRightRun->GetPosition());
					playerRightIdle->SetValue(playerRightRun->GetValue());

					player = playerRightIdle;
				}

			}
		}
		break;

		case Input::Command::CM_LEFT:
		{
			channelRunning->setPaused(false);

			if(player == playerLeftIdle)
			{
				playerLeftIdle->IsActive(false);
				playerLeftIdle->IsVisible(false);

				playerLeftRun->SetPosition(playerLeftIdle->GetPosition());
				playerLeftRun->SetValue(playerLeftIdle->GetValue());
			}

			if (player == playerRightIdle)
			{
				playerRightIdle->IsActive(false);
				playerRightIdle->IsVisible(false);

				playerLeftRun->SetPosition(playerRightIdle->GetPosition());
				playerLeftRun->SetValue(playerRightIdle->GetValue());
			}

			if (player == playerRightRun)
			{
				playerRightRun->IsActive(false);
				playerRightRun->IsVisible(false);

				playerLeftRun->SetPosition(playerRightRun->GetPosition());
				playerLeftRun->SetValue(playerRightRun->GetValue());
			}
			
			player = playerLeftRun;
			player->IsActive(true);
			player->IsVisible(true);
			player->SetVelocity(-movement); // -250
		}
		break;

		case Input::Command::CM_RIGHT:
		{
			channelRunning->setPaused(false);

			if (player == playerRightIdle)
			{
				playerRightIdle->IsActive(false);
				playerRightIdle->IsVisible(false);

				playerRightRun->SetPosition(playerRightIdle->GetPosition());
				playerRightRun->SetValue(playerRightIdle->GetValue());
			}

			if (player == playerLeftIdle)
			{
				playerLeftIdle->IsActive(false);
				playerLeftIdle->IsVisible(false);

				playerRightRun->SetPosition(playerLeftIdle->GetPosition());
				playerRightRun->SetValue(playerLeftIdle->GetValue());
			}

			if (player == playerLeftRun)
			{
				playerLeftRun->IsActive(false);
				playerLeftRun->IsVisible(false);

				playerRightRun->SetPosition(playerLeftRun->GetPosition());
				playerRightRun->SetValue(playerLeftRun->GetValue());
			}

			player = playerRightRun;
			player->IsActive(true);
			player->IsVisible(true);
			player->SetVelocity(movement); // 250
		}
		break;

		case Input::Command::CM_QUIT:
		{
			PostQuitMessage(0);
		}
		break;

		case Input::Command::CM_UI:
		{
			FMOD::Channel* channel;
			if (playButton->IsClicked())
			{
				playButton->IsClicked(false);

				playButton->IsActive(false);
				highScoreButton->IsActive(false);
				creditsButton->IsActive(false);
				exitButton->IsActive(false);

				continueButton->IsActive(true);

				name = "";
				audioManager->playSound(soundButton, 0, false, &channel);
				current_GameState = GS_Identification;
			}
			if (highScoreButton->IsClicked())
			{
				highScoreButton->IsClicked(false);

				playButton->IsActive(false);
				highScoreButton->IsActive(false);
				creditsButton->IsActive(false);
				exitButton->IsActive(false);

				backButton->IsActive(true);
				audioManager->playSound(soundButton, 0, false, &channel);
				current_GameState = GS_HighScore;
			}
			if (creditsButton->IsClicked())
			{
				creditsButton->IsClicked(false);

				playButton->IsActive(false);
				highScoreButton->IsActive(false);
				creditsButton->IsActive(false);
				exitButton->IsActive(false);

				backButton->IsActive(true);
				audioManager->playSound(soundButton, 0, false, &channel);
				current_GameState = GS_Credits;
			}
			if (exitButton->IsClicked())
			{
				exitButton->IsClicked(false);

				playButton->IsActive(false);
				highScoreButton->IsActive(false);
				creditsButton->IsActive(false);
				exitButton->IsActive(false);

				audioManager->playSound(soundButton, 0, false, &channel);
				PostQuitMessage(0);
			}
			if (backButton->IsClicked())
			{
				backButton->IsClicked(false);

				backButton->IsActive(false);
				audioManager->playSound(soundButton, 0, false, &channel);
				current_GameState = GS_Menu;
			}
			if (continueButton->IsClicked())
			{
				audioManager->playSound(soundButton, 0, false, &channel);
				if (name.length() != 0)
				{
					continueButton->IsClicked(false);

					continueButton->IsActive(false);

					nameFinal = name;
					current_GameState = GS_Level;
				}
				else
				{
					continueButton->IsClicked(false);
				}
			}
			if (pauseButton->IsClicked())
			{
				pauseButton->IsClicked(false);
				pauseButton->IsVisible(false);
				pauseButton->IsActive(false);

				resumeButton->IsVisible(true);
				resumeButton->IsActive(true);
				audioManager->playSound(soundButton, 0, false, &channel);
				current_GameState = GS_Paused;
			}
			if (resumeButton->IsClicked())
			{
				resumeButton->IsClicked(false);
				resumeButton->IsVisible(false);
				resumeButton->IsActive(false);

				pauseButton->IsVisible(true);
				pauseButton->IsActive(true);
				audioManager->playSound(soundButton, 0, false, &channel);
				current_GameState = GS_Level;
			}
			if (menuButton->IsClicked())
			{
				menuButton->IsClicked(false);
				menuButton->IsVisible(false);
				menuButton->IsActive(false);

				audioManager->playSound(soundButton, 0, false, &channel);
				StartGame();
			}
		}
		break;

		}
	}
}

void Update()
{
	switch (current_GameState)
	{
	case GameState::GS_Splash:
	case GameState::GS_Loading:
	{
		splashScreen->Update(deltaTime);
		splashDisplayTimer += deltaTime;

		if (splashDisplayTimer > splashDisplayThreshold)
			current_GameState = GameState::GS_Menu;
	}
	break;

	case GameState::GS_Menu:
	{
		menuScreen->Update(deltaTime);

		playButton->IsActive(true);
		playButton->Update(deltaTime);
		highScoreButton->IsActive(true);
		highScoreButton->Update(deltaTime);
		creditsButton->IsActive(true);
		creditsButton->Update(deltaTime);
		exitButton->IsActive(true);
		exitButton->Update(deltaTime);

		ProcessInput();
	}
	break;

	case GameState::GS_HighScore:
	{
		highScoreScreen->Update(deltaTime);

		backButton->IsActive(true);
		backButton->Update(deltaTime);

		ProcessInput();
	}
	break;

	case GameState::GS_Credits:
	{
		creditsScreen->Update(deltaTime);

		backButton->IsActive(true);
		backButton->Update(deltaTime);

		ProcessInput();
	}
	break;

	case GameState::GS_Identification:
	{
		identificationScreen->Update(deltaTime);

		continueButton->Update(deltaTime);

		ProcessInput();
	}
	break;

	case GameState::GS_Level:
	{
		ProcessInput();
		CheckHorizontalBoundaries(player);

		backgroundScreen->Update(deltaTime);

		playerRightIdle->Update(deltaTime);
		playerRightRun->Update(deltaTime);
		playerLeftIdle->Update(deltaTime);
		playerLeftRun->Update(deltaTime);

		pauseButton->Update(deltaTime);
		resumeButton->Update(deltaTime);
		orangeIcon->Update(deltaTime);
		clockIcon->Update(deltaTime);
		shoeIcon->Update(deltaTime);

		effectHearts->Update(deltaTime);
		effectFlames->Update(deltaTime);
		particlesOrange->Update(deltaTime);
		particlesBanana->Update(deltaTime);

		PickupControl(deltaTime);
		orange->Update(deltaTime);
		banana->Update(deltaTime);
		shoe->Update(deltaTime);
		CheckCollisions();

		boostClock += deltaTime;
		boostTrack -= deltaTime;

		levelTimer -= deltaTime;
		if (levelTimer <= 0)
			NextLevel();
	}
	break;

	case GameState::GS_LevelTwo:
	{
		ProcessInput();
		CheckHorizontalBoundaries(player);

		backgroundScreen->Update(deltaTime);

		playerRightIdle->Update(deltaTime);
		playerRightRun->Update(deltaTime);
		playerLeftIdle->Update(deltaTime);
		playerLeftRun->Update(deltaTime);

		pauseButton->Update(deltaTime);
		resumeButton->Update(deltaTime);
		orangeIcon->Update(deltaTime);
		clockIcon->Update(deltaTime);
		shoeIcon->Update(deltaTime);

		effectHearts->Update(deltaTime);
		effectFlames->Update(deltaTime);
		particlesOrange->Update(deltaTime);
		particlesBanana->Update(deltaTime);

		PickupControl(deltaTime);
		orange->Update(deltaTime);
		banana->Update(deltaTime);
		shoe->Update(deltaTime);
		CheckCollisions();

		boostClock += deltaTime;
		boostTrack -= deltaTime;

		levelTimer -= deltaTime;
		if (levelTimer <= 0)
			FinishGame();
	}
	break;

	case GameState::GS_Paused:
	{
		ProcessInput();
	}
	break;

	case GameState::GS_BetweenLevels:
	{
		levelCompleteScreen->Update(deltaTime);

		completeDisplayTimer += deltaTime;
		if (completeDisplayTimer > completeDisplayThreshold)
		{
			movement = 150;
			orangesCollectedTotal = orangesCollected;
			orangesCollected = 0;
			levelTimer = 41;
			orange->IsVisible(false);
			banana->IsVisible(false);
			current_GameState = GameState::GS_LevelTwo;
		}
	}
	break;

	case GameState::GS_GameOver:
	{
		gameOverScreen->Update(deltaTime);

		exitButton->IsActive(true);
		exitButton->Update(deltaTime);
		menuButton->IsActive(true);
		menuButton->Update(deltaTime);

		ProcessInput();
	}
	break;

	case GameState::GS_Finished:
	{
		finishScreen->Update(deltaTime);

		exitButton->IsActive(true);
		exitButton->Update(deltaTime);
		menuButton->IsActive(true);
		menuButton->Update(deltaTime);

		playerIcon->Update(deltaTime);
		orangeIconTwo->Update(deltaTime);
		orangeFinishIcon->Update(deltaTime);
		bananaFinishIcon->Update(deltaTime);
		shoeFinishIcon->Update(deltaTime);

		ProcessInput();
	}
	break;

	}
}

void Render() 
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	switch (current_GameState)
	{
	case GameState::GS_Splash:
	case GameState::GS_Loading:
	{
		splashScreen->Render();
	}
	break;

	case GameState::GS_Menu:
	{
		menuScreen->Render();

		playButton->Render();
		highScoreButton->Render();
		creditsButton->Render();
		exitButton->Render();
	}
	break;

	case GameState::GS_HighScore:
	{
		highScoreScreen->Render();

		backButton->Render();

		DrawHighScore();
	}
	break;

	case GameState::GS_Credits:
	{
		creditsScreen->Render();

		backButton->Render();
	}
	break;

	case GameState::GS_Identification:
	{
		identificationScreen->Render();

		continueButton->Render();

		char* temp = new char[name.length() + 1];
		strcpy(temp, name.c_str());
		DrawBitmapText(temp, 500.0f, 175.0f, 1.0f, 1.0f, 1.0f);
	}
	break;

	case GameState::GS_Level:
	case GameState::GS_LevelTwo:
	case GameState::GS_Paused:
	{
		backgroundScreen->Render();

		playerRightIdle->Render();
		playerRightRun->Render();
		playerLeftIdle->Render();
		playerLeftRun->Render();

		effectHearts->Render();
		effectFlames->SetPosition(player->GetPosition().x, player->GetPosition().y - 10);
		effectFlames->Render();
		particlesOrange->Render();
		particlesBanana->Render();

		pauseButton->Render();
		resumeButton->Render();
		orangeIcon->Render();
		clockIcon->Render();
		shoeIcon->Render();

		orange->Render();
		banana->Render();
		shoe->Render();

		std::string strData = std::to_string(orangesCollected);
		char* temp = new char[strData.length() + 1];
		strcpy(temp, strData.c_str());
		DrawBitmapText(temp, 1150.0f, 35.0f, 1.0f, 1.0f, 0.0f);

		std::string number2 = std::to_string((int)levelTimer);
		char* c = new char[number2.length() + 1];
		strcpy(c, number2.c_str());
		DrawBitmapText(c, 1150.0f, 70.0f, 1.0f, 1.0f, 0.0f);

		
		if (boostTrack > 0)
		{
			std::string number3 = std::to_string((int)boostTrack);
			char* c3 = new char[number3.length() + 1];
			strcpy(c3, number3.c_str());
			DrawBitmapText(c3, 1150.0f, 100.0f, 1.0f, 1.0f, 0.0f);
		}
		
	}
	break;

	case GameState::GS_BetweenLevels:
	{
		levelCompleteScreen->Render();
	}
	break;

	case GameState::GS_GameOver:
	{
		gameOverScreen->Render();

		exitButton->Render();
		menuButton->Render();
	}
	break;

	case GameState::GS_Finished:
	{
		finishScreen->Render();

		exitButton->Render();
		menuButton->Render();

		playerIcon->Render();
		orangeIconTwo->Render();
		orangeFinishIcon->Render();
		bananaFinishIcon->Render();
		shoeFinishIcon->Render();

		std::string strData = std::to_string(orangesCollectedTotal);
		char* temp = new char[strData.length() + 1];
		strcpy(temp, strData.c_str());
		DrawBitmapText(temp, 1025.0f, 235.0f, 1.0f, 1.0f, 0.0f);

		char* n = new char[nameFinal.length() + 1];
		strcpy(n, nameFinal.c_str());
		DrawBitmapText(n, 1025.0f, 170.0f, 1.0f, 1.0f, 0.0f);

		// only oranges
		std::string strOrg = std::to_string(orangesCollectedReal);
		char* tempOrg = new char[strOrg.length() + 1];
		strcpy(tempOrg, strOrg.c_str());
		DrawBitmapText(tempOrg, 1025.0f, 335.0f, 1.0f, 1.0f, 0.0f);

		// only bananas
		std::string strBan= std::to_string(bananasCollected);
		char* tempBan = new char[strBan.length() + 1];
		strcpy(tempBan, strBan.c_str());
		DrawBitmapText(tempBan, 1025.0f, 435.0f, 1.0f, 1.0f, 0.0f);

		// only shoes
		std::string strShoe = std::to_string(shoesCollected);
		char* tempShoe = new char[strShoe.length() + 1];
		strcpy(tempShoe, strShoe.c_str());
		DrawBitmapText(tempShoe, 1025.0f, 535.0f, 1.0f, 1.0f, 0.0f);
	}
	break;
	}

	glutSwapBuffers();
}

void GameLoop() 
{
	if (current_GameState == GameState::GS_Splash)
	{
		LoadTextures();
		InitFMOD();
		LoadAudio();

		current_GameState = GameState::GS_Loading;
	}

	Update();
	Render();
}

void display()
{
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = (float)(currentTime - previousTime) / 1000;
	previousTime = currentTime;

	GameLoop();
}

void reshape(const GLsizei p_width, const GLsizei p_height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 1200, 600, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutReshapeWindow(1200, 600);
}

void mouse(int button, int state, int x, int y)
{
	inputManager->mouse(button, state, x, y);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) 
	{
	case 'q':
	case 'Q':
	{
		if(name.length() < 20)
			name += 'q';
	}
	break;

	case 'w':
	case 'W':
	{
		if (name.length() < 20)
			name += 'w';
	}
	break;

	case 'e':
	case 'E':
	{
		if (name.length() < 20)
			name += 'e';
	}
	break;

	case 'r':
	case 'R':
	{
		if (name.length() < 20)
			name += 'r';
	}
	break;

	case 't':
	case 'T':
	{
		if (name.length() < 20)
			name += 't';
	}
	break;

	case 'z':
	case 'Z':
	{
		if (name.length() < 20)
			name += 'z';
	}
	break;

	case 'u':
	case 'U':
	{
		if (name.length() < 20)
			name += 'u';
	}
	break;

	case 'i':
	case 'I':
	{
		if (name.length() < 20)
			name += 'i';
	}
	break;

	case 'o':
	case 'O':
	{
		if (name.length() < 20)
			name += 'o';
	}
	break;

	case 'p':
	case 'P':
	{
		if (name.length() < 20)
			name += 'p';
	}
	break;

	case 'a':
	case 'A':
	{
		if (name.length() < 20)
			name += 'a';

		if (current_GameState == GameState::GS_Level || current_GameState == GameState::GS_LevelTwo)
			inputManager->SetCommand(Input::Command::CM_LEFT);
	}
	break;

	case 's':
	case 'S':
	{
		if (name.length() < 20)
			name += 's';
	}
	break;

	case 'd':
	case 'D':
	{
		if (name.length() < 20)
			name += 'd';
		if (current_GameState == GameState::GS_Level || current_GameState == GameState::GS_LevelTwo)
			inputManager->SetCommand(Input::Command::CM_RIGHT);
	}
	break;

	case 'f':
	case 'F':
	{
		if (name.length() < 20)
			name += 'f';
	}
	break;

	case 'g':
	case 'G':
	{
		if (name.length() < 20)
			name += 'g';
	}
	break;

	case 'h':
	case 'H':
	{
		if (name.length() < 20)
			name += 'h';
	}
	break;

	case 'j':
	case 'J':
	{
		if (name.length() < 20)
			name += 'j';
	}
	break;

	case 'k':
	case 'K':
	{
		if (name.length() < 20)
			name += 'k';
	}
	break;

	case 'l':
	case 'L':
	{
		if (name.length() < 20)
			name += 'l';
	}
	break;

	case 'y':
	case 'Y':
	{
		if (name.length() < 20)
			name += 'y';
	}
	break;

	case 'x':
	case 'X':
	{
		if (name.length() < 20)
			name += 'x';
	}
	break;

	case 'c':
	case 'C':
	{
		if (name.length() < 20)
			name += 'c';
	}
	break;

	case 'v':
	case 'V':
	{
		if (name.length() < 20)
			name += 'v';
	}
	break;

	case 'b':
	case 'B':
	{
		if (name.length() < 20)
			name += 'b';
	}
	break;

	case 'n':
	case 'N':
	{
		if (name.length() < 20)
			name += 'n';
	}
	break;

	case 'm':
	case 'M':
	{
		if (name.length() < 20)
			name += 'm';
	}
	break;

	// backspace
	case 8:
	{
		if (name.length() > 0)
			name.resize(name.size() - 1);
	}
	break;

	case 27:
		exit(0);
		break;
	default:
		inputManager->keyboardKey(key, x, y);
	}
}

void keyboardReleased(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'd':
	{
		inputManager->SetCommand(Input::Command::CM_STOP);
	}
	break;

	case 'a':
	{
		inputManager->SetCommand(Input::Command::CM_STOP);
	}
	break;
	}
}

void keyboardSpecial(int key, int x, int y) 
{
	inputManager->keyboardSpec(key, x, y);
}

void keyboardSpecialReleased(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_RIGHT:
	{
		inputManager->SetCommand(Input::Command::CM_STOP);
	}
	break;

	case GLUT_KEY_LEFT:
	{
		inputManager->SetCommand(Input::Command::CM_STOP);
	}
	break;

	}
}

void initGL()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_FLAT);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glDisable(GL_DEPTH_TEST);

	previousTime = glutGet(GLUT_ELAPSED_TIME);
}

void refreshTimer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(refresh, refreshTimer, 0);
}

int main(int argc, char** argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);

	screenWidth = (GLfloat)1200; // 1067
	screenHeight = (GLfloat)600;
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(300, 200);
	glutCreateWindow("Gravity Game");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(0, refreshTimer, 0);

	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardReleased);
	glutSpecialFunc(keyboardSpecial);
	glutSpecialUpFunc(keyboardSpecialReleased);

	initGL();
	StartGame();
	glutMainLoop();

	return 0;
}