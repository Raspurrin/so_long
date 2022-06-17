/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 21:19:30 by mialbert          #+#    #+#             */
/*   Updated: 2022/06/17 22:58:42 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft.h"
# include "MLX42/MLX42.h"

# include <stdlib.h>
# include <sys/stat.h>
# include <fcntl.h>
# define BLOK 32 		// pixel width/height of one image
# define ACCEL 1 		// starting value of the acceleration of a jump
# define ACCEL_MOD 1.3 	// the value accel is multiplied with every frame
# define JUMP_CAP 100	// the value accel needs to get to stop a jump
# define FATASS 10 		// how slow the player moves
# define SPEED 18 		// how many frames it takes to change ghost movement
# define GRAV 1 		// toggle gravity
# define BUFFERSIZE 30	// How many characters are read in one loop, 
						// used when reading the map

#ifndef STDOUT_FILENO
	#define STDOUT_FILENO 2
#endif

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
	CHAR,
	CHAR_L,
	DOOR,
	TILE,
	WALL,
	BG,
	BRICK,
	SCREEN,
	GREY,
	RED,
	IMG_COUNT,
}	t_images;

typedef enum obs_enum
{
	OBS_PICKUP,
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

typedef struct line
{
	ssize_t	count;
	ssize_t	size;
}	t_line;

typedef struct obstacle
{
	size_t	x_start;
	size_t	x_end;
	size_t	y_start;
	size_t	y_end;
	int32_t	instance;
}	t_coords;

typedef struct image_data
{
	float			accel;
	char			*bigass;
	uint32_t		char_start;
	size_t			pickup_max;
	size_t			pickup_count;
	char			*combstr[STR_COUNT];
	int32_t			count[STR_COUNT];
	bool			counter_lock;
	bool			fly;
	int32_t			height;
	mlx_image_t		*img[IMG_COUNT];
	mlx_key_data_t	*keydata;
	bool			jump_lock;
	t_line			line;
	char			**map;
	mlx_t			*mlx;
	t_coords		*obs_pickup;
	bool			*excep_pickup;
	size_t			old_x;
	size_t			old_y;
	int32_t			pid;
	uint8_t			*pixel;
	uint8_t			startingpoint;
	char			*str[STR_COUNT];
	int32_t			width;
	xpm_t			*xpm[IMG_COUNT];
	uint32_t		xy[2];
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
	bool	wrong_diffcount;
}	t_error;

void	check_damage(t_imgdata *data, int32_t *player, size_t i, size_t j);
bool	check_ext(char *file_name, char *ext);
void	check_player_amount(t_error *errors, t_imgdata *data);
void	collect(t_imgdata *data, size_t x, size_t y);
void	colour_screen(t_imgdata *data, int32_t macro, int32_t colour);
void	display_message(t_imgdata *data, bool death, float x_mod, float y_mod);
void	display_string(t_imgdata *data, int32_t str_img, size_t x, char *str);
void	end(mlx_key_data_t keydata, void *data);
void	end_message(t_imgdata *data);
void	error_output(t_error *errors, t_line *line);
void	error_close_window(t_imgdata *data, char *str);
int32_t	find_c_instance(t_imgdata *data, size_t index);
void	free_2d(char **map);
bool	free_array(mlx_image_t **arr, char *str, t_imgdata *data);
void	free_close_window(t_imgdata *data, void *var, char *str);
void	gravity(t_imgdata *data, size_t x, size_t y);
size_t	getncount(char *str, uint8_t chr);
size_t	getncount(char *str, uint8_t chr);
int32_t	graphics(t_imgdata *data, t_line *line);
bool	images_to_window(t_imgdata *data, size_t i);
char	**input_handler(int32_t fd, t_imgdata *data, t_line *line);
bool	loading_images(t_imgdata *data, xpm_t **xpm);
void	movement(t_imgdata *data, size_t x, size_t y);
void	movecounter(t_imgdata *data, size_t x, size_t y);
void	obstacle_pickup(t_imgdata *data);
char	*read_file(int32_t fd);
void	terminate(t_imgdata *data);
bool	texture_to_image(t_imgdata *data, xpm_t **xpm, mlx_image_t **img);
void	turn_char(t_imgdata *data, size_t macro, size_t x, size_t y);
bool	windowdisplay(t_imgdata *data, t_line *line, xpm_t **xpm);
#endif