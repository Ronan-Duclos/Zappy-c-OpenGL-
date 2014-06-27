/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_display_hud.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmielcza <tmielcza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 03:23:59 by tmielcza          #+#    #+#             */
/*   Updated: 2014/06/27 07:28:23 by tmielcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx_gl.h"

void		display_rect(int x, int y, int lettre)
{
	static GLfloat	vertices[] = {

	0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 0.0,
	0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0};
	glPushMatrix();
	glLoadIdentity();
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, vertices + 12);
	glBindTexture(GL_TEXTURE_2D, g_env->textures[lettre]);
	glScalef(0.05, 0.05, 0);
	glTranslatef(x, y, 0);
	glBegin(GL_QUADS);
	{
		glArrayElement(0);
		glArrayElement(1);
		glArrayElement(2);
		glArrayElement(3);
	}
	glEnd();
	glPopMatrix();
}

static void	display2(t_npc *npc)
{
	char	*str;

	str = ft_itoa(npc->inv[_sibur]);
	display_words(-20, 15, "Sibur");
	display_words(-10, 15, str);
	free(str);
	str = ft_itoa(npc->inv[_mendiane]);
	display_words(-20, 14, "Mendiane");
	display_words(-10, 14, str);
	free(str);
	str = ft_itoa(npc->inv[_phiras]);
	display_words(-20, 13, "Phiras");
	display_words(-10, 13, str);
	free(str);
	str = ft_itoa(npc->inv[_thystame]);
	display_words(-20, 12, "Thystame");
	display_words(-10, 12, str);
	free(str);
}

static void	display_inv(void)
{
	t_npc	*npc;
	char	*str;

	npc = &g_env->npc[g_env->curr_npc];
	if (npc->lvl == 0)
		return ;
	str = ft_itoa(npc->id);
	display_words(-20, 19, "ID");
	display_words(-10, 19, str);
	free(str);
	str = ft_itoa(npc->inv[_food]);
	display_words(-20, 18, "Food");
	display_words(-10, 18, str);
	free(str);
	str = ft_itoa(npc->inv[_linemate]);
	display_words(-20, 17, "Linemate");
	display_words(-10, 17, str);
	free(str);
	str = ft_itoa(npc->inv[_deraumere]);
	display_words(-20, 16, "Deraumere");
	display_words(-10, 16, str);
	free(str);
	display2(npc);
}

static void	select_player(void)
{
	int		i;

	if (g_env->curr_npc == 0)
		i = 0;
	else
		i = g_env->curr_npc;
	if (g_env->npc[i].lvl != 0)
		return ;
	i++;
	while (i != g_env->curr_npc && g_env->npc[i].lvl == 0)
	{
		i = (i + 1) % NPCS_MAX;
	}
	g_env->curr_npc = i;
	return ;
}

void		display_footer(void)
{
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, 0, 100);
	glMatrixMode(GL_MODELVIEW);
	select_player();
	display_inv();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}
