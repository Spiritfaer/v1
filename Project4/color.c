#include "main.h"

t_rgb	get_black_color(void)
{
	return ((t_rgb) {0, 0, 0, BLACK});
}
t_rgb	get_red_color(void)
{
	return ((t_rgb) { 255, 0, 0, RED });
}
t_rgb	get_green_color(void)
{
	return ((t_rgb) { 0, 255, 0, GREEN });
}
t_rgb	get_blue_color(void)
{
	return ((t_rgb) { 0, 0, 255, BLUE });
}
t_rgb	get_white_color(void)
{
	return ((t_rgb) { 255, 255, 255, WHITE });
}
void	set_color(t_rgb *color, uint8_t r, uint8_t g, uint8_t b)
{
	color->r = r;
	color->g = g;
	color->b = b;
	color->color = (color->r << 16 | color->g << 8 | color->b);
}
void	set_rgb_to_int(t_rgb *src)
{
	src->color = (src->r << 16 | src->g << 8 | src->b);
}
void	set_int_to_rgb(t_rgb *src)
{
	src->r = (src->color & RED) >> 16;
	src->g = (src->color & GREEN) >> 8;
	src->b = src->color & BLUE;
}

uint8_t	add_8_bit(uint8_t a, uint8_t b)
{
	int16_t sum;

	sum = (int16_t)a + (int16_t)b;
	sum = sum > 255 ? 255 : sum;
	sum = sum < 0 ? 0 : sum;
	return ((uint8_t)sum);
}
uint8_t	mult_8_bit(uint8_t a, double_t f)
{
	int16_t mult;

	mult = (int16_t)((double_t)a * f);
	mult = mult > 255 ? 255 : mult;
	mult = mult < 0 ? 0 : mult;
	return ((uint8_t)mult);
}
uint8_t	inter_8_bit(uint8_t a, uint8_t b)
{
	float_t cof;
	int16_t sum;
	int16_t t = 75;

	cof = ((float_t)a - (float_t)b) / 3;
	sum = (int16_t)a - (int16_t)cof;
	sum = sum > 255 ? 255 : sum;
	sum = sum < 0 ? 0 : sum;
	return ((uint8_t)sum);
}
t_rgb	colort_add_colort(t_rgb one, t_rgb two)
{
	t_rgb res;

	res.r = add_8_bit(one.r, two.r);
	res.g = add_8_bit(one.g, two.g);
	res.b = add_8_bit(one.b, two.b);
	set_rgb_to_int(&res);
	return (res);
}
int32_t	colort_int_add_colort_int(int32_t one, int32_t two)
{
	t_rgb one_t;
	t_rgb two_t;
	t_rgb res;

	one_t.color = one;
	two_t.color = two;

	set_int_to_rgb(&one_t);
	set_int_to_rgb(&two_t);

	res.r = inter_8_bit(one_t.r, two_t.r);
	res.g = inter_8_bit(one_t.g, two_t.g);
	res.b = inter_8_bit(one_t.b, two_t.b);
	set_rgb_to_int(&res);
	return (res.color);
}

t_rgb	colort_mult_f(t_rgb one, double_t f)
{
	t_rgb res;

	res.r = mult_8_bit(one.r, f);
	res.g = mult_8_bit(one.g, f);
	res.b = mult_8_bit(one.b, f);
	set_rgb_to_int(&res);
	return (res);
}
