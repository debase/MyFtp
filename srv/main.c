/*
** main.c for main in /home/debas_e/Project/System_Unix/PSU_2013_myftp
**
** Made by Etienne
** Login   <debas_e@epitech.net>
**
** Started on  Mon Apr  7 13:30:06 2014 Etienne
** Last update Sun Apr 13 00:59:35 2014 Etienne
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "serveur.h"

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

int			send_result_client(int sockfd, t_data *data)
{
  int			ret;

  ret = write(sockfd, data, sizeof(*data));
  if (ret != sizeof(*data) || ret < 0)
    {
      perror("write");
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}

int			manage_socket(int newsockfd, int sockfd,
				      struct sockaddr_in *cli_addr)
{
  pid_t			childpid;

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
      handle_client(newsockfd, cli_addr);
      close(newsockfd);
      exit(EXIT_SUCCESS);
    }
  return (EXIT_SUCCESS);
}

int			main(int ac, char *argv[1])
{
  struct sockaddr_in	cli_addr;
  int			sockfd;
  int			clilen;
  int			newsockfd;

  if (ac != 2)
    return (usage(argv[0]));
  if ((sockfd = init_server(argv[1])) < 0)
    return (EXIT_FAILURE);
  while (1)
    {
      clilen = sizeof(cli_addr);
      newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr,
			 (socklen_t *)&clilen);
      if (manage_socket(newsockfd, sockfd, &cli_addr))
	return (EXIT_FAILURE);
      close(newsockfd);
    }
  close(sockfd);
  return (0);
}
