/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 08:57:58 by aarrien-          #+#    #+#             */
/*   Updated: 2022/12/06 17:13:55 by aarrien-         ###   ########.fr       */
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
void	ft_first_child(t_pipex *gen);
void	ft_middle_child(t_pipex *gen, int i);
void	ft_last_child(t_pipex *gen, int i);
int		ft_pipex(t_pipex *gen);

/*-HERE_DOC-*/
char	*ft_get_line(void);
void	ft_here_doc(char *limit);

/*-UTILS-*/
int		ft_check_empty(char **argv);
void	ft_error_msg(char *s1, char *s2, t_pipex *gen);
void	ft_free_all(t_pipex *gen);
void	ft_close(t_pipex *gen, int n);
void	ft_free_split(char **split);
void	ft_print_struct(t_pipex *gen);

/*-FILL-*/
void	ft_save_paths(char **envp, t_pipex *gen);
char	*ft_cmd_path(char *cmd, t_pipex *gen);
char	**ft_prepare_exec(char *cmd, t_pipex *gen);
void	ft_fill(char **input, t_pipex *gen, int n, char **envp);

#endif
