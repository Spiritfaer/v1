#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

typedef struct		s_rgb
{
	uint8_t			r;
	uint8_t			g;
	uint8_t			b;
	uint32_t		color;
}					t_rgb;

t_rgb		get_black_color(void);
t_rgb		get_red_color(void);
t_rgb		get_green_color(void);
t_rgb		get_blue_color(void);
t_rgb		get_white_color(void);
void		set_color(t_rgb *color, uint8_t r, uint8_t g, uint8_t b);
void		set_rgb_to_int(t_rgb *src);
void		set_int_to_rgb(t_rgb *src);
t_rgb		colort_add_colort(t_rgb one, t_rgb two);
t_rgb		colort_mult_f(t_rgb one, double_t f);
int32_t		colort_int_add_colort_int(int32_t one, int32_t two);

#endif // !COLOR_H
