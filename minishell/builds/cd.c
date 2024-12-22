/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femoreno <femoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:48:56 by femoreno          #+#    #+#             */
/*   Updated: 2024/11/25 17:00:09 by femoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	str_message(t_minis *minis, char *s1, char *s2, char *s3)
{
	char	*str1;
	char	*str2;
	int		status;

	status = 1;
	str1 = ft_strjoin(s1, s2);
	str2 = ft_strjoin(str1, s3);
	if (ft_strnstr(s1, "redir", strlen(s1)) != 0)
		status = 2;
	set_status(minis, str2, status);
	free (str1);
	free (str2);
}

int	change_oldpwd(t_minis *minis, int i)
{
	char	*aux;
	char	*aux2;

	while (minis->p_env[++i] != NULL)
	{
		if (ft_strncmp(minis->p_env[i], "OLDPWD",
				ft_strlenc(minis->p_env[i], '=')) == 0)
		{
			aux2 = getcwd(NULL, 0);
			if (!aux2)
				return (free(aux2), 1);
			aux = ft_strjoin("OLDPWD=", aux2);
			free(aux2);
			free(minis->p_env[i]);
			if (!aux)
				return (1);
			minis->p_env[i] = aux;
		}
	}
	return (0);
}

int	change_dir(t_minis *minis, char *str, int i)
{
	char	*aux;
	char	*aux2;

	change_oldpwd(minis, i);
	if (chdir(str) != 0)
		return (str_message(minis, "cd: ", str,
				": No such file or directory\n"), 1);
	while (minis->p_env[++i] != NULL)
	{
		if (ft_strncmp(minis->p_env[i], "PWD",
				ft_strlenc(minis->p_env[i], '=')) == 0)
		{
			aux2 = getcwd(NULL, 0);
			if (!aux2)
				return (set_status(minis, "liberror aux2\n", 1), 1);
			aux = ft_strjoin("PWD=", aux2);
			if (!aux)
				return (free(aux2), set_status(minis, "liberror aux\n", 1), 1);
			free(minis->p_env[i]);
			free(aux2);
			minis->p_env[i] = aux;
		}
	}
	return (0);
}

void	bash_cd(t_minis *minis, char **str, int i, char *s)
{
	if (str[1] && str[2])
		return (set_status(minis, "cd: too many arguments\n", 1));
	else
	{
		if (!str[1])
		{
			while (minis->p_env[++i])
			{
				if (ft_strncmp("HOME=", minis->p_env[i], 5) == 0)
				{
					s = ft_substr(minis->p_env[i], 5,
							(ft_strlen(minis->p_env[i])));
					break ;
				}
			}
			if (!s)
				return (set_status(minis, "HOME not set\n", 1));
			if (change_dir(minis, s, -1) != 0)
				return (free(s));
			free(s);
		}
		else
			change_dir(minis, str[1], -1);
	}
}
