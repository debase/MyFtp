/*
** put_client.c for put_client in /home/debas_e/Project/System_Unix/PSU_2013_myftp
**
** Made by Etienne
** Login   <debas_e@epitech.net>
**
** Started on  Fri Apr 11 19:14:17 2014 Etienne
** Last update Fri Apr 11 20:45:23 2014 Etienne
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

static int	is_valid_file(char *path_file, t_data *data)
{
  int		fd;
  struct stat	st;
  char		*name;

  if (path_file[0] == 0)
    {
      printf ("%sUsage : put [file]%s\n", COLOR_RED, COLOR_RESET);
      return (-1);
    }
  if ((fd = open(path_file, O_RDONLY)) < 0)
    {
      fprintf(stderr, "%sFailded to opend file : %s%s\n",
	      COLOR_RED, path_file, COLOR_RESET);
      return (-1);
    }
  if (fstat(fd, &st) < 0)
    {
      fprintf(stderr, "%sfstat error : %s%s\n",
	      COLOR_RED, strerror(errno), COLOR_RESET);
      return (-1);
    }
  if (!S_ISREG(st.st_mode))
    {
      fprintf(stderr, "%sput : invalid file%s\n",
	      COLOR_RED, COLOR_RESET);
      return (-1);
    }
  data->size = st.st_size;
  name = rindex(path_file, '/');
  name = (name == NULL ? path_file : name + 1);
  snprintf(data->data, DATA_SIZE,"%s", name);
  return (fd);
}

int		put_client(t_client *client, t_cmd *cmd)
{
  int		fd;
  t_data	data;

  memset(&data, 0, sizeof(data));
  if ((fd = is_valid_file(cmd->arg2, &data)) > 0)
    {
      if (send_cmd_serv(client->sockfd, cmd) == EXIT_FAILURE ||
	  (write(client->sockfd, &data, sizeof(data)) != sizeof(data)) ||
	  (sendfile(client->sockfd, fd, NULL, data.size) < 0))
	{
	  printf("%sError occured during sending file%s", COLOR_RED, COLOR_RESET);
	  return (EXIT_FAILURE);
	}
    }
  if (fd > 0)
    {
      printf("%sSuccess sending file\n%s", COLOR_GREEN, COLOR_RESET);
      close(fd);
    }
  return (EXIT_SUCCESS);
}
