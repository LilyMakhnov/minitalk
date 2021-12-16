# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: esivre <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/27 16:19:19 by esivre            #+#    #+#              #
#    Updated: 2021/11/10 20:52:43 by esivre           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_CLIENT = client
NAME_SERVER = server

SRCS_CLIENT	=	client.c
SRCS_SERVER	=	server.c 


SRCS_CLIENT_BONUS	=	client_bonus.c 
SRCS_SERVER_BONUS	=	server_bonus.c 


OBJS_CLIENT	=	$(SRCS_CLIENT:.c=.o)
OBJS_SERVER	=	$(SRCS_SERVER:.c=.o)

OBJS_CLIENT_BONUS	=	$(SRCS_CLIENT_BONUS:.c=.o)
OBJS_SERVER_BONUS	=	$(SRCS_SERVER_BONUS:.c=.o)


FLAGS		=	-Wall -Wextra -Werror

LIBFT       =   libft/libft.a

.c.o:
		gcc ${FLAGS} -c $< -o ${<:.c=.o}


all:			$(LIBFT) $(NAME_SERVER) $(NAME_CLIENT)

bonus:			$(LIBFT) $(OBJS_SERVER_BONUS) $(OBJS_CLIENT_BONUS)
				gcc $(FLAGS) -o $(NAME_SERVER) $(OBJS_SERVER_BONUS) $(LIBFT)
				gcc $(FLAGS) -o $(NAME_CLIENT) $(OBJS_CLIENT_BONUS) $(LIBFT)

$(LIBFT):		
			make bonus -C libft

$(NAME_SERVER):		$(OBJS_SERVER)
			gcc $(FLAGS) -o $(NAME_SERVER) $(OBJS_SERVER) $(LIBFT) 

$(NAME_CLIENT):		$(OBJS_CLIENT)
			gcc $(FLAGS) -o $(NAME_CLIENT) $(OBJS_CLIENT) $(LIBFT)

clean:
			/bin/rm -f $(OBJS_SERVER) $(OBJS_CLIENT) $(OBJS_SERVER_BONUS) $(OBJS_CLIENT_BONUS)
			make -C ./libft clean

fclean:			clean
			/bin/rm -f $(NAME_SERVER) $(NAME_CLIENT)
			make -C ./libft/ fclean

re:			fclean all

.PHONY:		all clean fclean re
