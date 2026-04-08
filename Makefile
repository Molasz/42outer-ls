NAME		= ft_ls

PRINTF		= libftprintf.a

LIBDIR		= printf

SRCS		= ft_ls.c

OBJS		= $(addprefix $(ODIR), $(SRCS:.c=.o))

SDIR		= src/

ODIR		= obj/

IDIR		= includes/

DEPS		= $(addprefix $(ODIR), $(SRCS:.c=.d))

CFLAGS		= -Wall -Wextra -Werror -MMD -Iincludes/ -Iprintf/

AR			= ar rcs

RM			= rm -rf

all:		dir ${NAME}

dir:
				$(MAKE) -C $(LIBDIR)
				mkdir -p $(ODIR)

obj/%.o:	src/%.c Makefile
				$(CC) $(CFLAGS) -c $< -o $@

${NAME}:	$(OBJS)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBDIR)/$(PRINTF)

bonus:		all

clean:
				make -C $(LIBDIR) clean
				$(RM) $(ODIR)

fclean:		
				make -C $(LIBDIR) fclean
				$(RM) $(ODIR)
				$(RM) $(NAME)

re:			fclean all

-include ${DEPS}

.PHONY:		clean fclean re all dir
