/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:04:30 by prosas-p          #+#    #+#             */
/*   Updated: 2024/08/01 13:20:50 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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
}	t_ite;

void	exit_error(char	*error_message);
void	null_matrix(char ***matrix);
void	free_matrix_twice(char ***matrix);
void	free_matrix(char ***matrix);
void	final_free(char ***matrix, char **str, char **str2);
void	exec_cmd(t_ite *ite, char **env);
void	dup3(int fd1, int fd2);
void	dup_error2(char *error_message, int fd, int fd2);
void	close2(int fd, int fd2);
void	free2(char ***matrix, char **str);
void	dup_error3(char *error_message, int fd, int fd2, int fd3);
void	val_args_pipex(char *comand, char **env, t_ite *ite);
int		its_empty_str(char *str);
void	close3(int fd, int fd2, int fd3);

#endif
