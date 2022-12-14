/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/02 12:29:37 by tklouwer      #+#    #+#                 */
/*   Updated: 2022/12/14 16:03:37 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int execute_command(t_data *data, char **cmd1)
{
    char    *file_cmd;
    int     i;

    i = 0;
    while(data->path_vars[i])
    {
        file_cmd = ft_strjoin(data->path_vars[i], data->argv[2]);
        execve(file_cmd, cmd1, data->envp);
        free(file_cmd);
        i++;
    }
    return (EXIT_SUCCESS);
}
int child_process(t_data *data)
{
    int IN_FILE;

    IN_FILE = open(data->argv[1], O_RDONLY);
    if (IN_FILE < 0)
        exit(EXIT_FAILURE);
    if (dup2(IN_FILE, STDIN_FILENO) < 0)
        perror("Dup2: ");
    if (dup2(data->end[1], STDOUT_FILENO) < 0)
        perror("Dup2: ");
    close(data->end[0]);
    close(IN_FILE);
    execute_command(data, data->cmd1);    
    return (EXIT_SUCCESS);
}

int child_process2(t_data *data)
{
    if (dup2(data->end[0], STDIN_FILENO) < 0)
        perror("Dup2: ");
    if (dup2(data->end[1], STDOUT_FILENO) < 0)
        perror("Dup2: ");
    close(data->end[0]);
    close(data->end[1]);
    execute_command(data, data->cmd1);    
    return (EXIT_SUCCESS);
}

int parent_process(t_data *data)
{
    int status;
    int OUT_FILE;

    waitpid(-1, &status, 0);
    OUT_FILE = open(data->argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0666);
    if (OUT_FILE < 0)
        exit(EXIT_FAILURE);
    if (dup2(OUT_FILE, STDOUT_FILENO) < 0)
        perror("Dup2: ");
    if (dup2(data->end[0], STDIN_FILENO) < 0)
        perror("Dup2: ");
    close(data->end[1]);
    close(OUT_FILE);
    execute_command(data, &data->cmd2);    
    return (EXIT_SUCCESS);
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
    if (child1 == 0)
        child_process(data);
    child2 = fork();
    if (child2 < 0)
        perror("Fork");
    if (child2 == 0)
        child_process2(data);
    else
        parent_process(data);
    return (EXIT_SUCCESS);
}

int main(int argc, char **argv, char **envp)
{
    t_data data;

    if (argc != 5)
        error("NOT CORRECT AMOUNT ARGS");
    parse_path(&data, argv, envp);
    pipex(&data);
    return (1);
}
