/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 21:19:30 by mialbert          #+#    #+#             */
/*   Updated: 2022/06/20 16:26:30 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "libft.h"
# include "MLX42/MLX42.h"
# include <sys/types.h>

# ifndef _WIN32
	# include <sys/wait.h>
	# define WIN 0
# else 
	# include <windows.h>
	# include <mmsystem.h>
	# define WIN 1
# endif 

# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <sys/stat.h>
# include <fcntl.h>
# define GHOSTCOUNT 10
# define PINKCOUNT 10
# define POTIONCOUNT 2
# define BLOK 32 		// pixel width/height of one image
# define LIVES 5
# define ACCEL 1 		// starting value of the acceleration of a jump
# define ACCEL_MOD 1.3 	// the value accel is multiplied with every frame
# define JUMP_CAP 100	// the value accel needs to get to stop a jump
# define FATASS 10 		// how slow the player moves
# define FATBOO 15		// how slow ghosts move
# define SPEED 18 		// how many frames it takes to change ghost movement
# define IMMORTAL 0 	// toggle immortality
# define KILL 1 		// toggle ability to kill enemies
# define GRAV 1 		// toggle gravity
# define BUFFERSIZE 30	// How many characters are read in one loop, 
						// used when reading the map
# if defined(__linux__)
    #define AUDIO "/usr/bin/aplay"
# elif defined(__APPLE__)
    #define AUDIO "/usr/bin/afplay", "--volume", "1"
# else 
	#define AUDIO ""
# endif

#ifndef STDOUT_FILENO
	#define STDOUT_FILENO 2
#endif

// ---Do not touch this:--- //
# define DIFFCOUNT 2

typedef enum enumy
{
	GHOST,
	PINK,
}	t_enumy;

typedef enum move
{
	X,
	Y,
	XY
}	t_move;

typedef enum mlx_images
{
	STRLIFE,
	STRMOVE,
	PICKUP,
	CHAR_R,
	CHAR_L,
	DOOR,
	TILE,
	WALL,
	SLIME,
	BG,
	BRICK,
	PINK_R,
	PINK_L,
	SCREEN,
	GREY,
	RED,
	POTION,
	KEY_STR,
	CIRCLE,
	IMG_COUNT,
}	t_images;

typedef enum obs_enum
{
	OBS_PICKUP,
	OBS_GHOST,
	OBS_PINK,
	OBS_EXIT,
	OBS_1,
	OBSCOUNT
}	t_obs_enum;

typedef enum string
{
	LIFE,
	MOVE,
	FRAME,
	ENDFRAME,
	TEST,
	STR_COUNT,
}	t_string;

typedef struct enemy_diff
{
	mlx_image_t		*ghost_img[GHOSTCOUNT];
	mlx_image_t		*pink_img[PINKCOUNT];
	mlx_image_t		**lal[DIFFCOUNT + 1];
}	t_enemy_diff;

typedef struct line
{
	ssize_t	count;
	ssize_t	size;
}	t_line;

typedef struct animate
{
	size_t		dir;
	uint32_t	length;
	uint32_t	start;
	uint32_t	xy[XY];
}	t_animate;

typedef struct coords
{
	size_t	x_start;
	size_t	x_end;
	size_t	y_start;
	size_t	y_end;
	int32_t	instance;
}	t_coords;

/**
 * So I should have written this in a way that I could have just 
 * reused it for different enemies with different instances of this
 * struct. Also I should have used linked lists, so I wouldn't need
 * exception arrays, I could just take enemies out of the list.
 * I have so many variables for the double exception array, 
 * because I couldn't figure out how to initalise it otherwise. 
 * (*excep[DIFFCOUNT + 1] + ghost_excep[GHOSTCOUNT] + pink_excep[PINKCOUNT])
 */

typedef struct enemy
{
	bool			fall_lock;
	t_animate		pink_anim;
	size_t			ghost_move[GHOSTCOUNT];
	size_t			pink_move[PINKCOUNT];
	size_t			ghost_excep[GHOSTCOUNT];
	size_t			pink_excep[PINKCOUNT];
	size_t			counts[DIFFCOUNT];
	size_t			current_time;
	size_t			excep_count;
	size_t			*excep[DIFFCOUNT + 1];
	mlx_texture_t	*ghost;
	mlx_texture_t	*ghost_r;
	mlx_image_t		*ghost_img[GHOSTCOUNT];
	ssize_t			ghost_spawn[GHOSTCOUNT];
	mlx_image_t		**img_order;
	size_t			max;
	size_t			*move[DIFFCOUNT + 1];
	ssize_t			pink_spawn[PINKCOUNT];
	size_t			time;
	bool			time_lock;
	size_t			total_enemies;
	int32_t			x[2];
	int32_t			y[2];
}	t_enemy;

/**
 * There should be a t_coords array. 
 */
typedef struct image_data
{
	t_animate			animate;
	float				accel;
	char				*bigass;
	uint32_t			char_start;
	bool				*excep_pickup;
	bool				excep_potion[POTIONCOUNT];
	size_t				pickup_max;
	size_t				pickup_count;
	char				*combstr[STR_COUNT];
	int32_t				count[STR_COUNT];
	bool				counter_lock;
	t_enemy				enemy;
	t_enemy_diff		enemy_diff;
	bool				fly;
	int32_t				height;
	mlx_image_t			*img[IMG_COUNT];
	size_t				obs_amount[OBSCOUNT];
	mlx_key_data_t		*keydata;
	bool				jump_lock;
	t_line				line;
	char				**map;
	mlx_t				*mlx;
	t_coords			*obs_pickup;
	t_coords			*obs_tile;
	t_coords			*obs_1;
	t_coords			player;
	t_coords			obs_potion[POTIONCOUNT];
	size_t				old_x;
	size_t				old_y;
	int32_t				pid;
	int32_t				pid2;
	uint8_t				*pixel;
	ssize_t				potion_spawn[POTIONCOUNT];
	uint8_t				startingpoint;
	char				*str[STR_COUNT];
	size_t				tile_count;
	int32_t				width;
	char				*you_won;
	xpm_t				*xpm[IMG_COUNT];
	uint32_t			xy[2];
}	t_imgdata;

typedef struct error_cases
{
	bool	error;
	bool	file_name;
	bool	walls;
	bool	no_cpe;
	bool	different_input;
	bool	not_rectangular;
	bool	morecharacters;
	bool	enemyoverflow;
	bool	enemyunderflow;
	bool	wrong_diffcount;
}	t_error;

void		audio(void);
void		animate_char(t_imgdata *data, t_animate *animate, size_t x, \
																size_t y);
void		animate_ghosts(t_imgdata *data, mlx_texture_t *ghost, \
												size_t i, size_t j);
void		animate_pinks(t_imgdata *data, size_t i, size_t x, size_t y);
ssize_t		*avail_ground_spawn(t_imgdata *data, t_line *line, \
												int *spawn_count);
void		check_damage(t_imgdata *data, int32_t *player, size_t i, size_t j);
void		check_enemy_error(t_imgdata *data, t_enemy *enemy, t_error *errors);
bool		check_ext(char *file_name, char *ext);
void		check_player_amount(t_error *errors, t_imgdata *data);
void		collect(t_imgdata *data, size_t x, size_t y);
void		colour_screen(t_imgdata *data, int32_t macro, int32_t colour);
void		display_message(t_imgdata *data, bool death, float x_mod, \
															float y_mod);
void		display_string(t_imgdata *data, int32_t str_img, size_t x, \
																char *str);
void		end(mlx_key_data_t keydata, void *data);
void		end_message(t_imgdata *data);
void		enemies(t_imgdata *data, t_enemy *enemy, size_t x, size_t y);
bool		random_to_window(t_imgdata *data, ssize_t *index, size_t max_count, \
															mlx_image_t **img);
void		error_output(t_error *errors, t_line *line);
void		error_close_window(t_imgdata *data, char *str);
int32_t		find_c_instance(t_imgdata *data, size_t index);
void		free_2d(char **map);
bool		free_array(mlx_image_t **arr, char *str, t_imgdata *data);
void		free_close_window(t_imgdata *data, void *var, char *str);
void		gameloop_unix(t_imgdata *data);
void		gravity(t_imgdata *data, size_t x, size_t y);
size_t		getncount(char *str, uint8_t chr);
size_t		getncount(char *str, uint8_t chr);
void		get_ghost_spawn(t_imgdata *data, t_enemy *enemy, t_line *line);
bool		get_ground_spawn(int *spawn_count, ssize_t *avail, ssize_t *spawn, \
															size_t max_count);
int32_t		graphics(t_imgdata *data, t_line *line, t_enemy *enemy);
void		hook(void	*data);
bool		images_to_window(t_imgdata *data, size_t i);
void		init_coords(t_imgdata *data, size_t index, int32_t obs_index, \
																t_coords *obs);
char		**input_handler(int32_t fd, t_imgdata *data, \
							t_line *line, t_enemy *enemy);
void		kill_process(t_imgdata *data);
void		kill_enemy(t_imgdata *data, int32_t *player, size_t i, size_t j);
void		kurwa_audio(char *args[]);
bool		loading_images(t_imgdata *data, xpm_t **xpm);
void		movement(t_imgdata *data, size_t x, size_t y);
void		movecounter(t_imgdata *data, t_animate *animate, size_t x, \
																size_t y);
void		obstacle_pickup(t_imgdata *data);
char		*read_file(int32_t fd);
void		terminate(t_imgdata *data);
bool		texture_to_image(t_imgdata *data, xpm_t **xpm, mlx_image_t **img);
void		turn_char(t_imgdata *data, size_t macro, size_t x, size_t y);
bool		windowdisplay(t_imgdata *data, t_line *line, xpm_t **xpm);
#endif