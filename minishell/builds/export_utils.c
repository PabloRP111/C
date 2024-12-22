/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femoreno <femoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:19:28 by femoreno          #+#    #+#             */
/*   Updated: 2024/11/25 18:10:28 by femoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	bash_correct_export_arg(t_minis *minis, char *str)
{
	int	i;

	if (!str || !str[0])
		return (2);
	if (!ft_isalpha(str[0]) && str[0] != '_')
	{
		str_message(minis, "export: `", str, "': not a valid identifier\n");
		return (2);
	}
	i = 0;
	while (str[++i] && str[i] != '=')
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_'
			&& (str[i] != '+' || (str[i] == '+' && str[i + 1] != '=')))
		{
			str_message(minis, "export: `", str, "': not a valid identifier\n");
			return (2);
		}
	}
	if (str[i - 1] == '+' && str[i] == '=')
		return (0);
	return (1);
}

int	replace_var(t_minis *minis, char *str)
{
	int	i;
	int	j;
	int	z;

	change_int(&i, &j, -1, -1);
	while (str[++i] && str[i] != '=')
		if (str[i] != '=' && str[i + 1] == '\0')
			return (1);
	z = i;
	while (minis->p_env[++j])
	{
		if ((int)ft_strlenc(minis->p_env[j], '=') >= i)
			z = ft_strlenc(minis->p_env[j], '=');
		if (ft_strncmp(minis->p_env[j], str, z) == 0)
			break ;
		if (!minis->p_env[j + 1])
			return (1);
		z = i;
	}
	free(minis->p_env[j]);
	minis->p_env[j] = ft_strdup(str);
	return (0);
}

void	add_var(t_minis *minis, char *str, int i)
{
	int		z;
	char	**dup;
	char	*name;

	while (str[++i] != '=' && str[i] != '\0')
		;
	name = ft_substr(str, 0, i);
	if (!name)
		return ;
	change_int(&i, &z, -1, ft_strlen(name));
	if (add_var2(minis, &name, &i, z) != 0)
		return ;
	dup = malloc(sizeof(char *) * (i + 2));
	i = -1;
	while (minis->p_env[++i])
		dup[i] = minis->p_env[i];
	dup[i++] = ft_strdup(str);
	dup[i] = NULL;
	free(minis->p_env);
	minis->p_env = dup;
}

void	append_to_add(t_minis *minis, char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] != '+')
		i++;
	while (str[i])
	{
		str[i] = str[i + 1];
		i++;
	}
	str[i] = '\0';
	if (replace_var(minis, str) == 1)
		add_var(minis, str, -1);
}

void	append_var(t_minis *minis, char *str)
{
	int		i;
	int		j;
	char	*s;

	change_int(&i, &j, 0, 0);
	while (str[i] && str[i] != '+')
		i++;
	i++;
	while (ft_strncmp(str, minis->p_env[j], i) != -18)
	{
		if (!minis->p_env[j + 1])
		{
			append_to_add(minis, str);
			return ;
		}
		j++;
	}
	i = 0;
	while (str[i] != '=')
		i++;
	i++;
	s = ft_strjoin(minis->p_env[j], ft_substr(str, i, (ft_strlen(str) - i)));
	free(minis->p_env[j]);
	minis->p_env[j] = s;
}
