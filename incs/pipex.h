/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 08:57:58 by aarrien-          #+#    #+#             */
/*   Updated: 2022/12/01 16:27:52 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include "libft.h"

typedef struct s_pipex
{
	int			inout_fd[2];
	char		**paths;
	char		**path_cmd;
	char		***cmds;
	int			npipes;
	int			**fds;
}				t_pipex;

/*-PIPEX-*/
int		ft_first_child(t_pipex *gen);
int		ft_middle_child(t_pipex *gen, int i);
int		ft_last_child(t_pipex *gen, int i);
int		ft_pipex(t_pipex *gen);

/*-UTILS-*/
void	ft_free_all(t_pipex *gen);
int		ft_check(t_pipex *gen);
void	ft_close(t_pipex *gen, int n);
void	ft_free_split(char **split);
void	ft_print_struct(t_pipex *gen);

/*-FILL-*/
void	ft_save_paths(char **envp, t_pipex *gen);
char	*ft_cmd_path(char *cmd, t_pipex *gen);
char	**ft_prepare_exec(char *cmd, t_pipex *gen);
void	ft_fill(char **input, t_pipex *gen, int n, char **envp);

#endif
