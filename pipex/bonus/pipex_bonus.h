/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:04:30 by prosas-p          #+#    #+#             */
/*   Updated: 2024/08/01 12:01:56 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../LIBDEF/libdef.h"
# include <sys/types.h>
# include <unistd.h>
# include <sys/wait.h>

typedef struct s_ite
{
	int		i;
	int		argc;
	int		fd_in;
	int		fd_out;
	char	*actual_r;
	char	**cmd_args;
	char	**env;
	char	*eof;
}	t_ite;

void	exit_error(char	*error_message);
void	null_matrix(char ***matrix);
void	free_matrix_twice(char ***matrix);
void	free_matrix(char ***matrix);
void	final_free(char ***matrix, char **str, char **str2);
void	exec_cmd(t_ite *ite, char **env);
void	dup_error2(char *error_message, int fd, int fd2);
void	close2(int fd, int fd2);
void	close3(int fd, int fd2, int fd3);
void	free2(char ***matrix, char **str);
void	dup_error3(char *error_message, int fd, int fd2, int fd3);
void	val_args_pipex(char *comand, char **env, t_ite *ite);
void	is_here_doc(char **argv, t_ite *ite, char **env);
int		its_empty_str(char *str);

#endif
