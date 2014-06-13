# Makefile de test #

CFLAGS="-Wno-deprecated -Wno-deprecated-declarations"

SRCS="srcs/g_main.c srcs/g_mdx_parser.c srcs/g_parsemdx.c \
		srcs/g_colors1.c \
		srcs/g_colors2.c \
		srcs/g_parse_png.c"

gcc -framework GLUT -framework OpenGL -framework Cocoa $CFLAGS $SRCS -o test -I includes/
