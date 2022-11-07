#include "cub3d.h"

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

static size_t	get_map_size(char *path)
{
	size_t	map_sz;
	char	*line;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	map_sz = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		free(line);
		map_sz++;
	}
	close(fd);
	return (map_sz);
}

char **load_map_file(char *path, size_t	sz)
{
	char	**map;
	char	*line;
	int		fd;

	map = ft_calloc(sizeof(char *), sz + 1);
	if (!map)
		return (NULL);
	sz = 0;
	fd = open(path, O_RDONLY);
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

char	**load_map(char *path)
{
	size_t	sz;

	sz = get_map_size(path);
	if (!sz)
		return (NULL);
	return (load_map_file(path, sz));
}
