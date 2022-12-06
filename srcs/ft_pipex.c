/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 11:59:42 by aarrien-          #+#    #+#             */
/*   Updated: 2022/12/05 12:44:35 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_first_child(t_pipex *gen)
{
	dup2(gen->fds[0][1], STDOUT_FILENO);
	ft_close(gen, gen->npipes);
	if (execve(gen->path_cmd[0], gen->cmds[0], NULL) == -1)
		ft_error_msg("zsh: command not found: ", gen->cmds[0][0]);
	return (0);
}

int	ft_middle_child(t_pipex *gen, int i)
{
	dup2(gen->fds[i - 1][0], STDIN_FILENO);
	dup2(gen->fds[i][1], STDOUT_FILENO);
	ft_close(gen, gen->npipes);
	if (execve(gen->path_cmd[i], gen->cmds[i], NULL) == -1)
		ft_error_msg("zsh: command not found: ", gen->cmds[i][0]);
	return (0);
}

int	ft_last_child(t_pipex *gen, int i)
{
	dup2(gen->fds[i - 1][0], STDIN_FILENO);
	ft_close(gen, gen->npipes);
	if (execve(gen->path_cmd[i], gen->cmds[i], NULL) == -1)
		ft_error_msg("zsh: command not found: ", gen->cmds[i][0]);
	return (0);
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

	if (argc < 4)
		exit(0);
	gen.inout_fd[1] = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (ft_strncmp(argv[1], "here_doc", 9) != 0)
	{
		gen.inout_fd[0] = open(argv[1], O_RDONLY);
		ft_fill(&argv[2], &gen, argc - 3, envp);
	}
	else
	{
		ft_here_doc(argv[2]);
		gen.inout_fd[0] = open(".temp.txt", O_RDONLY);
		ft_fill(&argv[3], &gen, argc - 4, envp);
	}
	if (ft_check(&gen, argv) != 0)
		exit(0);
	ft_pipex(&gen);
	unlink(".temp.txt");
	//ft_print_struct(&gen);
	exit(0);
}
