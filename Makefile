SRCS = main_program.c init_data.c helpers.c philo_functions.c utils.c
BONUS_SRCS =  philo_bonus.c init_bonus.c helpers_bonus.c utils_bonus.c utils_2_bonus.c \
utils_3_bonus.c additional_bonus.c
MAND_DIR = ./mandatory_part/
BONUS_DIR= ./bonus_part/
OBJS= $(addprefix $(MAND_DIR), $(SRCS:.c=.o))
BONUS_OBJS = $(addprefix $(BONUS_DIR), $(BONUS_SRCS:.c=.o))
CFLAGS  = -Wall -Wextra -Werror
LDFLAGS = -pthread  -lpthread 
CC = gcc
BONUS= philo_bonus
NAME= philo
%.o:$(MAND_DIR)/%.c
	$(CC) -c $(CFLAGS) -o $(MAND_DIR)/$@ $<
%.o:$(BONUS_DIR)/%.c
	$(CC) -c $(CFLAGS) -o $(BONUS_DIR)/$@ $<
$(NAME):$(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(NAME)
$(BONUS):$(BONUS_OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(BONUS_OBJS) -o $(BONUS)
all:$(NAME)
bonus:$(BONUS)
clean:
	rm -rf $(OBJS) $(BONUS_OBJS)
fclean:clean
	rm -rf $(NAME) $(BONUS)
re:fclean all