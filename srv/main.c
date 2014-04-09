/*
** main.c for main in /home/debas_e/Project/System_Unix/PSU_2013_myftp
**
** Made by Etienne
** Login   <debas_e@epitech.net>
**
** Started on  Mon Apr  7 13:30:06 2014 Etienne
** Last update Wed Apr  9 16:06:23 2014 Etienne
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>
#include "serveur.h"

static t_serveur_asso_func g_assofunc[] =
  {
    /* {"get", get_serveur}, */
    /* {"put", put_serveur}, */
    {"ls", ls_serveur},
    /* {"cd", sc_serveur}, */
    /* {"pwd", pwd_serveur}, */
    {NULL, NULL}
  };

int			usage(char *pname)
{
  fprintf(stderr, "Usage : %s port\n", pname);
  return (EXIT_FAILURE);
}

int			init_server(char *port)
{
  int			sockfd;

  if ((sockfd = create_socket_server(port)) < 0)
    return (-1);
  if (listen(sockfd, 40) < 0)
    {
      perror("listen");
      return (-1);
    }
  return (sockfd);
}

int			send_result_client()
{

}

char			*ls_serveur(int sockfd, t_cmd *cmd)
{
  DIR			*dir;
  t_data		data;

  dir = opendir("./");
  if (dir == NULL)
    {
      perror("opendir");
      return ("Error : failed to opendir");
    }
  return ("Success");
}

int			run_cmd_client(int sockfd, t_cmd *cmd)
{
  int			i;
  char			*ret;

  i = 0;
  while (g_assofunc[i].cmd != NULL)
    {
      if (!strcmp(g_assofunc[i].cmd, cmd->arg1))
	{
	  ret = g_assofunc[i].func(sockfd, cmd);

	}
      i++;
    }
  return (EXIT_SUCCESS);
}

void			handle_client(int sockfd, struct sockaddr_in *cli_addr)
{
  t_cmd			cmd;
  int			ret;

  printf("server: got connection from %s\n", inet_ntoa(cli_addr->sin_addr));
  while (1)
    {
      memset(&cmd, 0, sizeof(cmd));
      ret = read(sockfd, &cmd, sizeof(cmd));
      if (ret <= 0)
	{
	  printf("client exited\n");
	  return;
	}
      run_cmd_client(sockfd, &cmd);
    }
}

int			main(int ac, char *argv[1])
{
  struct sockaddr_in	cli_addr;
  int			sockfd, clilen, newsockfd, childpid;

  if (ac != 2)
    return (usage(argv[0]));
  if ((sockfd = init_server(argv[1])) < 0)
    return (EXIT_FAILURE);
  while (1)
    {
      clilen = sizeof(cli_addr);
      errno = 0;
      newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t *)&clilen);
      if (newsockfd < 0)
	{
	  perror("listen");
	  return (EXIT_FAILURE);
	}
      if ((childpid = fork()) < 0)
	{
	  perror("fork");
	  return (EXIT_FAILURE);
	}
      else if (childpid == 0)
	{
	  close(sockfd);
	  handle_client(newsockfd, &cli_addr);
	  close(newsockfd);
	  exit(EXIT_SUCCESS);
	}
      close(newsockfd);
    }
  close(sockfd);
  return (0);
}
