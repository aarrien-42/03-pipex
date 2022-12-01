/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 11:59:42 by aarrien-          #+#    #+#             */
/*   Updated: 2022/12/01 18:44:59 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_first_child(t_pipex *gen)
{
	dup2(gen->fds[0][1], STDOUT_FILENO);
	ft_close(gen, gen->npipes);
	execve(gen->path_cmd[0], gen->cmds[0], NULL);
	return (0);
}

int	ft_middle_child(t_pipex *gen, int i)
{
	dup2(gen->fds[i - 1][0], STDIN_FILENO);
	dup2(gen->fds[i][1], STDOUT_FILENO);
	ft_close(gen, gen->npipes);
	execve(gen->path_cmd[i], gen->cmds[i], NULL);
	return (0);
}

int	ft_last_child(t_pipex *gen, int i)
{
	dup2(gen->fds[i - 1][0], STDIN_FILENO);
	ft_close(gen, gen->npipes);
	execve(gen->path_cmd[i], gen->cmds[i], NULL);
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

	gen.inout_fd[1] = open(argv[argc - 1], O_WRONLY | O_TRUNC);
	if (ft_strncmp(argv[1], "here_doc", 9) != 0) // no heredoc
	{
		gen.inout_fd[0] = open(argv[1], O_RDONLY);
		ft_fill(&argv[2], &gen, argc - 3, envp);
	}
	else
	{
		//ft_fill(&argv[3], &gen, argc - 4, envp);
	}
	ft_pipex(&gen);
	//ft_print_struct(&gen);
	exit(0);
}
