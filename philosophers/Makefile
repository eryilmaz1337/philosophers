# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eryilmaz <eryilmaz@student.42kocaeli.com.  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/16 19:18:48 by eryilmaz          #+#    #+#              #
#    Updated: 2022/06/16 19:18:49 by eryilmaz         ###   ########.tr        #
#                                                                              #
# **************************************************************************** #

all:
	@gcc ./src/* -Wall -Wextra -Werror -o ./philosophers
	@echo "DERLENDİ :)"

clean:
	@rm -rf ./philosophers

fclean:		clean

re:			fclean all

.PHONY:		all clean fclean re