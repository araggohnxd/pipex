/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 02:17:23 by maolivei          #+#    #+#             */
/*   Updated: 2022/06/07 15:43:30 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "../libft/libft.h"
# include <stdio.h> // perror
# include <fcntl.h> // open, close
# include <sys/wait.h> // wait, waitpid

# define READ 0
# define WRITE 1
# define STDIN STDIN_FILENO
# define STDOUT STDOUT_FILENO
# define STDERR STDERR_FILENO

# define ERRUSE "Invalid usage\n"
# define USAGE "Usage: ./pipex <infile> <cmd1> <cmd2> <outfile>"
# define ERRARG "An error occurred while parsing arguments"
# define ERRCMD "An error occurred while parsing commands"

typedef struct s_data {
	int		infile;
	int		outfile;
	char	*cmd;
	char	**args;
	int		pipe_fd[2];
	pid_t	child_pid_1;
	pid_t	child_pid_2;
}	t_data;

void	ft_set_error(int error_id, char *error_msg);
void	ft_get_arguments(t_data *data, char *arg, char *envp[]);
char	**ft_parse_cmd_args(char *cmd);
void	ft_replace_quoted_arg(char **str, char from, char to);
char	*ft_parse_env_path(char *envp[], char *cmd);
void	ft_execute(t_data *data, char *envp[]);
void	ft_read_infile(t_data *data, char *arg, char *envp[]);
void	ft_write_outfile(t_data *data, char *arg, char *envp[]);

#endif /* PIPEX_H */
