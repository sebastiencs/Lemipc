/*
** lemipc.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Mar  5 19:24:41 2015 chapui_s
** Last update Sun Mar  8 08:31:30 2015 chapui_s
*/

#include "lemipc.h"

void		down_the_arms(t_info *info)
{
  if (info->is_first && !(get_connected(info)))
  {
    msgctl(info->msg_id, IPC_RMID, (struct msqid_ds*)0);
    semctl(info->sem_id, 1, IPC_RMID);
    shmctl(info->shm_id, IPC_RMID, (struct shmid_ds*)0);
  }
}

void		manage_sig(t_info *param)
{
  static t_info *info;

  if (!param)
  {
    msgctl(info->msg_id, IPC_RMID, (struct msqid_ds*)0);
    semctl(info->sem_id, 1, IPC_RMID);
    shmctl(info->shm_id, IPC_RMID, (struct shmid_ds*)0);
  }
  else
    info = param;
}

void		sig_handler(int sig)
{
  (void)sig;
  manage_sig((t_info*)0);
  exit(0);
}

void		my_putchar(char c)
{
  write(1, &c, 1);
}

void		my_putnbr(int n)
{
  if (n >= 10)
    my_putnbr(n / 10);
  my_putchar((n % 10) + '0');
}

void		my_putstr(char *s)
{
  if (s)
    write(1, s, strlen(s));
}

void		print_battlefield(t_info *info)
{
  char		val;
  int		x;
  int		y;

  y = 0;
  my_putstr("\033[H\033[J");
  while (y < SIZE_Y)
  {
    x = 0;
    while (x < SIZE_X)
    {
      val = get_battlefield(info, x, y);
      if (val != 0)
	my_putnbr(val);
      else
	my_putchar('.');
      x += 1;
    }
    my_putchar('\n');
    y += 1;
  }
}

int		main(int argc, char **argv)
{
  t_info	info;

  signal(SIGINT, sig_handler);
  if (get_info(argc, argv, &info) == -1)
    return (-1);
  srand(time((time_t*)0));
  manage_sig(&info);
  if (prepare_for_battle(&info) == -1)
    return (-1);
  manage_sig(&info);
  while (AM_I_ALIVE)
  {
    if (can_i_fight(&info))
    {
      find_enemy_and_fuck_him(&info);
    }
    if (info.is_first)
      print_battlefield(&info);
    sleep(1);
  }
  if (info.is_first)
  {
    msgctl(info.msg_id, IPC_RMID, (struct msqid_ds*)0);
    semctl(info.sem_id, 1, IPC_RMID);
    shmctl(info.shm_id, IPC_RMID, (struct shmid_ds*)0);
  }
  return (0);
}
