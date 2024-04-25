/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrodrigu <yrodrigu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 20:36:20 by yrodrigu          #+#    #+#             */
/*   Updated: 2024/04/03 18:12:35 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line_bonus.h"

char	*multiple_free(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
	return (NULL);
}

static char	*fd_lector(int fd, char *buff, char *saved_text)
{
	ssize_t	bytes;
	char	*temp;

	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == -1)
			return (multiple_free(&saved_text));
		if (bytes == 0)
			break ;
		buff[bytes] = '\0';
		if (!saved_text)
			saved_text = ft_strdup("");
		if (!saved_text)
			return (multiple_free(&saved_text));
		temp = saved_text;
		saved_text = ft_strjoin(temp, buff);
		free (temp);
		temp = NULL;
		if (ft_strchr(buff, '\n'))
			break ;
	}
	return (saved_text);
}

static char	*ft_line_remover(char *line)
{
	size_t	count;
	char	*saved_text;
	size_t	i;

	i = 0;
	count = 0;
	while (line[count] != '\n' && line[count] != '\0')
		count++;
	if (line[count] == '\0')
		return (0);
	saved_text = ft_substr(line, count + 1, ft_strlen(line) - (count + 1));
	if (!saved_text)
		return (multiple_free(&saved_text));
	if (*saved_text == '\0')
	{
		free(saved_text);
		saved_text = NULL;
	}
	line[count + 1] = '\0';
	return (saved_text);
}

char	*get_next_line(int fd)
{
	char		*buff;
	static char	*saved_text[OPEN_MAX];
	char		*line;
	char		*tmp;

	if (fd == -1 || BUFFER_SIZE <= 0 || fd >= OPEN_MAX)
		return (0);
	buff = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	line = fd_lector(fd, buff, saved_text[fd]);
	free(buff);
	buff = NULL;
	if (!line)
	{
		saved_text[fd] = NULL;
		return (NULL);
	}
	saved_text[fd] = ft_line_remover(line);
	tmp = ft_strdup(line);
	free(line);
	line = tmp;
	if (!line)
		return (multiple_free(&saved_text[fd]));
	return (line);
}
