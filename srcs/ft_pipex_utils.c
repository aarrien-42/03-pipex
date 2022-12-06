/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:34:22 by aarrien-          #+#    #+#             */
/*   Updated: 2022/12/06 11:38:20 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_all(t_pipex *gen)
{
	int	i;

	i = 0;
	ft_free_split(gen->paths);
	while (i < gen->npipes)
	{
		if (gen->path_cmd[i] != NULL)
			free(gen->path_cmd[i]);
		i++;
	}
	free(gen->path_cmd);
	i = 0;
	while (gen->cmds[i])
	{
		ft_free_split(gen->cmds[i]);
		i++;
	}
	free(gen->cmds);
	exit(0);
}

void	ft_error_msg(char *s1, char *s2)
{
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(s2, 2);
	ft_putstr_fd("\n", 2);
	exit(0);
}

int	ft_check(t_pipex *gen, char **argv)
{
	int	i;

	i = 0;
	if (gen->inout_fd[0] == -1)
		ft_error_msg("zsh: no such file or directory: ", argv[1]);
	if (gen->npipes <= 0)
		return (write(2, "comandos insuficientes\n", 24), 2);
	while (i < gen->npipes)
	{
		if (gen->path_cmd[i] == NULL)
			ft_error_msg("zsh: command not found: ", gen->cmds[i][0]);
		i++;
	}
	return (0);
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
