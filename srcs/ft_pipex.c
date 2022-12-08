/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 11:59:42 by aarrien-          #+#    #+#             */
/*   Updated: 2022/12/08 13:50:15 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_first_child(t_pipex *gen)
{
	int	status;

	status = 0;
	dup2(gen->fds[0][1], STDOUT_FILENO);
	ft_close(gen, gen->npipes);
	if (gen->path_cmd[0] && gen->cmds[0])
		status = execve(gen->path_cmd[0], gen->cmds[0], NULL);
	ft_error_msg("zsh: command not found: ", gen->cmds[0][0], gen, status);
}

void	ft_middle_child(t_pipex *gen, int i)
{
	int	status;

	status = 0;
	dup2(gen->fds[i - 1][0], STDIN_FILENO);
	dup2(gen->fds[i][1], STDOUT_FILENO);
	ft_close(gen, gen->npipes);
	if (gen->path_cmd[i] && gen->cmds[i])
		status = execve(gen->path_cmd[i], gen->cmds[i], NULL);
	ft_error_msg("zsh: command not found: ", gen->cmds[i][0], gen, status);
}

void	ft_last_child(t_pipex *gen, int i)
{
	int	status;

	status = 0;
	dup2(gen->fds[i - 1][0], STDIN_FILENO);
	ft_close(gen, gen->npipes);
	if (gen->path_cmd[i] && gen->cmds[i])
		status = execve(gen->path_cmd[i], gen->cmds[i], NULL);
	ft_error_msg("zsh: command not found: ", gen->cmds[i][0], gen, status);
}

int	ft_pipex(t_pipex *gen)
{
	int	pid;
	int	i;

	i = 0;
	dup2(gen->inout_fd[0], STDIN_FILENO);
	dup2(gen->inout_fd[1], STDOUT_FILENO);
	close(gen->inout_fd[0]);
	close(gen->inout_fd[1]);
	while (gen->npipes - i + 1 > 0)
	{
		pid = fork();
		if (pid == 0)
		{
			if (i == 0)
				ft_first_child(gen);
			else if (i == gen->npipes)
				ft_last_child(gen, i);
			else
				ft_middle_child(gen, i);
		}
		ft_close(gen, i);
		waitpid(pid, NULL, 0);
		i++;
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	gen;

	if (ft_check(av, ac) == 1)
		return (1);
	if (ft_strncmp(av[1], "here_doc", 9) != 0)
	{
		if (ac - 3 <= 1)
			return (ft_putstr_fd("too few commands\n", 2), 2);
		gen.inout_fd[1] = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		gen.inout_fd[0] = open(av[1], O_RDONLY);
		ft_fill(&av[2], &gen, ac - 3, envp);
	}
	else
	{
		if (ac - 4 <= 1)
			return (ft_putstr_fd("too few commands\n", 2), 2);
		ft_here_doc(av[2]);
		gen.inout_fd[1] = open(av[ac - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
		gen.inout_fd[0] = open(".temp.txt", O_RDONLY);
		ft_fill(&av[3], &gen, ac - 4, envp);
	}
	ft_check_files(av, ac, &gen);
	ft_pipex(&gen);
	ft_free_all(&gen, 0);
}
