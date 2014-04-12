/*
** get_serveur.c for get_serveur in /home/debas_e/Project/System_Unix/PSU_2013_myftp
**
** Made by Etienne
** Login   <debas_e@epitech.net>
**
** Started on  Thu Apr 10 23:42:47 2014 Etienne
** Last update Sat Apr 12 15:23:49 2014 Etienne
*/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <limits.h>
#include <stdlib.h>
#include "serveur.h"

static int		check_path_file(char *file, t_serveur *serv)
{
  char			*real_path;
  int			base_pwd_len;

  base_pwd_len = strlen(serv->base_pwd);
  real_path = realpath(file, NULL);
  if (strncmp(serv->base_pwd, real_path, base_pwd_len))
    {
      return (-1);
    }
  return (0);
}

static int		check_valid_file(t_serveur *serv, t_cmd *cmd, t_data *data)
{
  int			fd;
  struct stat		st;

  memset(data, 0, sizeof(*data));
  if (cmd->arg2[0] == 0)
    {
      snprintf(data->data, DATA_SIZE, "Usage : get [file]");
      return (-1);
    }
  if ((fd = open(cmd->arg2, O_RDONLY)) < 0)
    {
      snprintf(data->data, DATA_SIZE, "Invalid file");
      return (-1);
    }
  if (fstat(fd, &st) < 0 || (check_path_file(cmd->arg2, serv) == -1)
      || !S_ISREG(st.st_mode))
    {
      snprintf(data->data, DATA_SIZE, "Invalid file");
      return (-1);
    }
  data->size = st.st_size;
  snprintf(data->data, DATA_SIZE, "%s", cmd->arg2);
  return (fd);
}

char			*get_serveur(t_serveur *serv, t_cmd *cmd)
{
  int			fd;
  t_data		data;

  fd = check_valid_file(serv, cmd, &data);
  write(serv->sockfd, &data, sizeof(data));
  if (fd > 0)
    {
      if (sendfile(serv->sockfd, fd, NULL, data.size) < 0)
	return ((void *)-1);
      return (NULL);
      close(fd);
    }
  return (NULL);
}
