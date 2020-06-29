SRCDIR_ASM = srcs/asm
OBJDIR_ASM = objs/asm

SRCDIR_CW = srcs/vm
OBJDIR_CW = objs/vm

# WE RESPECT NORM! FFFFFF
# 'ALL SOURCE FILES YOU NEED TO COMPILE YOUR PROJECT
#  MUST BE EXPLICITLY NAMED IN YOUR MAKEFILE'
#
#ALL_C_ASM = $(wildcard $(SRCDIR_ASM)/*.c)
#ALL_C_CW = $(wildcard $(SRCDIR_CW)/*.c)

#printf '        %s \\\n' *.c
ALL_C_ASM = add_header.c \
        add_label.c \
        check_label.c \
        check_op.c \
        check_type_arg.c \
        error.c \
        error_2.c \
        free_data.c \
        get_line.c \
        is_type.c \
        main.c \
        file_process.c \
        my_atoi.c \
        op.c \
        parse_args.c \
        parse_args_type.c \
        parse_file.c \
        print_bits.c \
        supfun.c \
        supfun_2.c \
        translate.c \
        write_to_file.c\
        print_memory.c

ALL_C_CW =  actions_1.c \
        actions_2.c \
        actions_3.c \
        actions_4.c \
        actions_handlers.c \
        check_operation.c \
        check_operation2.c \
        handle_carriages.c \
        handle_error.c \
        handle_players.c \
        handlers.c \
        main.c \
        op.c \
        parse_args.c \
        parse_player.c \
        print.c \
        print_bits.c \
        print_debug.c \
        print_ops.c \
        print_ops2.c \
        t_carriage.c \
        t_carriages.c \
        t_mods.c \
        t_player.c \
        t_players.c \
        t_vm.c \
        t_vm_info.c \
        t_vs.c \
        vs_add_cells.c \
        vs_itoa.c \
        vs_itoa_fd.c \
        vs_package.c \
        vs_put_change.c \
        vs_refresh.c \
        vs_utilites.c

ALL_OBJ_ASM = $(ALL_C_ASM:%.c=%.o)
ALL_OBJ_CW = $(ALL_C_CW:%.c=%.o)
OBJS_ASM = $(addprefix $(OBJDIR_ASM)/, $(ALL_OBJ_ASM))
OBJS_CW = $(addprefix $(OBJDIR_CW)/, $(ALL_OBJ_CW))

NAME_ASM = asm
NAME_CW = corewar

INCLUDES_ASM = ./includes/op.h ./includes/asm.h	./includes/asm_error.h
INCLUDES_CW = ./includes/op.h ./includes/vm.h ./includes/vm_error.h ./includes/vs_consts.h

LIBFT_DIR = ./libft_clala
LIBFT = $(LIBFT_DIR)/libft.a
COMP_LIB = make -C $(LIBFT_DIR)
CC = gcc
FLAGS = #-Wall -Wextra -Werror

all: $(LIBFT) $(NAME_ASM) $(NAME_CW)

$(NAME_ASM): $(LIBFT) $(OBJS_ASM)
	$(CC) $(FLAGS) $(OBJS_ASM) -L$(LIBFT_DIR) -lft -o $@

$(OBJDIR_ASM):
	/bin/mkdir -p $(OBJDIR_ASM)

$(OBJDIR_ASM)/%.o: $(SRCDIR_ASM)/%.c $(INCLUDES_ASM) | $(OBJDIR_ASM)
	$(CC) $(FLAGS) -I./includes -I.$(LIBFT_DIR)/includes -c $< -o $@

$(NAME_CW): $(LIBFT) $(OBJS_CW)
	$(CC) $(FLAGS) $(OBJS_CW) -L $(LIBFT_DIR) -lft -o $@

$(OBJDIR_CW):
	/bin/mkdir -p $(OBJDIR_CW)

$(OBJDIR_CW)/%.o: $(SRCDIR_CW)/%.c $(INCLUDES_CW) | $(OBJDIR_CW)
	$(CC) $(FLAGS) -I./includes -I.$(LIBFT_DIR)/includes -c $< -o $@

$(LIBFT): lib

lib:
	@$(COMP_LIB)

clean:
	@/bin/rm -rf $(OBJDIR_ASM) $(OBJDIR_CW)
	@$(COMP_LIB) clean

fclean: clean
	@/bin/rm -rf $(NAME_ASM) $(NAME_CW)
	@$(COMP_LIB) fclean

re: fclean all

.PHONY: lib clean fclean all re
