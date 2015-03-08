/*
** find_and_fuck.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Mar  8 08:30:23 2015 chapui_s
** Last update Sun Mar  8 08:31:06 2015 chapui_s
*/

#include "lemipc.h"

static int	listen_brothers(t_info *info,
				t_enemy *stupid_guy,
				int msg_id,
				int team_number)
{
  t_msg		msg;

  errno = 0;
  while (errno != ENOMSG)
  {
    if (!get_msgq(info, msg_id, team_number, &msg))
    {
      if (is_enemy_still_there(info, stupid_guy, &(msg.str[0])))
      {
	send_msgq(info, &msg);
	return (1);
      }
    }
    else
      return (0);
  }
  return (0);
}

static int	scan_map(t_info *info,
			 t_enemy *stupid_guy,
			 int team_number)
{
  char		val;
  int		x;
  int		y;

  y = 0;
  while (y < SIZE_Y)
  {
    x = 0;
    while (x < SIZE_X)
    {
      val = get_battlefield(info, x, y);
      if (val != 0 && val != team_number)
      {
	stupid_guy->x = x;
	stupid_guy->y = y;
	return (1);
      }
      x += 1;
    }
    y += 1;
  }
  return (0);
}

static void	send_position_to_brothers(t_info *info,
					  t_enemy *stupid_guy,
					  int team_number)
{
  t_msg		msg;

  msg.mtype = team_number;
  sprintf(&(msg.str[0]), "%d:%d", stupid_guy->x, stupid_guy->y);
  send_msgq(info, &msg);
}

static int	find_enemy(t_info *info, t_enemy *stupid_guy)
{
  if (listen_brothers(info, stupid_guy, info->msg_id, info->team_number))
  {
    return (1);
  }
  else if (scan_map(info, stupid_guy, info->team_number))
  {
    send_position_to_brothers(info, stupid_guy, info->team_number);
    return (1);
  }
  else
  {
    return (0);
  }
}

int		find_enemy_and_fuck_him(t_info *info)
{
  t_enemy	stupid_guy;

  if (find_enemy(info, &stupid_guy))
  {
    printf("I found an asshole to kick\n");
    sem_lock(info);
    move(info, &(info->x), &(info->y), &stupid_guy);
    sem_unlock(info);
  }
  else
  {
    sem_lock(info);
    move_random(info, &(info->x), &(info->y));
    sem_unlock(info);
  }
  return (0);
}
