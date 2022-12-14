/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/02 12:29:37 by tklouwer      #+#    #+#                 */
/*   Updated: 2022/12/13 14:54:19 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int  error(char *str)
{
    ft_putstr_fd(str, 2);
    exit(2);
}

int child_process(t_data *data, int fd1, char **cmd)
{
    if (dup2(fd1, data->fd[2]) < 0)
        perror("Dup2: ");
    execve(data->path_vars[0], cmd);
}

int open_fd(t_data *data, char **argv)
{
    data->fd[0] = open(argv[1], O_RDONLY);
    data->fd[1] = open(argv[4], O_WRONLY, O_CREAT, 066);
    if (!data->fd[0] || !data->fd[1])
    {
        close(data->fd[0]);
        close(data->fd[1]);
        exit(EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

int pipex(t_data *data, char **argv)
{
    pid_t process;

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
    open_fd(&data);
    parse_path(&data, argv, envp);
    pipex(&data, argv);
    return (1);
}
