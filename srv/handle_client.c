/*
** handle_client.c for handle_client in /home/debas_e/Project/System_Unix/PSU_2013_myftp/srv
**
** Made by Etienne
** Login   <debas_e@epitech.net>
**
** Started on  Fri Apr 11 23:54:50 2014 Etienne
** Last update Fri Apr 11 23:56:48 2014 Etienne
*/

#include <string.h>
#include <stdlib.h>
#include "serveur.h"

static int		init_serv_struct(t_serveur *serveur, int sockfd,
					 struct sockaddr_in *cli_addr)
{
  char			*path;

  serveur->sockfd = sockfd;
  serveur->cli_addr = cli_addr;
  path = realpath("./", NULL);
  if (!path)
    {
      perror("realpath");
      return (EXIT_FAILURE);
    }
  strncpy(serveur->base_pwd, path, PATH_MAX);
  strncpy(serveur->current_pwd, "/", PATH_MAX);
  return (EXIT_SUCCESS);
}

void			handle_client(int sockfd, struct sockaddr_in *cli_addr)
{
  t_cmd			cmd;
  int			ret;
  t_serveur		serveur;

  printf("server: got connection from %s\n", inet_ntoa(cli_addr->sin_addr));
  init_serv_struct(&serveur, sockfd, cli_addr);
  while (1)
    {
      memset(&cmd, 0, sizeof(cmd));
      ret = read(sockfd, &cmd, sizeof(cmd));
      if (ret <= 0)
	{
	  printf("client exited\n");
	  return;
	}
      if (run_cmd_client(&serveur, &cmd) == EXIT_FAILURE)
	return ;
    }
}
