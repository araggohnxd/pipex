/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_and_pid_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 04:59:17 by maolivei          #+#    #+#             */
/*   Updated: 2022/06/11 05:31:05 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_init_pipe(t_data *data)
{
	int	index;

	data->pipe_fd = ft_calloc((data->pipe_count + 1), sizeof(data->pipe_fd));
	if (!data->pipe_fd)
		ft_set_perror(data, EXIT_FAILURE, "error creating pipe");
	index = -1;
	while (++index < data->pipe_count)
	{
		data->pipe_fd[index] = ft_calloc(2, sizeof(int));
		if (!data->pipe_fd[index])
			ft_set_perror(data, EXIT_FAILURE, "error creating pipe");
		if (pipe(data->pipe_fd[index]) < 0)
			ft_set_perror(data, EXIT_FAILURE, "error creating pipe");
	}
}

void	ft_init_pid(t_data *data)
{
	data->pid = ft_calloc(data->cmd_count, sizeof(int));
	if (!data->pid)
		ft_set_perror(data, EXIT_FAILURE, "error creating PIDs array");
}
