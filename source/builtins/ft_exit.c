/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 12:24:58 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/22 19:26:49 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

int	is_within_longlong_range(char *str)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (str[i] == '\0')
		return (0);
	return (check_numeric_overflow(str, i, sign));
}

void	exit_with_numeric_error(t_cmd *cmd, t_data *data)
{
	printf("bash: exit: %s: numeric argument required\n", cmd->argv[1]);
	update_exit_status(data, 2);
	ft_free_all(data);
	exit(2);
}

void	ft_exit(t_cmd *cmd, t_data *data)
{
	long	exit_code;

	printf("exit\n");
	if (cmd->argv[1] && (!is_numeric(cmd->argv[1])
			|| !is_within_longlong_range(cmd->argv[1])))
		exit_with_numeric_error(cmd, data);
	if (cmd->argv[1] && cmd->argv[2])
	{
		printf("bash: exit: too many arguments\n");
		data->lst_exit = 1;
		update_exit_status(data, 1);
		return ;
	}
	if (cmd->argv[1])
		exit_code = ft_atol(cmd->argv[1]);
	else
		exit_code = data->lst_exit;
	exit_code = exit_code % 256;
	if (exit_code < 0)
		exit_code += 256;
	update_exit_status(data, exit_code);
	ft_free_all(data);
	exit(exit_code);
}
