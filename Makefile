NAME		= ft_ls

PRINTF		= libftprintf.a

PRINTFDIR	= printf

SRCS		= ft_ls.c \
				parse_args.c \
				ft_lstadd_alpha.c \
				utils.c

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
				$(MAKE) -C $(PRINTFDIR)
				mkdir -p $(ODIR)

obj/%.o:	src/%.c Makefile
				$(CC) $(CFLAGS) -c $< -o $@

${NAME}:	$(OBJS)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(PRINTFDIR)/$(PRINTF)

bonus:		all

clean:
				make -C $(PRINTFDIR) clean
				$(RM) $(ODIR)

fclean:		
				make -C $(PRINTFDIR) fclean
				$(RM) $(ODIR)
				$(RM) $(NAME)

re:			fclean all

-include ${DEPS}

.PHONY:		clean fclean re all dir
