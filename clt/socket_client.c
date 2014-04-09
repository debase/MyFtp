/*
** main.c for main in /home/debas_e/Project/System_Unix/PSU_2013_myftp
**
** Made by Etienne
** Login   <debas_e@epitech.net>
**
** Started on  Mon Apr  7 23:39:28 2014 Etienne
** Last update Tue Apr  8 14:08:58 2014 Etienne
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"

int			find_socketfd(struct addrinfo *result)
{
  int			fd_socket;
  struct addrinfo	*save;

  save = result;
  while (result)
    {
      fd_socket = socket(result->ai_family, result->ai_socktype,
			 result->ai_protocol);
      if (fd_socket > 0)
	{
	  if (connect(fd_socket, result->ai_addr, result->ai_addrlen) != -1)
	    break ;
	  close(fd_socket);
	}
      result = result->ai_next;
    }
  if (result == NULL)
    {
      fprintf(stderr, "Unable to connect to any address\n");
      return (-1);
    }
  freeaddrinfo(save);
  return (fd_socket);
}

int			create_socket_client(const char *host, const char *port)
{
  struct addrinfo	hint;
  struct addrinfo	*result;
  int			getaddr_ret;

  memset(&hint, 0, sizeof (hint));
  hint.ai_family = AF_INET;
  hint.ai_socktype = SOCK_STREAM;
  if ((getaddr_ret = getaddrinfo(host, port, &hint, &result)) != 0)
    {
      fprintf(stderr, "getaddrinfo : %s\n", gai_strerror(getaddr_ret));
      return (-1);
    }
  return (find_socketfd(result));
}
