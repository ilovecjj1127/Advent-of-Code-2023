#include "libft/libft.h"

char	*next_node(char **tabs, char dir, char *node)
{
	int		i = 1;
	char	*new_node;

	while (tabs[i] && ft_strncmp(node, tabs[i], 3))
		i++;
	if (dir == 'L')
		new_node = tabs[i] + 7;
	else
		new_node = tabs[i] + 12;
	return (new_node);
}

int	main(int argc, char **argv)
{
	int		fd, bytesread, len;
	char	*content = NULL;
	char	buffer[1001];
	char	**tabs;
	int		count = 0;

	fd = open(argv[argc - 1], O_RDONLY);
	while ((bytesread = read(fd, buffer, 1000)))
	{
		buffer[bytesread] = '\0';
		content = ft_strjoin(content, buffer);
	}
	len = arr_len(content, '\n');
	tabs = ft_split(content, '\n');
	char	*node = "AAA";
	int		i = 0;
	while (ft_strncmp(node, "ZZZ", 3))
	{
		node = next_node(tabs, tabs[0][i], node);
		count++;
		if (!tabs[0][++i])
			i = 0;
	}
	printf("%d\n", count);
	free(content);
	free_arr(tabs);
}