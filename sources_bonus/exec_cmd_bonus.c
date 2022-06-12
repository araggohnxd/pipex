/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 22:22:12 by maolivei          #+#    #+#             */
/*   Updated: 2022/06/12 14:16:54 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_exec_nth_cmd(t_data *data, int index)
{
	int	i;

	if (dup2(data->pipe_fd[index][READ], STDIN) < 0)
		ft_set_perror(data, EXIT_FAILURE, "error duping file descriptors");
	if (dup2(data->pipe_fd[index][WRITE], STDOUT) < 0)
		ft_set_perror(data, EXIT_FAILURE, "error duping file descriptors");
	i = -1;
	while (++i < data->cmd_count)
	{
		close(data->pipe_fd[i][READ]);
		close(data->pipe_fd[i][WRITE]);
	}
	if (!data->cmds[index]
		|| execve(data->cmds[index], data->args[index], data->envp) < 0)
		ft_set_perror(data, 127, ft_strjoin(CMD_404, data->args[index][0]));
}
