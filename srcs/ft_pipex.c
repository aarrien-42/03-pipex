/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 11:59:42 by aarrien-          #+#    #+#             */
/*   Updated: 2022/12/06 17:13:19 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_first_child(t_pipex *gen)
{
	dup2(gen->fds[0][1], STDOUT_FILENO);
	ft_close(gen, gen->npipes);
	if (gen->path_cmd[0] && gen->cmds[0])
		execve(gen->path_cmd[0], gen->cmds[0], NULL);
	ft_error_msg("zsh: command not found: ", gen->cmds[0][0], gen);
}

void	ft_middle_child(t_pipex *gen, int i)
{
	dup2(gen->fds[i - 1][0], STDIN_FILENO);
	dup2(gen->fds[i][1], STDOUT_FILENO);
	ft_close(gen, gen->npipes);
	if (gen->path_cmd[i] && gen->cmds[i])
		execve(gen->path_cmd[i], gen->cmds[i], NULL);
	ft_error_msg("zsh: command not found: ", gen->cmds[i][0], gen);
}

void	ft_last_child(t_pipex *gen, int i)
{
	dup2(gen->fds[i - 1][0], STDIN_FILENO);
	ft_close(gen, gen->npipes);
	if (gen->path_cmd[i] && gen->cmds[i])
		execve(gen->path_cmd[i], gen->cmds[i], NULL);
	ft_error_msg("zsh: command not found: ", gen->cmds[i][0], gen);
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

int	main(int argc, char **argv, char **envp)
{
	t_pipex	gen;

	if (ft_check_empty(argv) != 0)
		return (ft_putstr_fd("empty argument\n", 2), 0);
	gen.inout_fd[1] = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (ft_strncmp(argv[1], "here_doc", 9) != 0)
	{
		if (argc - 3 <= 1)
			return (ft_putstr_fd("too few commands\n", 2), 0);
		gen.inout_fd[0] = open(argv[1], O_RDONLY);
		ft_fill(&argv[2], &gen, argc - 3, envp);
	}
	else
	{
		if (argc - 4 <= 1)
			return (ft_putstr_fd("too few commands\n", 2), 0);
		ft_here_doc(argv[2]);
		gen.inout_fd[0] = open(".temp.txt", O_RDONLY);
		ft_fill(&argv[3], &gen, argc - 4, envp);
	}
	ft_pipex(&gen);
	unlink(".temp.txt");
	//ft_print_struct(&gen);
	ft_free_all(&gen);
}
