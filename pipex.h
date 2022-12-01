/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 08:57:58 by aarrien-          #+#    #+#             */
/*   Updated: 2022/11/30 18:32:40 by aarrien-         ###   ########.fr       */
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

typedef struct	s_pipex
{
	int			inout_fd[2];
	char		**paths;
	char		***path_cmd;
	int			npipes;
	int			**fds;
}				t_pipex;

/*-PIPEX-*/
int		ft_pipex(t_pipex *gen);

/*-UTILS-*/
void	ft_print_struct(t_pipex *gen);
void	ft_free_split(char **split);

/*-FILL-*/
void	ft_save_paths(char **envp, t_pipex *gen);
char	*ft_cmd_path(char *cmd, t_pipex *gen);
char	**ft_prepare_exec(char *cmd, t_pipex *gen);
void	ft_fill(char **input, t_pipex *gen, int n, char **envp);

#endif
