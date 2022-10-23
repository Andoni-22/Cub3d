#include <stdio.h>
#include <stdint.h>

int	main(int ac, char *av[]) {
	
	int	color = 0xFF0000;
	uint8_t	color_byte = 254;

	printf("COLOR: %d\n", color);
	printf("COLOR_BYTE: %d\n", color_byte);
	printf("COLOR_BYTE: %d\n", color_byte << 16);
	(void)ac;
	(void)av;
	return 0;
}

