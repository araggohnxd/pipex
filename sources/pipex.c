/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 02:17:00 by maolivei          #+#    #+#             */
/*   Updated: 2022/06/16 17:42:17 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_init_pipe(t_data *data)
{
	if (pipe(data->pipe_fd[0]) < 0)
		ft_set_perror(data, EXIT_FAILURE, "error creating pipe");
	if (pipe(data->pipe_fd[1]) < 0)
		ft_set_perror(data, EXIT_FAILURE, "error creating pipe");
	if (data->infile_fd >= 0)
	{
		close(data->pipe_fd[0][READ]);
		data->pipe_fd[0][READ] = data->infile_fd;
	}
	close(data->pipe_fd[0][WRITE]);
	data->pipe_fd[0][WRITE] = data->pipe_fd[1][WRITE];
	data->pipe_fd[1][WRITE] = data->outfile_fd;
}

static void	ft_init_data(t_data *data, int argc, char **argv, char **envp)
{
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
	data->infile = argv[1];
	data->outfile = argv[4];
	data->cmds = NULL;
	data->args = NULL;
	data->pid[0] = 0;
	data->pid[1] = 0;
	data->exit_value = 0;
	data->infile_fd = open(data->infile, O_RDONLY);
	if (data->infile_fd < 0)
		ft_set_perror(data, ERR_IO_FILE, data->infile);
	data->outfile_fd = open(data->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->outfile_fd < 0)
		ft_set_perror(data, ERR_IO_FILE, data->outfile);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc != 5)
	{
		if (argc > 5)
			ft_putendl_fd("pipex: Too many arguments", STDERR);
		else if (argc < 5)
			ft_putendl_fd("pipex: Too few arguments", STDERR);
		ft_putendl_fd(
			"Usage: ./pipex <infile> <cmd1> <cmd2> <outfile>", STDERR);
		exit(EXIT_FAILURE);
	}
	ft_init_data(&data, argc, argv, envp);
	ft_argument_parser(&data);
	ft_init_pipe(&data);
	ft_init_exec(&data);
	ft_free_pipex(&data);
	return (data.exit_value);
}
