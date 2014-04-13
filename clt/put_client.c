/*
** put_client.c for put_client in /home/debas_e/Project/System_Unix/PSU_2013_myftp
**
** Made by Etienne
** Login   <debas_e@epitech.net>
**
** Started on  Fri Apr 11 19:14:17 2014 Etienne
** Last update Sat Apr 12 17:29:21 2014 Etienne
*/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include "client.h"

static int	is_reg_file(int fd, struct stat *st)
{
  if (fstat(fd, st) < 0)
    {
      fprintf(stderr, "%sfstat error : %s%s\n",
	      COLOR_RED, strerror(errno), COLOR_RESET);
      return (-1);
    }
  if (!S_ISREG(st->st_mode))
    {
      fprintf(stderr, "%sput : invalid file%s\n",
	      COLOR_RED, COLOR_RESET);
      return (-1);
    }
  return (0);
}

static int	is_valid_file(char *path_file, t_data *data)
{
  int		fd;
  char		*name;
  struct stat	st;

  if (path_file[0] == 0)
    {
      printf("%sUsage : put [file]%s\n", COLOR_RED, COLOR_RESET);
      return (-1);
    }
  if ((fd = open(path_file, O_RDONLY)) < 0)
    {
      fprintf(stderr, "%sFailded to opend file : %s%s\n",
	      COLOR_RED, path_file, COLOR_RESET);
      return (-1);
    }
  if (is_reg_file(fd, &st) == -1)
    return (-1);
  data->size = st.st_size;
  name = rindex(path_file, '/');
  name = (name == NULL ? path_file : name + 1);
  snprintf(data->data, DATA_SIZE, "%s", name);
  return (fd);
}

static int	loop_put(size_t size, int sockfd, int fd)
{
  size_t	total_sent;
  ssize_t	sent;

  total_sent = 0;
  while (total_sent < size)
    {
      if ((sent = sendfile(sockfd, fd, NULL, size)) < 0)
	{
	  fprintf(stderr, "Error : sendfile error\n");
	  return (EXIT_FAILURE);
	}
      total_sent += sent;
    }
  return (EXIT_SUCCESS);
}

int		put_client(t_client *client, t_cmd *cmd)
{
  int		fd;
  t_data	data;

  memset(&data, 0, sizeof(data));
  if ((fd = is_valid_file(cmd->arg2, &data)) > 0)
    {
      if (send_cmd_serv(client->sockfd, cmd) == EXIT_FAILURE ||
	  (write(client->sockfd, &data, sizeof(data)) != sizeof(data)))
	{
	  printf("%sError occured during sending file%s", COLOR_RED, COLOR_RESET);
	  return (EXIT_FAILURE);
	}
      if (loop_put(data.size, client->sockfd, fd) == EXIT_FAILURE)
	return (EXIT_FAILURE);
    }
  if (fd > 0)
    {
      printf("%sSuccess sending file%s\n", COLOR_GREEN, COLOR_RESET);
      close(fd);
    }
  return (EXIT_SUCCESS);
}
