/*
** basic_func_server.c for basic_func_server in /home/debas_e/Project/System_Unix/PSU_2013_myftp/srv
**
** Made by Etienne
** Login   <debas_e@epitech.net>
**
** Started on  Fri Apr 11 23:58:39 2014 Etienne
** Last update Sat Apr 12 00:02:27 2014 Etienne
*/

#include <string.h>
#include <dirent.h>
#include <limits.h>
#include <stdlib.h>
#include "serveur.h"

char			*ls_serveur(t_serveur *serv,
				    __attribute__((unused)) t_cmd *cmd)
{
  DIR			*dir;
  struct dirent		*dirent;
  t_data		data;

  dir = opendir("./");
  if (dir == NULL)
    {
      perror("opendir");
      return ("Error : failed to opendir");
    }
  while ((dirent = readdir(dir)))
    {
      memset(&data, 0, sizeof(data));
      data.size = dirent->d_reclen;
      data.total_size = dirent->d_reclen;
      snprintf(data.data, DATA_SIZE, "%s%s%s",
	       dirent->d_type ==  DT_DIR ? COLOR_BLUE : "",
	       dirent->d_name, dirent->d_type ==  DT_DIR ? COLOR_RESET : "");
      data.flags = DATA;
      if (send_result_client(serv->sockfd, &data))
	return ("Error : send error occured");
    }
  return ("Success : ls");
}

char			*check_path(t_cmd *cmd, t_serveur *serv)
{
  int			path_base_len;
  char			*new_path;

  if (cmd->arg2[0] == 0)
    strncpy(cmd->arg2, serv->base_pwd, CMD_SIZE);
  new_path = realpath(cmd->arg2, NULL);
  if (!new_path)
    return (NULL);
  path_base_len = strlen(serv->base_pwd);
  if (strncmp(new_path, serv->base_pwd, path_base_len))
    return (NULL);
  return (new_path);
}

void			change_current_pwd(char *new_path, t_serveur *serv)
{
  int			base_pwd_len;

  if (!strcmp(new_path, serv->base_pwd))
    strcpy(serv->current_pwd, "/");
  else
    {
      base_pwd_len = strlen(serv->base_pwd);
      strncpy(serv->current_pwd, &new_path[base_pwd_len], PATH_MAX);
    }
}

char			*cd_serveur(t_serveur *serv, t_cmd *cmd)
{
  char			*new_path;

  new_path = check_path(cmd, serv);
  if (new_path == NULL)
    return ("Error : failded to change directory");
  if (chdir(new_path) < 0)
    {
      perror("chdir");
      return ("Error changing directory");
    }
  change_current_pwd(new_path, serv);
  return ("Success : cd");
}

char			*pwd_serveur(t_serveur *serv,
				     __attribute__((unused)) t_cmd *cmd)
{
  t_data		data;

  memset(&data, 0, sizeof(data));
  data.size = strlen(serv->current_pwd);
  data.total_size = strlen(serv->current_pwd);
  snprintf(data.data, DATA_SIZE, "%s", serv->current_pwd);
  data.flags = DATA;
  if (send_result_client(serv->sockfd, &data))
    return ("Error : send error occured");
  return ("Success : pwd");
}
