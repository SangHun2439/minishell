/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeson <jeson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 10:20:57 by jeson             #+#    #+#             */
/*   Updated: 2022/01/20 22:54:28 by jeson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd_err(int error, char *dir)
{
	ft_putstr_fd("cd: ", STDERR_FILENO);
	ft_putstr_fd(dir, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(error), STDERR_FILENO);
}

int	length_to_equ(const char *str)
{
	size_t	i;
	int		cnt;

	i = 0;
	cnt = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

char	*cut_val(char *str)
{
	char	*env_val;
	int		len_equ;
	int		len;

	len = ft_strlen(str);
	len_equ = length_to_equ(str);
	if (len - len_equ == 1)
		return (ft_strdup(""));
	env_val = ft_strndup(&str[len_equ + 1], (len - len_equ - 1));
	return (env_val);
}

void	env_overriding(char *str, int *cnt)
{
	t_list	*env_list;
	t_env	*env;
	char	*str_key;

	if (*cnt == 0)
		return ;
	env_list = g_vars.env_list;
	str_key = ft_strndup(str, length_to_equ(str));
	while (env_list)
	{
		env = env_list->content;
		if (!ft_strcmp(env->key, str_key))
		{
			free(env->val);
			env->val = cut_val(str);
		}
		env->flag = 0;
		env_list = env_list->next;
	}
	free(str_key);
}

void	export_no_parm(void)
{
	t_list	*env_list;
	t_env	*env;

	env_list = g_vars.env_list;
	while (env_list)
	{
		env = env_list->content;
		if (env->flag == 0)
			printf("declare -x %s=\"%s\"\n", env->key, env->val);
		else if (env->flag == 1)
			printf("declare -x %s\n", env->key);
		env_list = env_list->next;
	}
}
