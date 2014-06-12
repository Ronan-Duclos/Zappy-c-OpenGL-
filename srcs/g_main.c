/* Main de test GLUT by Paul-le-poulpe */

#include <GLUT/glut.h>
#include <math.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <strings.h>
#include <libft.h>
#include "testopengl.h"
#include "common.h"
#include "mdx.h"

void	normalize(GLdouble vec[3])
{
	double	mag;

	mag = MAG(vec);
	vec[0] /= mag;
	vec[1] /= mag;
	vec[2] /= mag;
}

void	getdir(GLdouble o[3], GLdouble dir[3])
{
	dir[0] -= o[0];
	dir[1] -= o[1];
	dir[2] -= o[2];
}

void	ft_color_white(void)
{
	static	GLfloat mat_specular[] = { 0.6, 0.6, 0.6, 1.0 };
	static	GLfloat mat_diffuse[] = { 0.9, 0.9, 0.9, 1.0 };
	static	GLfloat mat_ambient[] = { 0.5, 0.5, 0.5, 1.0 };

	glNewList(g_env->colors[_white], GL_COMPILE);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
	glEndList();
}

void	ft_color_red(void)
{
	static	GLfloat mat_specular[] = { 0.6, 0.6, 0.6, 1.0 };
	static	GLfloat mat_diffuse[] = { 0.9, 0.0, 0.0, 1.0 };
	static	GLfloat mat_ambient[] = { 0.5, 0.2, 0.2, 1.0 };

	glNewList(g_env->colors[_red], GL_COMPILE);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
	glEndList();
}

void	ft_color_blue(void)
{
	static	GLfloat mat_specular[] = { 0.6, 0.6, 0.6, 1.0 };
	static	GLfloat mat_diffuse[] = { 0.0, 0.0, 0.9, 1.0 };
	static	GLfloat mat_ambient[] = { 0.2, 0.2, 0.5, 1.0 };

	glNewList(g_env->colors[_blue], GL_COMPILE);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
	glEndList();
}

void	ft_color_green(void)
{
	static	GLfloat mat_specular[] = { 0.6, 0.6, 0.6, 1.0 };
	static	GLfloat mat_diffuse[] = { 0.0, 0.9, 0.0, 1.0 };
	static	GLfloat mat_ambient[] = { 0.2, 0.5, 0.2, 1.0 };

	glNewList(g_env->colors[_green], GL_COMPILE);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
	glEndList();
}

void	ft_color_yellow(void)
{
	static	GLfloat mat_specular[] = { 0.6, 0.6, 0.6, 1.0 };
	static	GLfloat mat_diffuse[] = { 0.9, 0.9, 0.0, 1.0 };
	static	GLfloat mat_ambient[] = { 0.5, 0.5, 0.2, 1.0 };

	glNewList(g_env->colors[_yellow], GL_COMPILE);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
	glEndList();
}

void	ft_color_pink(void)
{
	static	GLfloat mat_specular[] = { 0.6, 0.6, 0.6, 1.0 };
	static	GLfloat mat_diffuse[] = { 0.9, 0.0, 0.9, 1.0 };
	static	GLfloat mat_ambient[] = { 0.5, 0.2, 0.5, 1.0 };

	glNewList(g_env->colors[_pink], GL_COMPILE);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
	glEndList();
}

void	ft_color_cyan(void)
{
	static	GLfloat mat_specular[] = { 0.6, 0.6, 0.6, 1.0 };
	static	GLfloat mat_diffuse[] = { 0.0, 0.9, 0.9, 1.0 };
	static	GLfloat mat_ambient[] = { 0.2, 0.5, 0.5, 1.0 };

	glNewList(g_env->colors[_cyan], GL_COMPILE);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
	glEndList();
}

void	map_intersection(GLdouble *inter, GLdouble *a, GLdouble *b)
{
	double	t;

	getdir(a, b);
	normalize(b);
	t = (1.0 * -a[1]) / (1.0 * b[1]);
	inter[0] = a[0] + b[0] * t;
	inter[1] = a[1] + b[1] * t;
	inter[2] = a[2] + b[2] * t;
}

/*
**
*/
void    pos(void)
{
	GLdouble	model[16];
	GLdouble	proj[16];
	GLint		view[4];
	GLdouble	posz0[3];
	GLdouble	posz1[3];

	glGetDoublev(GL_MODELVIEW_MATRIX, model);
	glGetDoublev(GL_PROJECTION_MATRIX, proj);
	glGetIntegerv(GL_VIEWPORT, view);
	gluUnProject(0, 0, 0, model, proj, view, posz0 + 0, posz0 + 1, posz0 + 2);
	gluUnProject(0, 0, 1, model, proj, view, posz1 + 0, posz1 + 1, posz1 + 2);
	map_intersection(g_env->realpos00, posz0, posz1);
	gluUnProject(0, g_env->winy, 0, model, proj, view, posz0 + 0, posz0 + 1,
				posz0 + 2);
	gluUnProject(0, g_env->winy, 1, model, proj, view, posz1 + 0, posz1 + 1,
				posz1 + 2);
	map_intersection(g_env->realpos0y, posz0, posz1);
	gluUnProject(g_env->winx, g_env->winy, 0, model, proj, view, posz0 + 0,
				posz0 + 1, posz0 + 2);
	gluUnProject(g_env->winx, g_env->winy, 1, model, proj, view, posz1 + 0,
				 posz1 + 1, posz1 + 2);
	map_intersection(g_env->realposxy, posz0, posz1);
}
/*
**	La je mets un oeuf. PushMatrix() pour bouger sans changer la matrice du
**	dessous, BindBuffer pour me placer sur le buffer d'indexes, CallList pour
**	appeler la liste des modifications de matrices, et je draw. Eh ouais.
*/

void	display_egg(int i)
{
	glPushMatrix();
	glTranslatef(1.9 / 16.0 * (i % 16) + 0.1, 0.0, 1.9 / 16 * (i / 16) + 0.1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_env->vbo_indx);
	glCallList(g_env->lists);
	glDrawElements(GL_TRIANGLES, g_mdx.chunks[_pvtx].nb, GL_UNSIGNED_SHORT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glPopMatrix();
}
/*
**	La je pose les oeuf. Enfin les pierres. De toutes les couleurs.
*/

void	display_items(int sq)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (j < 7)
	{
		glCallList(g_env->colors[j]);
		while (i < CASE_MAX_ITEMS)
		{
			if (g_env->sq[sq].grid[i] == j)
			{
				display_egg(i);
			}
			i++;
		}
		i = 0;
		j++;
	}
}
/*
**	Je fous une case. Donc je donne a chaque fois une coordonnee de texture,
**	 une normale, puis le vertex qui leur est associé (glArrayElement).
**	Fonction un peu crade, a revoir. Eventuellement.
*/

void	display_grid()
{
	static GLfloat	vertices[] = {

	-1.0, 0.05, -1.0, 1.0, 0.05, -1.0, 1.0, 0.05, 1.0, -1.0, 0.05, 1.0
	};
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glBegin(GL_LINE_LOOP);
	{
		glColor3f(1.0, 1.0, 0.0);
		glArrayElement(0);
		glArrayElement(1);
		glArrayElement(2);
		glArrayElement(3);
	}
	glEnd();
}

void	display_square(int i)
{
	static GLfloat	vertices[] = {

	-1.0, 0.0, -1.0, 1.0, 0.0, -1.0, 1.0, 0.0, 1.0, -1.0, 0.0, 1.0,
	0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0
	};
	glNormalPointer(GL_FLOAT, 0, vertices + 12);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glBegin(GL_QUADS);
	{
		glTexCoord2f((float)(i % 8) / 8.0, (4.0 - i / 8) / 4.0);
		glArrayElement(0);
		glTexCoord2f((float)(i % 8 + 1) / 8.0, (4.0 - i / 8) / 4.0);
		glArrayElement(1);
		glTexCoord2f((float)(i % 8 + 1) / 8.0, (3.0 - i / 8) / 4.0);
		glArrayElement(2);
		glTexCoord2f((float)(i % 8) / 8.0, (3.0 - i / 8) / 4.0);
		glArrayElement(3);
	}
	glEnd();
}

void	display_all_squares(void)
{

}
/*
**	Boucle d'affichage de la map.
**	Je push une matrice, c'est a dire que qu'elle va se mettre en haut
**	de la pile et copier celle du dessous et devenir la matrice courante.
**	Je la modifie, je m'en sers, je la pop et elle se casse.
**	Ca permet de se situer plus precisement de repere en repere,
**	sans modifier les reperes precdents.
*/
void	display_map(void)
{
	int	i;

	i = 0;
	glCallList(g_env->colors[_white]);
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glBindTexture(GL_TEXTURE_2D, g_env->maptex);
	while (i < g_env->mapw * g_env->maph)
	{
		glPushMatrix();
		glTranslatef(i % g_env->mapw * 2.0, 0.0, i / g_env->mapw * 2.0);
		display_square((int)g_env->sq[i].tile);
		glPopMatrix();
		i++;
	}
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

	i = 0;
	glLineWidth(2.0);
	glDisable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_LIGHTING);
	while (i < g_env->mapw * g_env->maph)
	{
		glPushMatrix();
		glTranslatef(i % g_env->mapw * 2.0, 0.0, i / g_env->mapw * 2.0);
		display_grid();
		glPopMatrix();
		i++;
	}
	glEnable(GL_LIGHTING);
	glDisableClientState(GL_VERTEX_ARRAY);

	i = 0;
	glDisable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, g_env->vbo_vrtx);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, g_env->vbo_nrms);
	glNormalPointer(GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	while (i < g_env->mapw * g_env->maph)
	{
		if (g_env->realpos0y[0] > i % g_env->mapw * 2.0 + 1.0
			|| g_env->realposxy[0] < i % g_env->mapw * 2.0 - 1.0
			|| g_env->realposxy[2] > i / g_env->mapw * 2.0 + 1.0
			|| g_env->realpos00[2] < i / g_env->mapw * 2.0 - 1.0)
		{
			i++;
			continue ;
		}
		glPushMatrix();
		glTranslatef(i % g_env->mapw * 2.0, 0.0, i / g_env->mapw * 2.0);
		display_items(i);
		glPopMatrix();
		i++;
	}
	glDisableClientState(GL_NORMAL_ARRAY | GL_VERTEX_ARRAY);
}

/*
**	J'ouvre un fichier BMP et je le parse degueulassement
**	pour en faire une texture. C'est moche, faut le refaire
**	et pour les PNG, s'il vous plait, comme ca on a l'alpha.
*/
GLuint	ft_load_tex(char *file)
{
	int				fd;
	unsigned char	*data;
	int				*offset;
	int				*size;
	GLuint			tex;

	if (!(fd = open(file, O_RDONLY)))
		return (1);
	data = (unsigned char *)malloc(14 * sizeof(char));
	if (!read(fd, data, 14))
		return (1);
	offset = (int *)(data + 10);
	size = (int *)(data + 2);
	free(data);
	data = (unsigned char *)malloc((*size - 14) * sizeof(char));
	if (!read(fd, data, *size - 14))
		return (1);
	glGenTextures(1, &g_env->maptex);
	glBindTexture(GL_TEXTURE_2D, g_env->maptex);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, *(int *)(data + 4), *(int *)(data + 8),
				0, GL_BGR, GL_UNSIGNED_BYTE, &data[*offset - 14]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	return (0);
}

/*
**	Initialisation dans la structure globale (pas d'affichage)
*/
void	ft_put_stones(char tab[7], t_square *sq)
{
	int		amount;
	int		i;
	int		sect;
	int		tmp;

	i = 0;
	tmp = 0;
	amount = tab[0] + tab[1] + tab[2] + tab[3] + tab[4] + tab[5] + tab[6];
	if (amount == 0)
		return ;
	sect = CASE_MAX_ITEMS / amount;
	while (i < amount)
	{
		while (tab[tmp] == 0)
			tmp = (tmp + 1) % 7;
		sq->grid[i * sect + (rand() % sect)] = tmp;
		tab[tmp]--;
		i++;
		tmp = (tmp + 1) % 7;
	}
}

/*
**
*/
void	test_init_map(void)
{
	int		i;
	char	tab[7];
	int		j;

	i = 0;
	g_env->sq = (t_square *)malloc(g_env->maph * g_env->mapw * sizeof(t_square));
	memset(g_env->sq, -1, g_env->mapw * g_env->maph * sizeof(t_square)); // NON
	while (i / g_env->mapw < g_env->maph)
	{
		tab[0] = rand() % 5;
		tab[1] = rand() % 4;
		tab[2] = rand() % 3;
		tab[3] = rand() % 2;
		tab[4] = rand() % 2;
		tab[5] = rand() % 2;
		tab[6] = rand() % 2;
		ft_put_stones(tab, &g_env->sq[i]);
		j = rand() % 8;
		g_env->sq[i].tile = j + 4 + (j / 2 * 6);
		i++;
	}
}
/*
**	La je commence a dessiner des trucs.
**	Je clear tous mes buffers utilisé (en blanc), je place la "camera"
**	comme il faut (du moins je crois que c'est ce qui se passe..)
**	avec glTranslatef() et glRotatef(). Je Swap les buffers a la fin
**	(il y en a deux en fait) pour afficher celui sur lequel je viens d'ecrire.
*/

void	display(void)
{
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glRotatef(20.0, 1.0, 0.0, 0.0);
	glTranslatef(g_env->camtrans[0], g_env->camtrans[1], g_env->camtrans[2]);
	display_map();
	glutSwapBuffers();
}

void	speckey(int key, int xmouse, int ymouse)
{
	int			i;
	static int	tab[] = {

	GLUT_KEY_LEFT, FLAG_LEFT,
	GLUT_KEY_DOWN, FLAG_DOWN,
	GLUT_KEY_RIGHT, FLAG_RIGHT,
	GLUT_KEY_UP, FLAG_UP,
	0, 0};
	i = 0;
	while (tab[i] != 0 && tab[i] != key)
		i += 2;
	if (tab[i])
		g_env->keys |= tab[i + 1];
}

void	speckeyup(int key, int xmouse, int ymouse)
{
	int			i;
	static int	tab[] = {

	GLUT_KEY_LEFT, FLAG_LEFT,
	GLUT_KEY_DOWN, FLAG_DOWN,
	GLUT_KEY_RIGHT, FLAG_RIGHT,
	GLUT_KEY_UP, FLAG_UP,
	0, 0};
	i = 0;
	while (tab[i] != 0 && tab[i] != key)
		i += 2;
	if (tab[i])
		g_env->keys &= ~tab[i + 1];
}
/*
**	Fonction de redimensionnement de l'ecran. Viewport c'est les dimensions
**	de l'image finale par rapport a celle qu'on cree.
**	J'initialise la perspective avec gluPerspective (logique)
**	apres m'etre bien sur placé sur la pile des matrices de projection
**	(glMatrixMode() et glLoadIdentity() pour la mettre a 0).
*/

void	reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	g_env->winx = w;
	g_env->winy = h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void	init_light(void)
{
	static GLfloat	light_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
	static GLfloat	light_position[] = { 50.0, 150.0, 50.0, 0.0 };

	glShadeModel(GL_SMOOTH);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void	init_env(void)
{
	g_env->camtrans[0] = -0.5;
	g_env->camtrans[1] = -10.1;
	g_env->camtrans[2] = -30.0;
}

void	init_colors(void)
{
	g_env->colors[_white] = glGenLists(1);
	g_env->colors[_red] = glGenLists(1);
	g_env->colors[_blue] = glGenLists(1);
	g_env->colors[_green] = glGenLists(1);
	g_env->colors[_yellow] = glGenLists(1);
	g_env->colors[_pink] = glGenLists(1);
	g_env->colors[_cyan] = glGenLists(1);
	ft_color_white();
	ft_color_red();
	ft_color_blue();
	ft_color_green();
	ft_color_yellow();
	ft_color_pink();
	ft_color_cyan();
}

void	init(void)
{
	init_colors();
	init_light();
	init_env();
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glClearColor (1.0, 1.0, 1.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_RESCALE_NORMAL);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0);
	g_env->lists = glGenLists(1);
	glNewList(g_env->lists, GL_COMPILE);
	{
		glTranslatef(-1.0, -0.7, -1.0);
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glScalef(0.009, 0.009, 0.009);
	}
	glEndList();
}

void	idle(void)
{
	if (g_env->keys & FLAG_RIGHT)
		g_env->camtrans[0] += -0.2;
	if (g_env->keys & FLAG_LEFT)
		g_env->camtrans[0] += 0.2;
	if (g_env->keys & FLAG_UP)
		g_env->camtrans[2] += 0.2;
	if (g_env->keys & FLAG_DOWN)
		g_env->camtrans[2] += -0.2;
	if (g_env->keys)
		pos();
	glutPostRedisplay();
}

/*
**	Initialisation de glut...
*/

void	init_glut(int ac, char **av)
{
	glutInit(&ac, av);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(30, 30);
	glutInitWindowSize(SCR_WID, SCR_HGH);
	glutCreateWindow("*HOSHI* TESUTO DA YO NE~ *HOSHI*");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(speckey);
	glutSpecialUpFunc(speckeyup);
	glutIdleFunc(idle);
}

void	set_map_size(char **av)
{
	g_env->mapw = atoi(av[0]);
	g_env->maph = atoi(av[1]);
	if (!g_env->mapw || !g_env->maph)
	{
		printf("FUCK YOU\n");
		exit(1);
	}
}

int		get_params(int ac, char **av)
{
	if (ac != 3)
		return (printf("Usage: FUCK YOU\n"), 1);
	set_map_size(av + 1);
	return (0);
}

/*
**	Ah non c'est la que je m'occupe du vbo ...
*/

void	ft_vbo_from_mdx(t_mdx *mdx)
{
	glGenBuffers(1, &g_env->vbo_vrtx);
	glGenBuffers(1, &g_env->vbo_nrms);
	glGenBuffers(1, &g_env->vbo_indx);
	glBindBuffer(GL_ARRAY_BUFFER, g_env->vbo_vrtx);
	glBufferData(GL_ARRAY_BUFFER, mdx->chunks[_vrtx].nb * sizeof(float) * 3,
			mdx->chunks[_vrtx].data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, g_env->vbo_nrms);
	glBufferData(GL_ARRAY_BUFFER, mdx->chunks[_nrms].nb * sizeof(float) * 3,
			mdx->chunks[_nrms].data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_env->vbo_indx);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			mdx->chunks[_pvtx].nb * sizeof(uint16_t) * 3,
			mdx->chunks[_pvtx].data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

int		main(int ac, char **av)
{
	t_env		env;
	t_mdx		mdx;
	char		*tmp;

	srand(time(NULL));
	bzero(&env, sizeof(t_env)); ////Attation
	g_env = &env;
	if (get_params(ac, av))
		return (1);
	init_glut(ac, av);
	test_init_map();
	tmp = ft_strjoin(INC_FILES, "Lords_grassDark2.bmp");
	ft_load_tex(tmp);
	free(tmp);
	tmp = ft_strjoin(INC_FILES, "CrystalShard.mdx");
	get_model_from_mdx(tmp, &g_mdx);
	free(tmp);
	ft_vbo_from_mdx(&g_mdx);
	init();
	glutMainLoop();
	return (0);
}
