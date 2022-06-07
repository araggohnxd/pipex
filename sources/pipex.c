/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 02:17:00 by maolivei          #+#    #+#             */
/*   Updated: 2022/06/07 15:46:31 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_set_error(int error_id, char *error_msg)
{
	ft_putstr_fd("pipex: ", 2);
	if (error_id == 1)
	{
		ft_putendl_fd(error_msg, STDERR);
		exit(EXIT_FAILURE);
	}
	else
		perror(error_msg);
}

void	ft_get_io_files(t_data *data, char *infile, char *outfile)
{
	data->infile = open(infile, O_RDONLY);
	if (data->infile < 0)
		ft_set_error(2, "infile");
	data->outfile = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->outfile < 0)
		ft_set_error(2, "outfile");
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;

	if (argc != 5)
		ft_set_error(1, ERRUSE USAGE);
	ft_get_io_files(&data, argv[1], argv[argc - 1]);
	if (pipe(data.pipe_fd))
		ft_set_error(2, "pipe");
	ft_read_infile(&data, argv[2], envp);
	ft_write_outfile(&data, argv[3], envp);
	close(data.pipe_fd[READ]);
	close(data.pipe_fd[WRITE]);
	waitpid(data.child_pid_1, NULL, 0);
	waitpid(data.child_pid_2, NULL, 0);
	return (0);
}
