/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:34:22 by aarrien-          #+#    #+#             */
/*   Updated: 2022/12/06 17:13:22 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_check_empty(char **argv)
{
	int		i;

	i = 0;
	while (argv[i])
	{
		if (*argv[i] == 0)
			return (1);
		i++;
	}
	return (0);
}

void	ft_free_all(t_pipex *gen)
{
	int	i;

	i = 0;
	ft_free_split(gen->paths);
	while (i < gen->npipes + 1)
	{
		if (gen->path_cmd[i])
			free(gen->path_cmd[i]);
		i++;
	}
	free(gen->path_cmd);
	i = 0;
	while (gen->cmds[i])
		ft_free_split(gen->cmds[i++]);
	free(gen->cmds);
	i = 0;
	while (gen->npipes - i > 0)
		free(gen->fds[i++]);
	free(gen->fds);
	exit(0);
}

void	ft_error_msg(char *s1, char *s2, t_pipex *gen)
{
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(s2, 2);
	ft_putstr_fd("\n", 2);
	printf("gen->paths[1] = %s\n\n", gen->paths[1]);
	if (gen->paths[1] != 0 && gen->cmds)
		ft_free_all(gen);
}

void	ft_close(t_pipex *gen, int n)
{
	int	i;

	i = 0;
	while (n - i > 0)
	{
		close(gen->fds[i][0]);
		close(gen->fds[i][1]);
		i++;
	}
}

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
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
	printf("gen->inout_fd[0] = %d\n", gen->inout_fd[0]);
	printf("gen->inout_fd[1] = %d\n", gen->inout_fd[1]);
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
	while (gen->path_cmd[i])
	{
		printf("Path%d:\n", i);
		printf("%s\n", gen->path_cmd[i]);
		i++;
	}
	i = 0;
	printf("|------------------------------|\n");
	printf("\n|CMDS|\n");
	while (gen->cmds[i])
	{
		printf("Comand%d:\n", i);
		while (gen->cmds[i][j])
		{
			printf("%s\n", gen->cmds[i][j]);
			j++;
		}
		j = 0;
		i++;
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
