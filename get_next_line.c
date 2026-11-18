/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   get_next_line.c                                     :+:    :+:           */
/*                                                      +:+                   */
/*   By: fozturk <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/11/18 17:23:07 by fozturk        #+#    #+#                */
/*   Updated: 2026/11/18 17:23:08 by fozturk        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_extract_line(char **line)
{
	char	*tmp;
	char	*extract;
	int		i;
	int		len;

	if (!*line || !**line)
		return (NULL);
	i = ft_checkstr(*line);
	if (i >= 0)
	{
		extract = ft_strndup(*line, i + 1);
		len = ft_strlen(*line) - (i + 1);
		if (len > 0)
			tmp = ft_strndup(*line + i + 1, len);
		else
			tmp = NULL;
		free(*line);
		*line = tmp;
		return (extract);
	}
	extract = ft_strndup(*line, ft_strlen(*line));
	free(*line);
	*line = NULL;
	return (extract);
}

char	*get_next_line(int fd)
{
	static char	*line[OPEN_MAX];
	static char	buffer[BUFFER_SIZE + 1];
	char		*tmp;
	ssize_t		bytes_read;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	while (ft_checkstr(line[fd]) < 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			if (bytes_read == 0 && line[fd])
				break ;
			free(line[fd]);
			line[fd] = NULL;
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		tmp = ft_strjoin(line[fd], buffer);
		free(line[fd]);
		line[fd] = tmp;
	}
	return (ft_extract_line(&line[fd]));
}
/*
int	main(void)
{
	int		fd;
	int		fd2;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	fd2 = open("test.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (1);
	}
	printf("%d", fd2);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
*/