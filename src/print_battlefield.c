/*
** print_battlefield.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Mar  8 09:00:50 2015 chapui_s
** Last update Sun Mar  8 23:20:53 2015 chapui_s
*/

#ifndef SDL_OUTPUT

# include "lemipc.h"

static void	my_putchar(char c)
{
  write(1, &c, 1);
}

static void	my_putnbr(int n)
{
  if (n >= 10)
    my_putnbr(n / 10);
  my_putchar((n % 10) + '0');
}

static void	my_putstr(char *s)
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
      val = info->map[y * SIZE_Y + x];
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

#endif /* !SDL_OUTPUT */
