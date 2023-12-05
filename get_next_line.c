/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:22:33 by yabejani          #+#    #+#             */
/*   Updated: 2023/12/05 15:03:55 by yabejani         ###   ########.fr       */
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
	if (!save)
	{
		save = malloc(sizeof(char) * 1);
		if (!save)
			return (NULL);
		save[0] = '\0';
	}
	while (!ft_strchr(save, '\n') && readbytes != 0)
	{
		readbytes = read(fd, tmp, BUFFER_SIZE);
		if (readbytes == -1)
			return (free(tmp), free(save), NULL);
		tmp[readbytes] = '\0';
		save = ft_strjoin(save, tmp);
	}
	return (free(tmp), save);
}

char	*ft_get_line(char *save)
{
	char	*line;
	int		i;

	i = 0;
	if (!save)
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i] == '\n')
	{
		line = ft_strndup(save, i + 1);
		i++;
	}
	else
		line = ft_strndup(save, i);
	return (line);
}

char	*ft_clean_save(char *save)
{
	int		i;
	int		len;
	char	*newsave;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	len = ft_strlen(save);
	if (!save[i])
		return (free(save), NULL);
	newsave = ft_strndup((save + i + 1), (len - i));
	if (newsave)
		free(save);
	return (newsave);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

	line = NULL;
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	save = ft_read(fd, save);
	if (!save || save[0] == 0)
	{
		free(save);
		save = NULL;
		return (NULL);
	}
	line = ft_get_line(save);
	if (!line || line[0] == 0)
		return (free(line), free(save), NULL);
	save = ft_clean_save(save);
	if (save && save[0] == 0)
	{
		free(save);
		save = NULL;
	}
	return (line);
}

// #include <fcntl.h>
// #include <stdio.h>

// int	main(void)
// {
// 	int		fd;
// 	char	*str;

// 	fd = open("tests/test.txt", O_RDONLY);
// 	while ((str = get_next_line(fd)))
// 	{
// 		printf("%s", str);
// 		free(str);
// 	}
// 	close(fd);
// 	free(str);
// }
