/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeson <jeson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:47:02 by jeson             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/01/05 15:01:06 by jeson            ###   ########.fr       */
=======
/*   Updated: 2022/01/03 16:25:11 by jeson            ###   ########.fr       */
>>>>>>> 2b92af95d14440155de3e5e750fa73c8572eb48b
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export_no_argv(t_cmd *cmd)
{
	char **envs;
	char **split;
	char *key;
	char *value;

	envs = *(cmd->env_ptr);
	while (*envs)
	{
		split = ft_split(*envs++, '=');
		key = *split++;
		value = *split;
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(key, 1);
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(value, 1);
		ft_putendl_fd("\"", 1);
	}
}

<<<<<<< HEAD
int		length_to_equ(char *s1)
{
	int	i;

	i = 0;
	while (s1[i] != '=')
		i++;
	return (i);
}
/*
char **make_new_env(char **src, char *argv_ptr)
{
	char	**res;
	int		cnt;
	int		len;
	int		i;

	cnt	= 0;
	while (src[cnt])
		cnt++;
	res = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (!res)
		return (ini_err());
	i = 0;
	while (i < cnt)
	{
		len = ft_strlen(src[i]);
		res[i] = (char *)malloc(sizoef)
	}
}
*/
void	export_override(t_cmd *cmd, char *argv_ptr)
{
	char	*export_key;
	int		len;
	int		i;
	char	**myenv;

	i = 0;
	len = 0;
	myenv = *cmd->env_ptr;
	export_key = (char *)malloc(sizeof(char) * (length_to_equ(argv_ptr) + 1));
	ft_memcpy(export_key, argv_ptr, length_to_equ(argv_ptr) + 1);
	while (myenv[i])
	{
		len = length_to_equ(myenv[i]);
		if (!ft_strncmp(myenv[i], export_key, len))
		{
			free(myenv[i]);
			myenv[i] = (char *)malloc(sizeof(char) * (ft_strlen(argv_ptr) + 1));
			ft_memcpy(myenv[i], argv_ptr, ft_strlen(argv_ptr) + 1);
		}
		i++;;
	}
}
=======
/*
void	export_override(t_cmd *cmd, char *argv_ptr)
{
	char **argv_split;
	char *key_tmp;

	argv_split = ft_split(argv_ptr, '=');
	key_tmp = *argv_split;
	getenv
}
*/
>>>>>>> 2b92af95d14440155de3e5e750fa73c8572eb48b

int	is_valid(char *str)
{
	int	i;
	int idx;
	int	cnt;

	i = 0;
	cnt = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			cnt++;
			idx = i;
		}
		i++;
	}
<<<<<<< HEAD
	if (cnt == 1 && idx != 0)
=======
	if (cnt == 1 && (idx != 0 && idx != (i - 1)))
>>>>>>> 2b92af95d14440155de3e5e750fa73c8572eb48b
		return (0);
	return (1);
}

int	is_envs(char *tmp_env)
{
<<<<<<< HEAD
	char **env_split;

	env_split = ft_split(tmp_env, '=');
	if (!getenv(*env_split))
=======
	if (!getenv(tmp_env))
>>>>>>> 2b92af95d14440155de3e5e750fa73c8572eb48b
		return (1);
	return (0);
}

<<<<<<< HEAD
char	**export_env(t_cmd *cmd, char *argv_ptr)
{
	int		len;
	int		env_cnt;
	int		i;
	char	**myenv;
	char	**env_cpy;

	env_cnt = 0;
	myenv = *cmd->env_ptr;
	while (myenv[env_cnt])
		env_cnt++;
	env_cpy = (char **)malloc(sizeof(char *) * (env_cnt + 2));
	if (!env_cpy)
		return (init_err());
	i = 0;
	while (i < env_cnt)
	{
		len = ft_strlen(myenv[i]);
		env_cpy[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (!env_cpy[i])
			return (init_err());
		env_cpy[i] = ft_memcpy(env_cpy[i], myenv[i], (len + 1));
		i++;
	}
	env_cpy[i] = (char *)malloc(sizeof(char) * (ft_strlen(argv_ptr) + 1));
	env_cpy[i] = ft_memcpy(env_cpy[i], argv_ptr, ft_strlen(argv_ptr) + 1);
	env_cpy[env_cnt + 1] = 0;
	return (env_cpy);
}

=======
>>>>>>> 2b92af95d14440155de3e5e750fa73c8572eb48b
int	ft_export(t_cmd *cmd)
{
	int	i;
	int	res;
<<<<<<< HEAD
	int	flg_form;
	char	**myenviron;

	i = 1;
	flg_form = 0;
	myenviron = *cmd->env_ptr;
=======

	i = 1;
>>>>>>> 2b92af95d14440155de3e5e750fa73c8572eb48b
	if (!cmd->argv[1])
	{
		print_export_no_argv(cmd);
		return (0);
	}
	while (cmd->argv[i])
	{
		if (!is_valid(cmd->argv[i]))
			res = is_envs(cmd->argv[i]);
<<<<<<< HEAD
		if (res == 0)
			export_override(cmd, cmd->argv[i]);
		else
			*cmd->env_ptr = export_env(cmd, cmd->argv[i]);
		i++;
=======
	/*	if (res == 0)
			export_override(cmd, cmd->argv[i]);
	*/	i++;
>>>>>>> 2b92af95d14440155de3e5e750fa73c8572eb48b
	}
	return (0);
}
