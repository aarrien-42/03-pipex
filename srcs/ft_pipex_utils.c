/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:34:22 by aarrien-          #+#    #+#             */
/*   Updated: 2022/12/08 14:12:45 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_check(char **av, int ac)
{
	int		i;

	i = 0;
	if (ac == 1)
		return (ft_putstr_fd("no arguments supplied\n", 2), 1);
	while (av[i])
	{
		if (*av[i] == 0)
			return (ft_putstr_fd("empty argument\n", 2), 1);
		i++;
	}
	return (0);
}

void	ft_free_all(t_pipex *gen, int code)
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
	unlink(".temp.txt");
	exit(code);
}

void	ft_error_msg(char *s1, char *s2, t_pipex *gen, int code)
{
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(s2, 2);
	ft_putstr_fd("\n", 2);
	if (gen->paths[0] != 0)
		ft_free_all(gen, code);
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
