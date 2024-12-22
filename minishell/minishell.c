/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:51:29 by prosas-p          #+#    #+#             */
/*   Updated: 2024/11/24 17:59:51 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig = 0;

char	*get_beginnig(t_minis *minis)
{
	char	*begin;
	int		i;
	int		slash;

	minis->cd = getcwd(NULL, 0);
	if (!minis->cd)
		return (NULL);
	slash = 0;
	i = -1;
	while (minis->cd[++i])
		if (minis->cd[i] == '/')
			slash++;
	i = -1;
	while (slash >= 2)
	{
		if (minis->cd[++i] == '/')
			slash--;
	}
	begin = ft_strjoin(&minis->cd[i], "$ ");
	free(minis->cd);
	return (begin);
}

int	init_vals2(t_minis *minis, char **env, int i, char *aux)
{
	if (!(*env))
		i = 3;
	else
		while (env[i] != NULL)
			i++;
	minis->p_env = ft_calloc(i + 1, sizeof(char *));
	if (!minis->p_env)
		return (1);
	i = -1;
	if (*env)
	{
		while (env[++i] != NULL)
			minis->p_env[i] = ft_strdup(env[i]);
		minis->p_env[i] = NULL;
	}
	else
	{
		minis->p_env[0] = ft_strdup("SHLVL=2");
		minis->p_env[1] = ft_strdup("OLDPWD");
		aux = ft_strjoin("PWD=", minis->path_here_doc);
		minis->p_env[2] = aux;
	}
	return (0);
}

int	init_vals(t_minis *minis, char **env, int j, int i)
{
	minis->path_here_doc = getcwd(NULL, 0);
	if (!minis->path_here_doc)
		return (1);
	if (init_vals2(minis, env, 0, NULL) != 0)
		return (1);
	if (!minis->p_env)
		return (1);
	change_int(&i, &j, 0, 0);
	while (*env && minis->p_env[i++] != NULL)
	{
		if (ft_strncmp(minis->p_env[i], "SHLVL=", 6) == 0)
		{
			j = ft_strlen(minis->p_env[i]) - 6;
			minis->str_aux = ft_substr(minis->p_env[i], 6, j);
			j = ft_atoi(minis->str_aux) + 1;
			free2(&minis->p_env[i], &minis->str_aux);
			minis->str_aux = ft_itoa(j);
			minis->p_env[i] = ft_strjoin("SHLVL=", minis->str_aux);
			free(minis->str_aux);
			break ;
		}
	}
	return (0);
}

void	shell_cicle(t_minis *minis)
{
	if (minis->line != NULL && isnt_space(minis) == 0)
		add_history(minis->line);
	if (g_sig != 0)
		minis->status = 128 + g_sig;
	if (minis->line != NULL && parsing(minis) == 0)
		decide_cmd(minis, 0);
	if (minis->cmds)
		free_minis_cmds(minis);
	eliminar_txt_en_carpeta(minis);
	g_sig = 0;
}

int	main(int argc, char **argv, char **env)
{
	t_minis	minis;

	if (argc != 1 || !argv)
		return (1);
	ft_memset(&minis, 0, sizeof(t_minis));
	if (init_vals(&minis, env, 0, 0) != 0)
		return (1);
	while (1)
	{
		ms_setsignals();
		minis.begining = get_beginnig(&minis);
		minis.line = readline(minis.begining);
		if (minis.begining)
			free(minis.begining);
		minis.begining = NULL;
		if (minis.line == NULL && printf("exit\n") == 5)
			break ;
		ms_setsignal2();
		shell_cicle(&minis);
		free(minis.line);
	}
	free_final(&minis);
}
