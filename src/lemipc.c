/*
** lemipc.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Mar  5 19:24:41 2015 chapui_s
** Last update Sun Mar  8 07:35:50 2015 chapui_s
*/

#include "lemipc.h"

void			sem_lock(t_info *info)
{
  struct sembuf		sops;

  sops.sem_num = 0;
  sops.sem_flg = 0;
  sops.sem_op = -1;
  semop(info->sem_id, &sops, 1);
}

void			sem_unlock(t_info *info)
{
  struct sembuf		sops;

  sops.sem_num = 0;
  sops.sem_flg = 0;
  sops.sem_op = 1;
  semop(info->sem_id, &sops, 1);
}

void		set_connected(t_info *info, int set)
{
  sem_lock(info);
  info->space->nb_connected += set;
  sem_unlock(info);
}

int		get_connected(t_info *info)
{
  int		tmp;

  sem_lock(info);
  tmp = info->space->nb_connected;
  sem_unlock(info);
  return (tmp);
}

void		down_the_arms(t_info *info)
{
  if (info->is_first && !(get_connected(info)))
  {
    msgctl(info->msg_id, IPC_RMID, (struct msqid_ds*)0);
    semctl(info->sem_id, 1, IPC_RMID);
    shmctl(info->shm_id, IPC_RMID, (struct shmid_ds*)0);
  }
}

char		get_battlefield(t_info *info, int x, int y)
{
  char		tmp;

  x = (x < 0) ? (0) : (x % SIZE_X);
  y = (y < 0) ? (0) : (y % SIZE_Y);
  sem_lock(info);
  tmp = info->map[(y * SIZE_Y + x) % SIZE_MAP];
  sem_unlock(info);
  return (tmp);
}

void		set_battlefield(t_info *info, int x, int y, char value)
{
  x = (x < 0) ? (0) : (x % SIZE_X);
  y = (y < 0) ? (0) : (y % SIZE_Y);
  sem_lock(info);
  info->map[(y * SIZE_Y + x) % SIZE_MAP] = value;
  sem_unlock(info);
}

void		place_this_spartiate(t_info *info)
{
  int		x;
  int		y;

  x = rand() % SIZE_X;
  y = rand() % SIZE_Y;
  while (get_battlefield(info, x, y) != 0)
  {
    x += 1;
    if (!(x % SIZE_X))
      y += 1;
  }
  info->x = x % SIZE_X;
  info->y = y % SIZE_Y;
  set_battlefield(info, x, y, info->team_number);
}

int		prepare_for_battle(t_info *info)
{
  if (get_map(info) == -1)
    return (-1);
  if (get_sem(info) == -1)
    return (-1);
  if (get_msg(info) == -1)
    return (-1);
  if (get_connected(info) > (int)SIZE_MAP / 2)
  {
    printf("Ouch.. They block the door :-O I can't go in !\n");
    printf("Let me go home ! *call his mother*\n");
    down_the_arms(info);
    return (-1);
  }
  set_connected(info, ONE_MORE);
  info->i_am_alive = 1;
  place_this_spartiate(info);
  if (info->is_first)
    printf("\033[H\033[J");
#ifdef DEBUG
  printf("Ready to fight ! x: %d y: %d Bring me wine !\n", info->x, info->y);
#else
  printf("Ready to fight ! Bring me wine and whores !\n");
#endif
  return (0);
}

int		am_i_surrounded(t_info *info, int nb_attackers)
{
  int		x;
  int		id;

  x = ((info->x - 1) < 0) ? (0) : (info->x - 1);
  while (x < info->x + 1 && x < SIZE_X)
  {
    if (info->y + 1 < SIZE_Y)
      if ((id = get_battlefield(info, x, info->y + 1)) != 0
	  && id != info->team_number)
	nb_attackers += 1;
    if (info->y - 1 >= 0)
      if ((id = get_battlefield(info, x, info->y - 1)) != 0
	  && id != info->team_number)
	nb_attackers += 1;
    x += 1;
  }
  if (info->x > 0 && (id = get_battlefield(info, info->x - 1, info->y)) != 0
      && id != info->team_number)
    nb_attackers += 1;
  if (info->x < SIZE_X - 1
      && (id = get_battlefield(info, info->x + 1, info->y)) != 0
      && id != info->team_number)
    nb_attackers += 1;
  return ((nb_attackers >= 2) ? (1) : (0));
}

int		can_i_fight(t_info *info)
{
  if (info->i_am_alive && am_i_surrounded(info, 0))
  {
    info->i_am_alive = 0;
    printf("FUCK ! They killed me ! It wasn't my war !\n");
    set_battlefield(info, info->x, info->y, 0);
    return (0);
  }
  else if (info->i_am_alive)
  {
    printf("Still alive !\n");
    return (1);
  }
  return (0);
}

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
  msgsnd(info->msg_id, msg, sizeof(*msg), 0);
  sem_unlock(info);
}

int		is_enemy_still_there(t_info *info,
				     t_enemy *stupid_guy,
				     char *s)
{
  char		val;
  int		x;
  int		y;

  x = atoi(strtok(s, ":"));
  y = atoi(strtok(s, ":"));
  val = get_battlefield(info, x, y);
  if (val != 0 && val != info->team_number)
  {
    stupid_guy->x = x;
    stupid_guy->y = y;
    return (1);
  }
  else
  {
    return (0);
  }
}

int		listen_brothers(t_info *info,
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

int		scan_map(t_info *info,
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

void		send_position_to_brothers(t_info *info,
					  t_enemy *stupid_guy,
					  int team_number)
{
  t_msg		msg;

  msg.mtype = team_number;
  sprintf(&(msg.str[0]), "%d:%d", stupid_guy->x, stupid_guy->y);
  send_msgq(info, &msg);
}

int		find_enemy(t_info *info, t_enemy *stupid_guy)
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

void		print_battlefield(t_info *info)
{
  char		val;
  int		x;
  int		y;

  y = 0;
  printf("\033[H\033[J\n");
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
