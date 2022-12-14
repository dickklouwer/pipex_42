/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/02 12:29:37 by tklouwer      #+#    #+#                 */
/*   Updated: 2022/12/14 09:52:24 by dickklouwer   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int child_process(t_data *data, int fd1, char **cmd)
{
    if (dup2(fd1, data->fd[1]) < 0)
        perror("Dup2: ");
    // if (dup2())
    // execve(data->path_vars[0], cmd);
}

int pipex(t_data *data, char **argv)
{
    pid_t process;

    open_fd(data, argv);
    if (pipe(data->fd) < 0)
        perror("pipe");
    process = fork();
    if (process < 0)
        perror("Fork:");
    if (process == 0)
    {
        child_process(data, data->fd[0], data->cmd1);
    }
    // if (process > 0)
    //     parent_process();
    return (EXIT_SUCCESS);
}

int main(int argc, char **argv, char **envp)
{
    t_data data;

    if (argc != 5)
        error("NOT CORRECT AMOUNT ARGS");
    parse_path(&data, argv, envp);
    pipex(&data, argv);
    return (1);
}
