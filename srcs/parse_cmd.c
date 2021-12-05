/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 00:59:16 by sangjeon          #+#    #+#             */
/*   Updated: 2021/12/05 11:09:53 by sangjeon         ###   ########.fr       */
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
	if (!ft_strncmp(">>", str, 2))
		cmd->multi_status = REDIRECT_APPEND;
	else if (!ft_strncmp("<<", str, 2))
		cmd->multi_status = REDIRECT_HEREDOC;
	else if (!ft_strncmp(">", str, 1))
		cmd->multi_status = REDIRECT_OUTPUT;
	else if (!ft_strncmp("<", str, 1))
		cmd->multi_status = REDIRECT_INPUT;
	else if (!ft_strncmp("|", str, 1))
		cmd->multi_status = PIPE;
	else
		cmd->multi_status = 0;
	return (cmd->multi_status);
}

void	set_null_and_move_ptr(char **line_ptr, t_cmd *cmd)
{
	if (**line_ptr)
	{
		**line_ptr = '\0';
		(*line_ptr)++;
		if (cmd->multi_status == REDIRECT_APPEND)
			(*line_ptr)++;
		if (cmd->multi_status == REDIRECT_HEREDOC)
			(*line_ptr)++;
	}
}

void	parse_cmd(t_list **cmd_list_ptr, char *line)
{
	t_cmd	*cmd;
	char	*tmp;

	while (*line && in_isspace(*line))
		line++;
	while (*line)
	{
		cmd = (t_cmd *)malloc(sizeof(t_cmd));
		if (!cmd)
			return err_handle1();
		tmp = line;
		while (*line && !is_multi_cmd(line, cmd))
			line++;
		set_null_and_move_ptr(&line, cmd);
		cmd->argv = ft_split(tmp, ' ');
		ft_lstadd_back(cmd_list_ptr, ft_lstnew(cmd));
	}
}
