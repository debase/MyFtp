/*
** com.h for com in /home/debas_e/Project/System_Unix/PSU_2013_myftp/includes
**
** Made by Etienne
** Login   <debas_e@epitech.net>
**
** Started on  Wed Apr  9 13:36:18 2014 Etienne
** Last update Wed Apr  9 15:46:03 2014 Etienne
*/

#ifndef _COM_H_
# define _COM_H_

# define CMD_SIZE	4096
# define DATA_SIZE	4096
# define MSG_END	1
# define DATA		2

typedef struct	s_cmd
{
  char		arg1[CMD_SIZE];
  char		arg2[CMD_SIZE];
}		t_cmd;

typedef struct	s_data
{
  int		size;
  char		data[DATA_SIZE];
  char		flags;
}		t_data;

#endif /* !_COM_H_ */
