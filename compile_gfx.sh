# Makefile de test #

CFLAGS="-Wno-deprecated -Wno-deprecated-declarations"

SRCS="srcs/gfx/g_main.c srcs/gfx/g_mdx_parser.c srcs/gfx/g_parsemdx.c \
		srcs/gfx/g_colors1.c \
		srcs/gfx/g_colors2.c \
		srcs/gfx/g_parse_png.c"

gcc -framework GLUT -framework OpenGL -framework Cocoa $CFLAGS $SRCS -o test -I includes/
