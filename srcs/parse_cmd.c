/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 00:59:16 by sangjeon          #+#    #+#             */
/*   Updated: 2021/12/05 02:41:02 by sangjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	in_isspace(char chr)
{
	if (chr == '\t')
		return (1);
	if (chr == ' ')
		return (1);
	return (0);
}

static int	is_multi_cmd(char *str, t_cmd *cmd)
{
	if (!ft_strncmp(">", str, 1))
		cmd->multi_cmd = REDIRECT_OUTPUT;
	else if (!ft_strncmp("<", str, 1))
		cmd->multi_cmd = REDIRECT_INPUT;
	else if (!ft_strncmp(">>", str, 2))
		cmd->multi_cmd = REDIRECT_APPEND;
	else if (!ft_strncmp("<<", str, 2))
		cmd->multi_cmd = REDIRECT_HEREDOC;
	else if (!ft_strncmp("|", str, 1))
		cmd->multi_cmd = PIPE;
	else
		cmd->multi_cmd = 0;
	return (cmd->multi_cmd);
}

void	set_null_and_move_ptr(char **line_ptr)
{
	if (**line_ptr)
	{
		**line_ptr = '\0';
		(*line_ptr)++;
	}
}

t_cmd	*parse_one(char **line_ptr)
{
	char	*tmp;
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return err_handle1();
	while (**line_ptr && in_isspace(**line_ptr))
		(*line_ptr)++;
	tmp = *line_ptr;
	while (**line_ptr && !in_isspace(**line_ptr))
		(*line_ptr)++;
	set_null_and_move_ptr(line_ptr);
	cmd->cmd = ft_strdup(tmp);
	while (**line_ptr && in_isspace(**line_ptr))
		(*line_ptr)++;
	tmp = *line_ptr;
	while (**line_ptr && !is_multi_cmd(*line_ptr, cmd))
		(*line_ptr)++;
	set_null_and_move_ptr(line_ptr);
	cmd->arg = ft_strdup(tmp);
	return (cmd);
}

void	parse_cmd(t_list **cmd_list_ptr, char *line)
{
	while (*line)
		ft_lstadd_back(cmd_list_ptr, ft_lstnew(parse_one(&line)));
}
