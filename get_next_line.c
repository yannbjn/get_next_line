/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:22:33 by yabejani          #+#    #+#             */
/*   Updated: 2023/12/04 11:24:14 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read(int fd, char *save)
{
	char	*tmp;
	int		readbytes;

	tmp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!tmp)
		return (NULL);
	readbytes = 1;
	while (!ft_strchr(save, '\n') && readbytes != 0)
	{
		readbytes = read(fd, tmp, BUFFER_SIZE);
		if (readbytes == -1)
		{
			free(tmp);
			tmp = NULL;
			return (NULL);
		}
		tmp[readbytes] = '\0';
		save = ft_strjoin(save, tmp);
	}
	free(tmp);
	return (save);
}

char	*ft_get_line(char *save)
{
	char	*line;
	int		i;

	i = 0;
	if (!save[i])
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		line[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
	{
		line[i] = save[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_clean_save(char *save)
{
	char	*newsave;
	int		i;
	int		j;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	newsave = malloc(sizeof(char) * (ft_strlen(save) - i + 1));
	if (!newsave)
	{
		free(newsave);
		return (NULL);
	}
	i++;
	j = 0;
	while (save[i])
		newsave[j++] = save[i++];
	newsave[j] = '\0';
	free(save);
	return (newsave);
}

#include <stdio.h>

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (0);
	save = ft_read(fd, save);
	printf("SAVE de ft_read :%s", save);
	if (!save)
		return (NULL);
	line = ft_get_line(save);
	if (!line || line[0] == 0)
	{
		free(line);
		return (NULL);
	}
	printf("LINE de get line :%s", line);
	save = ft_clean_save(save);
	if (!save || save[0] == 0)
		{
			free(save);
			save = NULL;
		}
	printf("SAVE de clean save :%s", save);
	return (line);
}

#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	char	*line;
	int	fd1;
	int	i;

	fd1 = open("tests/test.txt", O_RDONLY);
	i = 1;
	while (i < 6)
	{
		line = get_next_line(fd1);
		printf("line %d :%s", i, line);
		free(line);
		i++;
	}
	close(fd1);
	return (0);
}
