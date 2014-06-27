/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_display_hud.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmielcza <tmielcza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 03:23:59 by tmielcza          #+#    #+#             */
/*   Updated: 2014/06/27 04:38:21 by dmansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx_gl.h"

t_pol		g_police[] =
{
	{'a', _ta},
	{'b', _tb},
	{'c', _tc},
	{'d', _td},
	{'e', _te},
	{'f', _tf},
	{'g', _tg},
	{'h', _th},
	{'i', _ti},
	{'j', _tj},
	{'k', _tk},
	{'l', _tl},
	{'m', _tm},
	{'n', _tn},
	{'o', _to},
	{'p', _tp},
	{'q', _tq},
	{'r', _tr},
	{'s', _ts},
	{'t', _tt},
	{'u', _tu},
	{'v', _tv},
	{'w', _tw},
	{'x', _tx},
	{'y', _ty},
	{'z', _tz},
	{'A', _tA},
	{'B', _tB},
	{'C', _tC},
	{'D', _tD},
	{'E', _tE},
	{'F', _tF},
	{'G', _tG},
	{'H', _tH},
	{'I', _tI},
	{'J', _tJ},
	{'K', _tK},
	{'L', _tL},
	{'M', _tM},
	{'N', _tN},
	{'O', _tO},
	{'P', _tP},
	{'Q', _tQ},
	{'R', _tR},
	{'S', _tS},
	{'T', _tT},
	{'U', _tU},
	{'V', _tV},
	{'W', _tW},
	{'X', _tX},
	{'Y', _tY},
	{'Z', _tZ},
	{'0', _t0},
	{'1', _t1},
	{'2', _t2},
	{'3', _t3},
	{'4', _t4},
	{'5', _t5},
	{'6', _t6},
	{'7', _t7},
	{'8', _t8},
	{'9', _t9},
	{' ', 1},
};


static void	display_rect(int x, int y, int lettre)
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

static void	display_words(float x, float y, char *str)
{
	int		i;

	while (*str)
	{
		i = 0;
		while (g_police[i].c != *str && g_police[i].c != ' ')
			i++;
		if (g_police[i].c == ' ')
		{
			x++;
			str++;
			continue;
		}
		display_rect(x++, y, g_police[i].n);
		str++;
	}
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
	display_words(-20, 19, "connasse!!!pute");
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}
