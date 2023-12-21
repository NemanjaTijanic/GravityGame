# Gravity Game
**Introduction**

This is a simple 2D gravity game where you play as a fox and collect falling fruit in order to gain as much points as possible and set a new high score. The purpose of this project was for me to learn the proccess of making a game using OpenGL and gain deeper understanding of the logic behind video games.

The game was made with OpenGL, using GLUT, SOIL2 and FMOD libraries.

## Specifics
**Gameplay**

The gameplay loop revolves around the player trying to set a new high score by collecting as many points as he can during the two rounds he is given. Both rounds have a set time limit and spawn 3 types of collectibles. 

The two main ones that give points when collected are the oranges and the bananas that fall from the sky. Oranges fall slower but are worth less points, while the bananas are the opposite, falling faster and giving more points. The third type of collectibles are the sneakers that spawn on the ground. When collected they give a speed increase for a certain time.

After the two rounds are completed, a detailed statistics panel is shown, featuring the players name, total points collected, and how many instances of each of the collectibles was collected exactly. If the achieved score is higher than at least one of the scores in the top five list, the players username and score will be shown in the high score menu.

## Installation

Visual Studio version 2019 or higher is required (64-bit).

- Download GravityGame folder and SLN file.
- Open the project using Visual Studio.
- Build and run the game.

## Screenshots

![Splash Screen](https://i.imgur.com/jW1E9eN.png)
![Main Menu](https://i.imgur.com/wZeEwv6.png)
![High Score Menu](https://i.imgur.com/q7Fbiom.png)
![Username Prompt](https://i.imgur.com/6uaS3Sf.png)
![Gameplay 01](https://i.imgur.com/Ss9GkF9.png)
![Gameplay 02](https://i.imgur.com/KJTXcmM.png)
![Victory Screen](https://i.imgur.com/EepO4Mt.png)
