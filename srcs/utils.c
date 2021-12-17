/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 02:11:36 by sangjeon          #+#    #+#             */
/*   Updated: 2021/12/17 21:33:58 by sangjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_redi_info(void *content)
{
	t_redi	*redi;
	char	*str;

	redi = content;
	str = "normal";
	if (redi->redi_status == REDIRECT_INPUT)
		str = "input";
	if (redi->redi_status == REDIRECT_OUTPUT)
		str = "output";
	if (redi->redi_status == REDIRECT_APPEND)
		str = "append";
	if (redi->redi_status == REDIRECT_HEREDOC)
		str = "heredoc";
	printf("redi_status : %s\n", str);
	printf("redi_arg : %s\n", redi->arg);
}

void	print_cmd_info(void *content)
{
	t_cmd	*cmd;
	char	**arr;
	// char	**env;

	cmd = content;
	arr = cmd->argv;
	printf("=== cmd ===\n");
	while (*arr)
	{
		printf("%s\n", *arr);
		arr++;
	}
	printf("--- redi ---\n");
	ft_lstiter(cmd->redi_list, print_redi_info);
}

void	free_split(char **str_arr)
{
	int	i;

	i = 0;
	while (str_arr[i])
		free(str_arr[i++]);
	free(str_arr);
}

int	file_exist(char *path)
{
	struct stat	buf;

	if (!stat(path, &buf))
		return (1);
	else
		return (0);
}

int	get_child_return(pid_t pid, char *full_path)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_last_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_last_status = 128 + WTERMSIG(status);
	free(full_path);
	return (EXIST);
}

char	*get_full_path(char *each_cmd, char *each_path)
{
	char	*tmp;
	char	*full_path;

	tmp = ft_strjoin(each_path, "/");
	if (!tmp)
		return (err_handle3());
	full_path = ft_strjoin(tmp, each_cmd);
	free(tmp);
	if (!full_path)
		return (err_handle3());
	return(full_path);
}
