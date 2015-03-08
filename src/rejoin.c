/*
** rejoin.c for src in /home/glubzite/rendu/Lemipc/src
**
** Made by Glubzite
** Login   <glubzite@epitech.net>
**
** Started on  Sun Mar  8 02:47:47 2015 Glubzite
** Last update Sun Mar  8 04:05:38 2015 Glubzite
*/

#define abs(x) ((x) < 0 ? - (x) : (x))

void	rejoin(int pos_xa, int pos_ya, int pos_xb, int pos_yb)
{
  int	move;

  if (pos_xa != pos_xb)
    {
      if (pos_xa < pos_xb) /* Incrementation du joueur sur l'axe X */
	{
	  if (check_move(pos_xa + 1, pos_ya) == 0) /* Vérification de la case à droite */
	    ++pos_xa;
	  else /* Si je peux pas bouger je dois bouger sur l'autre axe */
	    {
	      if (pos_ya < pos_yb)
		{
		  if (check_move(pos_xa, pos_ya + 1) == 0)
		    ++pos_ya;
		  else
		    {
		      if(check_move(pos_xa - 1, pos_ya) == 0) /* Check un move en arrière */
			--pos_xa;
		      else if (check_move(pos_xa, pos_ya - 1) == 0)/* Check l'autre move en arrière si celui d'avant est bloqué */
			--pos_ya;
		      else
			return 0; /* le joueur est bloqué */
		    }
		}
	    }
	}
      else if (pos_xa > pos_xb) /* et c'est reparti pour le meme bail */
	return 0;
    }
  else if (pos_ya != pos_yb) /* et encore pareil en changeant le déplacement */
    return (0);
}
