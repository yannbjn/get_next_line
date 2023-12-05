/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:30:15 by yabejani          #+#    #+#             */
/*   Updated: 2023/12/05 16:41:40 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
		line = ft_strndup(save, i + 1);
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
	static char	*save[4095];
	char		*line;

	line = NULL;
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	save[fd] = ft_read(fd, save[fd]);
	if (!save[fd] || save[fd][0] == 0)
	{
		free(save[fd]);
		save[fd] = NULL;
		return (NULL);
	}
	line = ft_get_line(save[fd]);
	if (!line || line[0] == 0)
		return (free(line), free(save[fd]), NULL);
	save[fd] = ft_clean_save(save[fd]);
	if (save[fd] && save[fd][0] == 0)
	{
		free(save[fd]);
		save[fd] = NULL;
	}
	return (line);
}

// #include <fcntl.h>
// #include <stdio.h>

// int	main(void)
// {
// 	char	*line;
// 	int		fd1;
// 	int		fd2;
// 	int		fd3;
// 	int		i;

// 	fd1 = open("tests/test.txt", O_RDONLY);
// 	fd2 = open("tests/test2.txt", O_RDONLY);
// 	fd3 = open("tests/bible.txt", O_RDONLY);
// 	i = 1;
// 	while (i < 100183)
// 	{
// 		line = get_next_line(fd1);
// 		printf("line %d :%s", i, line);
// 		free(line);
// 		line = get_next_line(fd2);
// 		printf("line %d :%s", i, line);
// 		free(line);
// 		line = get_next_line(fd3);
// 		printf("line %d :%s", i, line);
// 		free(line);
// 		i++;
// 	}
// 	close(fd1);
// 	close(fd2);
// 	close(fd3);
// 	return (0);
//  }
// #include <stdio.h>
// #include <fcntl.h>
// int    main(int ac, char **av) {
//     int fd = open(av[1], O_RDONLY);
//     char *str;
//     (void)ac;

//     while ((str = get_next_line(fd))) {
//         printf("%s", str);
//         free(str);
//     }
//     free(str);
// }
