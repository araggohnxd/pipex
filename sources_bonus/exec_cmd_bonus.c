/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 22:22:12 by maolivei          #+#    #+#             */
/*   Updated: 2022/06/11 19:39:36 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_exec_nth_cmd(t_data *data, int index)
{
	int	i;

	if (dup2(data->pipe_fd[index - 1][READ], STDIN) < 0)
		ft_set_perror(data, EXIT_FAILURE, "error duping file descriptors");
	if (dup2(data->pipe_fd[index][WRITE], STDOUT) < 0)
		ft_set_perror(data, EXIT_FAILURE, "error duping file descriptors");
	i = -1;
	while (++i < data->pipe_count)
	{
		close(data->pipe_fd[i][WRITE]);
		close(data->pipe_fd[i][READ]);
	}
	if (!data->cmds[index]
		|| execve(
			data->cmds[index],
			data->args[index],
			data->envp) < 0)
		ft_set_perror(data, 127, ft_strjoin(CMD_404, data->args[index][0]));
}

void	ft_exec_first_cmd(t_data *data)
{
	int	index;

	data->infile_fd = open(data->infile, O_RDONLY);
	if (data->infile_fd < 0)
		ft_set_perror(data, EXIT_FAILURE, data->infile);
	if (dup2(data->infile_fd, STDIN) < 0)
		ft_set_perror(data, EXIT_FAILURE, "error duping file descriptors");
	if (dup2(data->pipe_fd[0][WRITE], STDOUT) < 0)
		ft_set_perror(data, EXIT_FAILURE, "error duping file descriptors");
	index = -1;
	while (++index < data->pipe_count)
	{
		close(data->pipe_fd[index][WRITE]);
		close(data->pipe_fd[index][READ]);
	}
	close(data->infile_fd);
	if (!data->cmds[0]
		|| execve(
			data->cmds[0],
			data->args[0],
			data->envp) < 0)
		ft_set_perror(data, 127, ft_strjoin(CMD_404, data->args[0][0]));
}

void	ft_exec_last_cmd(t_data *data)
{
	int	index;

	data->outfile_fd = open(data->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->outfile_fd < 0)
		ft_set_perror(data, EXIT_FAILURE, data->outfile);
	if (dup2(data->outfile_fd, STDOUT) < 0)
		ft_set_perror(data, EXIT_FAILURE, "error duping file descriptors");
	if (dup2(data->pipe_fd[(data->pipe_count - 1)][READ], STDIN) < 0)
		ft_set_perror(data, EXIT_FAILURE, "error duping file descriptors");
	index = -1;
	while (++index < data->pipe_count)
	{
		close(data->pipe_fd[index][WRITE]);
		close(data->pipe_fd[index][READ]);
	}
	close(data->outfile_fd);
	if (!data->cmds[(data->cmd_count - 1)]
		|| execve(
			data->cmds[(data->cmd_count - 1)],
			data->args[(data->cmd_count - 1)],
			data->envp) < 0)
		ft_set_perror(data, 127, ft_strjoin(
				CMD_404, data->args[(data->cmd_count - 1)][0]));
}
