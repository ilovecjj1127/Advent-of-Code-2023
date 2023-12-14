#include "libft/libft.h"


void	move_rock_north(char **platform, int i, int j)
{
	int pos;

	if (i == 0)
		return ;
	pos = i - 1;
	while (pos > 0 && platform[pos][j] == '.')
		pos--;
	if (pos == 0 && platform[pos][j] == '.')
		pos--;
	platform[i][j] = '.';
	platform[pos + 1][j] = 'O';
}

void	move_rock_south(char **platform, int i, int j)
{
	int pos;

	if (!platform[i + 1])
		return ;
	pos = i + 1;
	while (platform[pos + 1] && platform[pos][j] == '.')
		pos++;
	if (!platform[pos + 1] && platform[pos][j] == '.')
		pos++;
	platform[i][j] = '.';
	platform[pos - 1][j] = 'O';
}

void	move_rock_east(char **platform, int i, int j)
{
	int pos;

	if (!platform[0][j + 1])
		return ;
	pos = j + 1;
	while (platform[i][pos + 1] && platform[i][pos] == '.')
		pos++;
	if (!platform[i][pos + 1] && platform[i][pos] == '.')
		pos++;
	platform[i][j] = '.';
	platform[i][pos - 1] = 'O';
}

void	move_rock_west(char **platform, int i, int j)
{
	int pos;

	if (j == 0)
		return ;
	pos = j - 1;
	while (pos > 0 && platform[i][pos] == '.')
		pos--;
	if (pos == 0 && platform[i][pos] == '.')
		pos--;
	platform[i][j] = '.';
	platform[i][pos + 1] = 'O';
}

void	tilt_north(char **platform)
{
	int	i, j;
	int	len;

	j = -1;
	len = ft_strlen(platform[0]);
	while (++j < len)
	{
		i = -1;
		while (platform[++i])
		{
			if (platform[i][j] == 'O')
				move_rock_north(platform, i, j);
		}
	}
}

void	tilt_south(char **platform, int dep)
{
	int	i, j;
	int	len;

	j = -1;
	len = ft_strlen(platform[0]);
	while (++j < len)
	{
		i = dep;
		while (--i >= 0)
		{
			if (platform[i][j] == 'O')
				move_rock_south(platform, i, j);
		}
	}
}

void	tilt_west(char **platform)
{
	int	i, j;
	int	len;

	j = -1;
	len = ft_strlen(platform[0]);
	while (++j < len)
	{
		i = -1;
		while (platform[++i])
		{
			if (platform[i][j] == 'O')
				move_rock_west(platform, i, j);
		}
	}
}

void	tilt_east(char **platform)
{
	int	i, j;

	j = ft_strlen(platform[0]);
	while (--j >= 0)
	{
		i = -1;
		while (platform[++i])
		{
			if (platform[i][j] == 'O')
				move_rock_east(platform, i, j);
		}
	}
}

int	get_load(char **platform, int dep)
{
	int	i, j;
	int	load;

	i = -1;
	load = 0;
	while (platform[++i])
	{
		j = -1;
		while (platform[i][++j])
		{
			if (platform[i][j] == 'O')
				load += dep;
		}
		dep--;
	}
	return (load);
}

int	main(int argc, char **argv)
{
	int		fd;
	char	*content = NULL;
	char	buffer[1001];
	int		bytesread;
	char	**platform;

	fd = open(argv[argc - 1], O_RDONLY);
	if (fd == -1)
		return (1);
	while ((bytesread = read(fd, buffer, 1000)))
	{
		buffer[bytesread] = '\0';
		content = ft_strjoin(content, buffer);
	}
	platform = ft_split(content, '\n');
	int	dep = arr_len(content, '\n');
	int	i = 0;
	while (++i <= 1000000000)
	{
		tilt_north(platform);
		tilt_west(platform);
		tilt_south(platform, dep);
		tilt_east(platform);
	}
	printf("%d\n", get_load(platform, dep));

	free(content);
	free_arr(platform);
	close(fd);
	return (0);
}