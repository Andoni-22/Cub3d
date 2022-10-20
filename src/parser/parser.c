#include "cub3d.h"

ssize_t	get_map_size(int fd)
{
	ssize_t	map_sz;
	char	*line;

	map_sz = -1;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		map_sz++;
	}
	close(fd);
	return (map_sz);
}

char	**load_map(ssize_t sz, int fd)
{
	char	*line;
	char	**map;

	map = ft_calloc(sizeof(char *), sz + 1);
	if (!map)
	{
		close(fd);
		return (NULL);
	}
	sz = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		map[sz++] = line;
	}
	close(fd);
	return (map);
}
