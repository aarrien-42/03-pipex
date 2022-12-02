/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 12:58:12 by aarrien-          #+#    #+#             */
/*   Updated: 2022/12/02 18:44:15 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_get_line()
{
	char	c;
	char	*str;
	char	*tmp;
	char	*aux;

	str = malloc(1 * sizeof(char));
	str[0] = 0;
	while (read(0, &c, 1) && c != '\n')
	{
		aux = str;
		tmp = malloc(2 * sizeof(char));
		tmp[0] = c;
		tmp[1] = 0;
		str = ft_strjoin(str, tmp);
		free(tmp);
		free(aux);
	}
	return (str);
}

void	ft_here_doc(char *limit)
{
	int		fd;
	char	*line;
	size_t	limit_len;

	limit_len = ft_strlen(limit);
	fd = open("temp.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	while (1)
	{
		line = ft_get_line();
		if (ft_strncmp(line, limit, limit_len + 1) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	close(fd);
	//unlink("temp.txt");
}
