/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 22:23:07 by maolivei          #+#    #+#             */
/*   Updated: 2022/06/13 17:46:32 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_set_perror(t_data *data, int error_id, char *str)
{
	ft_putstr_fd("pipex_bonus: ", STDERR);
	if (error_id == 127)
	{
		ft_putendl_fd(str, STDERR);
		free(str);
		return ;
	}
	else
		perror(str);
	if (data->args)
		ft_free_pipex(data);
	exit(error_id);
}

void	ft_free_pipex(t_data *data)
{
	int	index;

	index = -1;
	while (++index < data->cmd_count)
	{
		ft_memfree((void *) &data->cmds[index]);
		ft_free_split((void *) &data->args[index]);
	}
	ft_memfree((void *) &data->cmds);
	ft_memfree((void *) &data->args);
	ft_memfree((void *) &data->pid);
	ft_free_split((void *) &data->pipe_fd);
}
