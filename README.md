# so_long

My game was made in C with the graphical library <a href="https://github.com/codam-coding-college/MLX42">MLX42</a>

The goal of the game is to collect all pickups and go through the exit and... Not get killed in the process.
Usually this project is made with a top-down view, but I decided to make it a platformer instead!

### It includes the following bonus features:
- Smooth animation.
- Gravity.
- The ability to jump.
- Two types of enemies which spawn in random locations and have random movement:
  - Ghosts, flying enemies.
  - Pink monsters, ground enemies. 
- Lives with a cooldown period upon getting hit and a red filter to indicate that.
- Ability to kill enemies by jumping on them.
- An ending message with a game over or winning screen at the end.

https://user-images.githubusercontent.com/13866954/172726956-90b16493-c178-4039-beb6-f9a9fb15fbda.mov



The main character has a different animation for moving and standing still.
And also switches between a reversed spritesheet when going in a different direction:

https://user-images.githubusercontent.com/13866954/172726896-85649e64-340c-49c6-bf62-05342e95acee.mov

### How to compile and run the game: 
To run the game type these commands: 
```c
  make
```
If you are on Linux and simply typing make doesn't work, that means don't have all required libraries. 
Use this command to install them:

```c
  make install on linux
```
And then run the game by typing: 
```c
  ./so_long input/large_map.ber
```

### Input maps:

It can take different maps as input to generate different levels, provided it passes all requirements. 
I provided valid and some invalid maps in the input folder. 
You can make your own maps provided they are rectangular, use the .ber extension, are fully enclosed by walls, 
include only one P, contains at least one C and E character. 
0 = empty space, E = exit, P = player starting location, 1 = wall or platform, C = collectible 

### Changing game settings: 
In the header in the includes folder you can change macros to change the game, 
like how many lives you have, the amount of enemies, to toggle gravity, damage, change the jump modifiers and so on. 


## Future additions

For now I want to focus on my other projects but at some point I want to improve this game a little.
I won't add too much to it because I want to start from scratch and make something even better instead!:

- Fixing the collision regarding the platforms and the left wall and making it more precise in general.
- Making the background and ending message truly dynamic and scaleable.
- Cleaning up my code.
