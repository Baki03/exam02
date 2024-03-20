#include "get_next_line.h"

int	ft_strlen(char	*str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*get_line(char	*stash)
{
	char	*line;
	int		i;

	i = 0;
	while (stash[i] != '\n' && stash[i])
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] != '\n' && stash[i])
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*clean_stash(char	*stash)
{
	char	*new_stash;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (stash[i] != '\n' && stash[i])
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	new_stash = (char *)malloc(sizeof(char) * (ft_strlen(stash) - i + 1));
	if (!new_stash)
		return (NULL);
	i++;
	while (stash[i])
	{
		new_stash[j] = stash[i];
		j++;
		i++;
	}
	new_stash[j] = '\0';
	free(stash);
	return (new_stash);
}

char	*ft_strjoin(char	*stash, char	*buffer)
{
	char	*new_stash;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!stash && !buffer)
		return (NULL);
	len = ft_strlen(stash) + ft_strlen(buffer);
	new_stash = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_stash)
		return (NULL);
	if (stash)
	{
		while (stash[i] != '\0')
		{
			new_stash[j] = stash[i];
			i++;
			j++;
		}
		i = 0;
	}
	while (buffer[i] != '\0')
	{
		new_stash[j] = buffer[i];
		j++;
		i++; 
	}
	new_stash[j] = '\0';
	free(stash);
	return (new_stash);
}

int	get_next_line(char **line)
{
	int			fd;
	static char	*stash;
	char		buffer[BUFFER_SIZE + 1];
	int			readed;

	fd = 0;
	readed = 1;
	if (!line)
		return (-1);
	while (buffer[0] != '\n' && readed != 0)
	{
		readed = read(fd, buffer, BUFFER_SIZE);
		if (readed == -1)
			return (-1);
		buffer[readed] = '\0';
		stash = ft_strjoin(stash, buffer);
	}
	*line = get_line(stash);
	stash = clean_stash(stash);
	if (readed == 0)
		return (0);
	else
		return (1);
}
