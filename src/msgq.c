/*
** msgq.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Mar  8 08:27:23 2015 chapui_s
** Last update Sun Mar  8 21:39:36 2015 chapui_s
*/

#include "lemipc.h"

int		get_msgq(t_info *info, int msg_id, int team_number, t_msg *msg)
{
  int		val;

  sem_lock(info);
  val = msgrcv(msg_id, &msg, sizeof(msg), team_number, IPC_NOWAIT);
  sem_unlock(info);
  return (val);
}

void		send_msgq(t_info *info, t_msg *msg)
{
  sem_lock(info);
  msgsnd(info->msg_id, msg, sizeof(*msg), IPC_NOWAIT);
  sem_unlock(info);
}
