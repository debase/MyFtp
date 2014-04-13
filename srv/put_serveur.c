/*
** put_serveur.c for put_serveur in /home/debas_e/Project/System_Unix/PSU_2013_myftp
**
** Made by Etienne
** Login   <debas_e@epitech.net>
**
** Started on  Fri Apr 11 20:14:33 2014 Etienne
** Last update Sun Apr 13 19:18:12 2014 Etienne
*/

#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "serveur.h"

static int	get_info_file(t_data *data, t_serveur *serveur)
{
  int		ret;

  memset(data, 0, sizeof(*data));
  ret = get_data(serveur->sockfd, data, sizeof(*data));
  if (ret < 0)
    {
      perror("read");
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}

static int	create_file(t_data *data, int sockfd)
{
  int		fd;

  if ((fd = open(data->data, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
    {
      fprintf(stderr, "%s%s%s", COLOR_RED, strerror(errno), COLOR_RESET);
      close(sockfd);
      exit(EXIT_FAILURE);
    }
  return (fd);
}

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

char		*put_serveur(t_serveur *serveur,
			     __attribute__((unused)) t_cmd *cmd)
{
  int		fd;
  t_data	data;
  char		buff[DATA_SIZE];
  size_t	rcv;
  ssize_t	ret;

  rcv = 0;
  if (get_info_file(&data, serveur) == EXIT_FAILURE)
    return ((void *)-1);
  if ((fd = create_file(&data, serveur->sockfd)) > 0)
    while (rcv != data.size)
      {
	ret = read(serveur->sockfd, buff, DATA_SIZE);
	rcv += ret;
	if (ret <= 0 && rcv != data.size)
	  {
	    fprintf(stderr, "%sread error : failded to receive file%s\n",
		    COLOR_RED, COLOR_RESET);
	    return ((void *)-1);
	  }
	if (write_in_file(buff, fd, ret) == -1)
	  return ((void *)-1);
      }
  return (NULL);
}
