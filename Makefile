CC 				= gcc-13 # TODO CHANGE TO CC
CFLAGS			= -Wall -Werror -Wextra
SRC				= main.c hook.c pixel.c render.c
DEPS_FOLDER		= deps
BUILD_FOLDER	= build
OBJS 			= $(SRC:%.c=$(BUILD_FOLDER)/%.o)
DEPS 			= $(SRC:%.c=$(DEPS_FOLDER)/%.d)
LIBFT_DIR		= libft
LIBFT			= ft
LD				= -Lminilibx-linux -lmlx -lXext -lX11 -lm #-L$(LIBFT_DIR) -l$(LIBFT)
NAME 			= minirt

all bonus: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -O3 $^ $(LD) -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJS) :$(BUILD_FOLDER)/%.o:%.c | $(BUILD_FOLDER) $(DEPS_FOLDER)
	$(CC) -c -MMD -MF $(DEPS_FOLDER)/$*.d $(CFLAGS) -O3 $< -o $@

$(BUILD_FOLDER):
	mkdir -p $@
$(DEPS_FOLDER):
	mkdir -p $@

-include $(DEPS)

clean:
# 	$(MAKE) -C $(LIBFT_DIR) $@
	rm -rf $(DEPS_FOLDER) $(BUILD_FOLDER)

fclean: clean
# 	$(MAKE) -C $(LIBFT_DIR) $@
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re