/*
** get_client.c for get_client in /home/debas_e/Project/System_Unix/PSU_2013_myftp
**
** Made by Etienne
** Login   <debas_e@epitech.net>
**
** Started on  Thu Apr 10 23:41:35 2014 Etienne
** Last update Fri Apr 11 22:45:09 2014 Etienne
*/

#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "client.h"

static int	write_in_file(char *data, int fd, int size)
{
  int		ret;

  ret = write(fd, data, size);
  if (ret < 0 || ret != size)
    {
      fprintf(stderr, "%s%s%s", COLOR_RED, strerror(errno), COLOR_RESET);
      return (-1);
    }
  return (0);
}

static int	create_file(char *path)
{
  int		fd;

  if ((fd = open(path, O_WRONLY | O_APPEND | O_CREAT, 0644)) == -1)
    fprintf(stderr, "%s%s%s", COLOR_RED, strerror(errno), COLOR_RESET);
  return (fd);
}

static int	get_create_file(t_client *client, int *size)
{
  int		ret;
  t_data	data;

  ret = read(client->sockfd, &data, sizeof(data));
  if (ret < 0 || ret != sizeof(data))
    {
      fprintf(stderr, "read error : %s%s%s\n", COLOR_RED, strerror(errno), COLOR_RESET);
      return (-2);
    }
  if (!strcmp("Invalid file", data.data)
      || !strcmp("Usage : get [file]", data.data))
    {
      printf("%s%s%s\n", COLOR_RED, data.data, COLOR_RESET);
      return (-1);
    }
  *size = data.size;
  return (create_file(data.data));
}

int		get_client(t_client *client, t_cmd *cmd)
{
  int		ret;
  int		fd;
  int		size;
  int		rcv;
  char		buff[DATA_SIZE];

  rcv = 0;
  if (send_cmd_serv(client->sockfd, cmd) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  if ((fd = get_create_file(client, &size)) > 0)
    while (rcv != size)
      {
	ret = read(client->sockfd, buff, DATA_SIZE);
	rcv += ret;
	if (ret <= 0 && rcv != size)
	  {
	    fprintf(stderr, "%sread error : failded to receive file%s\n",
		    COLOR_RED, COLOR_RESET);
	    return (EXIT_FAILURE);
	  }
	if (write_in_file(buff, fd, ret) == -1)
	  break;
      }
  if (fd > 0)
    {
      printf ("%sSuccess : get file%s\n", COLOR_GREEN, COLOR_RESET);
      close(fd);
    }
  return (fd == -2 ? EXIT_FAILURE : EXIT_SUCCESS);
}
