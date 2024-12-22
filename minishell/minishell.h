/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femoreno <femoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:51:51 by prosas-p          #+#    #+#             */
/*   Updated: 2024/11/25 18:10:55 by femoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _POSIX_C_SOURCE 200809L

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <curses.h>
# include <term.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/types.h>
# include <limits.h>

# include "Libft/libft.h"

typedef struct s_cmd
{
	char	**redir;
	char	**cmd;
	int		pid;		
}	t_cmd;

typedef struct s_minis
{
	char	**p_env;
	char	**paths;
	char	*line;
	char	*begining;
	char	*cmd_route;
	char	*cd;
	char	*path_here_doc;
	char	*str_aux;
	int		status;
	int		ite;
	int		aux;
	int		n_cmd;
	int		pipefd[2];
	int		prev_pipefd[2];
	int		std_in;
	int		std_out;
	int		heredocs_c;
	pid_t	pid;
	t_cmd	*cmds;
}	t_minis;

extern int	g_sig;

int		parsing(t_minis *minis);
int		empty_str(char *str);
int		is_dif_str(char c);
int		its_true_pipe(char *line, int *i);
int		metasim(char *line, int *i, int sum, int con);
int		expand(t_minis *minis, int i, int j, char *expand);
int		clean_unnecessary(t_minis *minis, int i, int j);
int		alloc_mem(t_minis *minis, int i, int n, int aux);
int		close_quoetes(t_minis *minis, int i, char quotes);
int		replace_var(t_minis *minis, char *str);
int		bash_correct_export_arg(t_minis *minis, char *str);
int		advance_q(char *line, int *i);
int		in_quo(char *line, int *i, int sum);
int		in_dquo(char *line, int *i, int sum);
int		escaped_bslash(const char *str, int pos);
int		ft_strncmp_equal(const char *s1, const char *s2, size_t n);
int		create_heredocs(t_minis *minis);
int		create_heardocs(t_minis *minis);
int		onlyr(t_minis *minis, int comand);
int		eliminar_txt_en_carpeta(t_minis *minis);
int		close_pipes(t_minis *minis, int i);
int		check_redirs(t_minis *minis, int j);
int		first_character(t_minis *minis, int i);
int		expand_heredoc(t_minis *minis, char *line, char *expand, int i);
int		strange_character(t_minis *minis, int i);
int		check_pipes(t_minis *minis, int i);
int		its_expand(char *line, int *i);
void	advance_space_2(char *str, int *i, int *j);
void	handle_sigint(int sig);
void	bash_pwd(t_minis *minis);
void	free_exit(t_minis *minis);
void	close2(int *fd, int *fd2);
void	free_change_p(char **str, char **new_str, int *z, int *i);
void	builts_off(t_minis *minis, int j);
void	free_matrix_twice(char **matrix);
void	change_int(int *i1, int *i2, int v1, int v2);
void	add2(t_minis *minis, int red, int *lp, int *i2);
void	free_minis_cmds(t_minis *minis);
void	free2(char **str, char **str2);
void	print_comads(t_minis *minis);
void	advance_space(char *str, int *i);
void	add_null(char *c1, char *c2);
void	bash_echo(t_minis *minis, char **line);
void	bash_env(t_minis *minis);
void	bash_exit(t_minis *minis, char **argv);
void	bash_export(t_minis *minis, char **str);
void	append_var(t_minis *minis, char *str);
void	add_var(t_minis *minis, char *str, int i);
int		add_var2(t_minis *minis, char **name, int *i, int z);
void	bash_unset(t_minis *minis, char **str);
void	bash_cd(t_minis *minis, char **str, int i, char *s);
void	decide_start_point(t_minis *minis, int *aux);
void	str_message(t_minis *minis, char *s1, char *s2, char *s3);
void	reopen_fd(void);
void	advance_to_dollar(char	*str, int *aux);
void	signal_cd_heredoc(char *name, int i);
void	handle_sigint(int sig);
void	handle_sigint2(int sig);
void	signal_quit_children(int sig);
void	ms_setsignalson(void);
void	ms_setsignals(void);
void	ms_setsignalhere(void);
void	ms_setsignal2(void);
void	signal_cd_pipes(void);
void	free_final(t_minis *minis);
void	advance_str(char *str, char c, int *i);
void	handle_sigint3(int sig);
int		isnt_space(t_minis *minis);
int		decide_cmd(t_minis *minis, int j);
void	signal_cd_quotes(char quotes);
int		check_orders(t_minis *minis, int j, int i);
int		null_expand2(t_minis *minis, char **nl, int j, int aux);
int		null_expand2_h(t_minis *minis, char **nl, int j, int aux);
void	set_status(t_minis *minis, char *error, int status);
char	**find_path(char **env);
char	**copymatriz(t_minis *minis, int n);

#endif
