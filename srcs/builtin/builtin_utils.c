/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 10:20:57 by jeson             #+#    #+#             */
/*   Updated: 2022/01/19 15:50:28 by jeson            ###   ########.fr       */
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

int	length_to_equ(const char *s1)
{
	size_t	len;

	len = 0;
	while (s1[len] && s1[len] != '=')
		len++;
	return (len);
}

char	**env_overriding(t_cmd *cmd, char *argv)
{
	int		len;
	int		i;
	int		env_cnt;
	char	**myenv;
	char	**env_cpy;

	env_cnt = 0;
	myenv = *cmd->env_ptr;
	while (myenv[env_cnt])
		env_cnt++;
	env_cpy = (char **)malloc(sizeof(char *) * (env_cnt + 1));
	i = -1;
	while (myenv[++i])
	{
		len = length_to_equ(myenv[i]);
		if (!ft_strncmp(myenv[i], argv, len))
			env_cpy[i] = ft_strdup(argv);
		else
			env_cpy[i] = ft_strdup(myenv[i]);
	}
	env_cpy[i] = 0;
	free_split(myenv);
	return (env_cpy);
}

char	**ft_export_arr(t_cmd *cmd, char *str)
{
	char	**my_arr;
	char	**cpy_arr;
	int		i;

	i = 0;
	if (is_envs_export(cmd, str))
		return (0);
	my_arr = *cmd->export_arr;
	while (my_arr[i])
		i++;
	cpy_arr = (char **)malloc(sizeof(char *) * (i + 2));
	if (!cpy_arr)
		return (init_err());
	i = -1;
	while(my_arr[++i])
		cpy_arr[i] = my_arr[i];
	cpy_arr[i] = ft_strdup(str);
	cpy_arr[i + 1] = 0;
	free(my_arr)
	return (cpy_arr);
}

void	export_no_parm(t_cmd *cmd)
{
	char	**envs;
	char	**split;
	char	*key;
	char	*value;
	char	**export_arr;

	envs = *cmd->env_ptr;
	while (*envs)
	{
		split = ft_split(*envs++, '=');
		key = split[0];
		value = split[1];
		printf("declare -x %s=\"%s\"\n", key, value);
		free_split(split);
	}
	export_arr = cmd->export_arr;
	while (*export_arr)
		printf("declare -x %s\n", *export_arr++);
}
