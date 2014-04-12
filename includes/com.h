/*
** com.h for com in /home/debas_e/Project/System_Unix/PSU_2013_myftp/includes
**
** Made by Etienne
** Login   <debas_e@epitech.net>
**
** Started on  Wed Apr  9 13:36:18 2014 Etienne
** Last update Sat Apr 12 15:19:31 2014 Etienne
*/

#ifndef _COM_H_
# define _COM_H_

# define CMD_SIZE	4096
# define DATA_SIZE	4096
# define MSG_END	1
# define DATA		2

# define COLOR_BLUE	"\033[34m"
# define COLOR_RED	"\033[31m"
# define COLOR_GREEN	"\033[32m"
# define COLOR_RESET	"\033[0m"

typedef struct	s_cmd
{
  char		arg1[CMD_SIZE];
  char		arg2[CMD_SIZE];
}		t_cmd;

typedef struct	s_data
{
  size_t	size;
  char		data[DATA_SIZE];
  int		total_size; /* for binaries */
  char		flags;
}		t_data;

#endif /* !_COM_H_ */
