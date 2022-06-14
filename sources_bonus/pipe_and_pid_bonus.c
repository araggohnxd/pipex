/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_and_pid_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 04:59:17 by maolivei          #+#    #+#             */
/*   Updated: 2022/06/14 19:30:28 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	ft_read_here_doc_input(t_data *data)
{
	const size_t	limiter_len = ft_strlen(data->limiter);
	char			*gnl;
	int				index;

	while (TRUE)
	{
		index = -1;
		while (++index < (data->cmd_count - 1))
			ft_putstr_fd("pipex ", STDIN);
		ft_putstr_fd("here_doc> ", STDIN);
		gnl = ft_get_next_line(STDIN);
		if (ft_strncmp(gnl, data->limiter, limiter_len) == 0
			&& gnl[limiter_len] == '\n')
		{
			ft_memfree((void *) &gnl);
			close(STDIN);
			close(STDOUT);
			close(data->pipe_fd[0][WRITE]);
			gnl = ft_get_next_line(STDIN);
			break ;
		}
		ft_putstr_fd(gnl, data->pipe_fd[0][WRITE]);
		ft_memfree((void *) &gnl);
	}
	ft_memfree((void *) &gnl);
}

static void	ft_build_pipeline(t_data *data)
{
	int	index;

	if (data->here_doc)
		ft_read_here_doc_input(data);
	else if (data->infile_fd >= 0)
	{
		close(data->pipe_fd[0][READ]);
		data->pipe_fd[0][READ] = data->infile_fd;
	}
	close(data->pipe_fd[0][WRITE]);
	index = -1;
	while (++index < (data->cmd_count - 1))
		data->pipe_fd[index][WRITE] = data->pipe_fd[index + 1][WRITE];
	data->pipe_fd[data->cmd_count - 1][WRITE] = data->outfile_fd;
}

void	ft_init_pipe(t_data *data)
{
	int	index;

	data->pipe_fd = (int **) ft_calloc(
			(data->cmd_count + 1), sizeof(data->pipe_fd));
	if (!data->pipe_fd)
		ft_set_perror(data, EXIT_FAILURE, "error allocating for pipe");
	index = -1;
	while (++index < data->cmd_count)
	{
		data->pipe_fd[index] = (int *) ft_calloc(2, sizeof(int));
		if (!data->pipe_fd[index])
			ft_set_perror(data, EXIT_FAILURE, "error allocating for pipe");
		if (pipe(data->pipe_fd[index]) < 0)
			ft_set_perror(data, EXIT_FAILURE, "error creating pipe");
	}
	ft_build_pipeline(data);
}

void	ft_init_pid(t_data *data)
{
	data->pid = ft_calloc(data->cmd_count, sizeof(int));
	if (!data->pid)
		ft_set_perror(data, EXIT_FAILURE, "error creating PIDs array");
}
