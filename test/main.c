#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define WIDTH	500
#define HEIGHT	500

#define texWidth 64
#define texHeight 64

typedef struct	s_texture
{
	int	xorcolor;
	int	ycolor;
	int	xycolor;
}	t_texture;

static void	set_texture_colors(char *texture, int y, int x, int color)
{
	char	*offset;

	offset = texture + x + y;
	*(unsigned char *)texture = color;
}

static void create_texture(char texture[8][16384])
{
	t_texture	t;
	size_t	x;
	size_t	y;

	memset(&t, 0, sizeof(t_texture));
	x = -1;
	while (++x < texWidth)
	{
		y = -1;
		while (++y < texHeight)
		{
			t.xorcolor = (x * 256 / texWidth) ^ (y * 256 / texHeight);
			t.ycolor = y * 256 / texHeight;
			t.xycolor = y * 128 / texHeight + x * 128 / texWidth;

			set_texture_colors(texture[0], y, x, 65536 * 254 * (x != y && x != texWidth - y));//flat red texture with black cross
			set_texture_colors(texture[1], y, x, t.xycolor + 256 * t.xycolor + 65536 * t.xycolor); //sloped greyscale
			set_texture_colors(texture[2], y, x, 256 * t.xycolor + 65536 * t.xycolor); //sloped yellow gradien
			set_texture_colors(texture[3], y, x, t.xorcolor + 256 * t.xorcolor + 65536 * t.xorcolor); //t.xor greyscale;
			set_texture_colors(texture[4], y, x, 256 * t.xorcolor); //t.xor green;
			set_texture_colors(texture[5], y, x, 65536 * 192 * (x % 16 && y % 16)); //red bricks;
			set_texture_colors(texture[6], y, x, 65536 * t.ycolor); //red gradient;
			set_texture_colors(texture[7], y, x, 128 + 256 * 128 + 65536 * 128); //flat grey texture;
		}
	}
}

int	main(int ac, char *av[]) {
	
	char	texture[8][texWidth * texHeight * 4];

	create_texture(texture);
	(void)ac;
	(void)av;
	return 0;
}
