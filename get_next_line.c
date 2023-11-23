/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:22:33 by yabejani          #+#    #+#             */
/*   Updated: 2023/11/22 15:32:33 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_and_save(int fd, char *save)
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

char	*ft_del_firstline(char *save)
{
	char	*str;
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
	str = malloc(sizeof(char) * (ft_strlen(save) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (save[i])
		str[j++] = save[i++];
	str[j] = '\0';
	free(save);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (0);
	save = ft_read_and_save(fd, save);
	if (!save)
		return (NULL);
	line = ft_get_line(save);
	printf(" printf save de get line %s \n", save);
	printf(" printf line de get line %s \n", line);
	save = ft_del_firstline(save);
	printf(" printf de del first line %s \n", save);
	printf(" printf line de del first line %s \n", line);
	return (line);
}

#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	char	*line1;
	char	*line2;
	char	*line3;
	char	*line4;
	char	*line5;
	char	*line6;
	int		fd1;
	
	fd1 = open("tests/test.txt", O_RDONLY);
	line1 = get_next_line(fd1);
	printf("line 1 ; %s", line1);
	free(line1);
	
	line2 = get_next_line(fd1);
	printf("line 2 ; %s", line2);
	free(line2);
	
	line3 = get_next_line(fd1);
	printf("line 3 ; %s", line3);
	free(line3);
	
	line4 = get_next_line(fd1);
	printf("line 4 ; %s", line4);
	free(line4);
	
	line5 = get_next_line(fd1);
	printf("line 5 ; %s", line5);
	free(line5);
	
	line6 = get_next_line(fd1);
	printf("line 6 ; %s", line6);
	free(line6);
	
	close(fd1);
	return (0);
}
