/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/02 12:29:37 by tklouwer      #+#    #+#                 */
/*   Updated: 2022/12/15 15:47:39 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include <stdlib.h>

int wr_dup2(int fd1, int fd2)
{
    close(fd1);
    close(fd2);
    perror("Dup2");
    exit (EXIT_FAILURE);   
}

int	p_error(char *str, int fd)
{
    write(2, "./pipex ", 8);
    perror(str);
    exit (fd);
}

char *command_path(t_data *data, char *argv)
{
    char *file_cmd;
    int i;
    
    i = 0;
    while(data->path_vars[i])
    {
        file_cmd = ft_strjoin(data->path_vars[i], argv);
        if (!file_cmd)
            p_error("ft_strjoin", 2);
        if (access(file_cmd, X_OK) == 0)
        {
            return (file_cmd);
        }
        free(file_cmd);
        i++;
    }
    return (NULL);
}

void execute_command(t_data *data, char **cmd, char *argv)
{
    char    *file_cmd;

    file_cmd = command_path(data, argv);
    if (!file_cmd)
        p_error("Command not found", 127);
    if (execve(file_cmd, cmd, data->envp) == -1)
        p_error("Execve", 127);
    p_error("Command execution failed", 127);
}

void child_process(t_data *data)
{
    int IN_FILE;

    IN_FILE = open(data->argv[1], O_RDONLY);
    if (IN_FILE < 0)
        p_error("Failed to open fd", 1);
    if (dup2(IN_FILE, STDIN_FILENO) < 0)
        wr_dup2(IN_FILE, data->end[1]);
    if (dup2(data->end[1], STDOUT_FILENO) < 0)
        wr_dup2(IN_FILE, data->end[1]);
    close(data->end[1]);
    close(IN_FILE);
    execute_command(data, data->cmd1, data->argv[2]);
}

void child_process2(t_data *data)
{
    int OUT_FILE;

    OUT_FILE = open(data->argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (OUT_FILE < 0)
        p_error("Failed to open fd", 1);
    if (dup2(data->end[0], STDIN_FILENO) < 0)
        wr_dup2(OUT_FILE, data->end[0]);
    if (dup2(OUT_FILE, STDOUT_FILENO) < 0)
        wr_dup2(OUT_FILE, data->end[0]);
    close(data->end[0]);
    close(data->end[1]);
    close(OUT_FILE);
    execute_command(data, data->cmd2, data->argv[3]);
}

int parent_process(t_data *data, pid_t child1, pid_t child2)
{
    int status;

    
    waitpid(child1, &status, 0);
    waitpid(child2, &status, 0);
    // if (WIFEXITED(status)) 
    // {
    //     ft_putnbr_fd(status, 1);
    //     write(1, "\n", 1);
    //     exit(status);
    // }
    close(data->end[0]);
    close(data->end[1]);
    return (status);
}

int pipex(t_data *data)
{
    pid_t child1;
    pid_t child2;

    if (pipe(data->end) < 0)
        perror("pipe");
    child1 = fork();
    if (child1 < 0)
        perror("Fork:");
    else if (child1 == 0)
        child_process(data);
    child2 = fork();
    if (child2 < 0)
        perror("Fork");
    else if (child2 == 0)
        child_process2(data);
    return (parent_process(data, child1, child2));
}

int main(int argc, char **argv, char **envp)
{
    t_data data;

    if (argc != 5)
        error("NOT CORRECT AMOUNT ARGS", 2);
    if (parse_path(&data, argv, envp))
        exit (EXIT_FAILURE);
    return(pipex(&data));
}
