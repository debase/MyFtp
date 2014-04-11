/*
** basic_func_client.c for basic_func in /home/debas_e/Project/System_Unix/PSU_2013_myftp
**
** Made by Etienne
** Login   <debas_e@epitech.net>
**
** Started on  Fri Apr 11 23:31:30 2014 Etienne
** Last update Fri Apr 11 23:33:33 2014 Etienne
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "client.h"

int		help_func(__attribute__((unused)) t_client *client,
			  __attribute__((unused)) t_cmd *cmd)
{
  printf("%sHelp :%s\n", COLOR_RED, COLOR_RESET);
  printf("%sls%s              : list all files of the "
	 "current server working directory\n", COLOR_BLUE, COLOR_RESET);
  printf("%spwd%s             : display the current "
	 "serveur working directory\n", COLOR_BLUE, COLOR_RESET);
  printf("%scd  <directory>%s : change server "
	 "working directory\n", COLOR_BLUE, COLOR_RESET);
  printf("%sget <file>%s      : transfert server file "
	 "to the current local working directory\n", COLOR_BLUE, COLOR_RESET);
  printf("%sput <file>%s      : transfert local file "
	 "to the current server working directory\n", COLOR_BLUE, COLOR_RESET);
  return (EXIT_SUCCESS);
}

int		other_func(t_client *client, t_cmd *cmd)
{
  int		ret;
  t_data	data;

  memset(&data, 0, sizeof(data));
  if (send_cmd_serv(client->sockfd, cmd) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  ret = read(client->sockfd, &data, sizeof(data));
  while (ret > 0 && ret == sizeof(data))
    {
      printf("%s\n", data.data);
      if (data.flags == MSG_END)
	break;
      ret = read(client->sockfd, &data, sizeof(data));
    }
  if (ret < 0 || ret != sizeof(data))
    {
      perror("read error");
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}
