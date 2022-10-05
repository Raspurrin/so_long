# <img width="80" alt="image" src="https://user-images.githubusercontent.com/13866954/172734156-4388b646-5a3a-4da7-934a-d8e8d323916a.png"> So_long

### Index:

+ [Description](#description) 
+ [Bonus features](#bonus-features) 
+ [How to compile and run the game](#how-to-compile-and-run-the-game)
+ [Input maps](#input-maps)
+ [Changing game settings](#changing-game-settings)
+ [Future additions](#future-additions)

## Description

My game was made in C with the graphical library <a href="https://github.com/codam-coding-college/MLX42">MLX42</a>

The goal of the game is to collect all pickups and go through the exit and... Not get killed in the process.
Usually this project is made with a top-down view, but I decided to make it a platformer instead!
It runs on Mac, Linux, and for Windows only the mandatory part works. 
If there are any issues with running it, refer to MLX42 for guidance. 

## Bonus features
- Smooth animations.
- Gravity.
- Sound effects and background music.
- The ability to jump.
- Two types of enemies which spawn in random locations and have random movement:
  - Ghosts, flying enemies.
  - Pink monsters, ground enemies. 
- Lives with a cooldown period upon getting hit and a red filter to indicate that.
- Movement counter and lives counter on the screen.
- Ability to kill enemies by jumping on them.
- An ending message with a game over or winning screen at the end.


https://user-images.githubusercontent.com/13866954/172744088-48f9b5ca-bb5f-45f2-b644-9dd0d4923bdc.mov


The main character has a different animation for moving and standing still.
And also switches between a reversed spritesheet when going in a different direction:

https://user-images.githubusercontent.com/13866954/172726896-85649e64-340c-49c6-bf62-05342e95acee.mov

## How to compile and run the game 

You could clone the project with `git clone --recurse-submodules <git url>`, but even without
the submodules will be initialised and updated automatically. 

To run only the mandatory part of the game use `make` and to include the bonus use `make bonus`

If you are on Linux and simply typing make doesn't work, that means don't have all required libraries. 
Use this command to install them:

```c
  make install on linux
```
And then run the game by typing: 
```c
  ./so_long input/large_map.ber
```

## Input maps:

It can take different maps as input to generate different levels, provided it passes all requirements. 
I provided valid and some invalid maps in the input folder. 
You can make your own maps provided they are rectangular, use the .ber extension, are fully enclosed by walls, 
include only one P, contains at least one C and E character. 
0 = empty space, E = exit, P = player starting location, 1 = wall or platform, C = collectible 

## Changing game settings: 
In the header in the includes folder you can change macros to change the game, 
like how many lives you have, the amount of enemies, to toggle gravity, damage, change the jump modifiers and so on.
Make sure to recompile everything by using `make re` to apply the changes.

## Future additions

For now I want to focus on my other projects but at some point I want to improve this game a little:

- Make certain it runs on different platforms.
- Clean up my code. If you have any suggestions for this, don't hesistate to tell me, I would love to hear feedback!
- Fix the collision.
- Make the background and ending messages dynamic and scalable.
- Timer with decreasing visibility.
- Create a menu where you can change the game settings and a pause option. 
- Make different levels. 
- A scoreboard. 
- A blog post/tutorial about the project, which will cover both implementation for Minilibx and MLX42.
