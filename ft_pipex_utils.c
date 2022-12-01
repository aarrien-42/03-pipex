/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:34:22 by aarrien-          #+#    #+#             */
/*   Updated: 2022/11/30 19:08:25 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	ft_print_struct(t_pipex *gen)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	printf("|------------------------------|\n");
	printf("\n|INOUT_FD|\n");
	printf("infile_fd = %d\n", gen->inout_fd[0]);
	printf("outfile_fd = %d\n", gen->inout_fd[1]);
	printf("|------------------------------|\n");
	printf("\n|PATHS|\n");
	while (gen->paths[i])
	{
		printf("%s\n", gen->paths[i]);
		i++;
	}
	i = 0;
	printf("|------------------------------|\n");
	printf("\n|PATH_CMD|\n");
	while (gen->path_cmd[j])
	{
		printf("\nPath%d:\n", j);
		while (gen->path_cmd[j][i])
		{
			printf("%s\n", gen->path_cmd[j][i]);
			i++;
		}
		i = 0;
		j++;
	}
	i = 0;
	printf("|------------------------------|\n");
	printf("\n|NPIPES|\n");
	printf("%d\n", gen->npipes);
	printf("|------------------------------|\n");
	printf("\n|FDS|\n");
	while (gen->npipes - i > 0)
	{
		printf("\nPipe%d:\n", i);
		printf("%d\n", gen->fds[i][0]);
		printf("%d\n", gen->fds[i][1]);
		i++;
	}
	printf("|------------------------------|\n");
}
