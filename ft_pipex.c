/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 11:59:42 by aarrien-          #+#    #+#             */
/*   Updated: 2022/12/01 10:17:42 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_pipex(t_pipex *gen)
{
	int	pid;
	int	pid1;
	int	i;

	i = 0;
	pid = fork();
	if (pid == 0)
	{
		dup2(gen->fds[0][1], STDOUT_FILENO);
		close(gen->fds[0][1]);
		close(gen->fds[0][0]);
		execve(gen->path_cmd[0][0], &gen->path_cmd[0][1], NULL);
	}
	pid1 = fork();
	if (pid1 == 0)
	{
		dup2(gen->fds[0][0], STDIN_FILENO);
		close(gen->fds[0][0]);
		close(gen->fds[0][1]);
		execve(gen->path_cmd[1][0], &gen->path_cmd[1][1], NULL);
	}
	close(gen->fds[0][1]);
	close(gen->fds[0][0]);
	printf("waiting to pid = %d\n", pid);
	waitpid(pid, NULL, 0);
	printf("waiting to pid = %d\n", pid1);
	waitpid(pid1, NULL, 0);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	gen;

	//gen.inout_fd[1] = open(argv[argc - 1], O_WRONLY | O_APPEND);
	//gen.inout_fd[0] = open(argv[1], O_RDONLY);
	ft_fill(&argv[1], &gen, argc - 1, envp);
	ft_pipex(&gen);
	ft_print_struct(&gen);
	return (0);
}
