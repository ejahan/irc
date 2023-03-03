# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: grannou <grannou@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/31 01:35:59 by grannou           #+#    #+#              #
#    Updated: 2023/02/21 00:51:46 by grannou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Makefile automatic variables:
# $@ = filename represeting the target
# $% = filename element of an archive member specification
# $< = filename of the first prerequisite
# $? = names of all prerequisites that are newer than the target, separated by spaces
# $+ = as $^ plus includes duplicates
# $* = stem (filename without its suffix) of the target filename

# Program name
NAME				=	ircserv
NAME_BONUS			=	ircservBonus

# Shell used and delete command
SHELL				=	/bin/sh
RM					=	/bin/rm -rf

# Files suffixes (By default, make recognizes .o and .c)
.SUFFIXES: .cpp .hpp

# Compiler and flags
CXX 				=	c++
#CXXFLAGS			=	-Wall -Wextra -Werror -MMD -MP -MT -g3 -std=c++98
CXXFLAGS 			=	-std=c++98 -Wall -Wextra -Werror -MMD -MP -MT -g3 -Ofast -fsanitize=address
//CXXFLAGS 			+=	-pedantic -Weffc++ -Wconversion
CPPFLAGS 			=	-I$(INCLUDES_DIR)

# Includes, sources, objects and dependencies directories
INCLUDES_DIR		=	includes

SRCS_DIR			=	srcs
OBJS_DIR			=	objects
DEPS_DIR			=	dependencies

SRCS_BONUS_DIR		= 	srcsBonus
OBJS_BONUS_DIR		= 	objectsBonus
DEPS_BONUS_DIR		= 	dependenciesBonus

# vpath specifies the paths where files can be found and search in order 
# folder01:folder02:folder03 etc
VPATH 				=	srcs:srcs/Parsing:srcs/Commands:includes

# Header files
INCLUDES_FILES		=	Server.hpp \
						Channel.hpp \
						User.hpp \
						Include.hpp

# Source files
SRCS_FILES 			=	srcs/main.cpp \
						srcs/Server.cpp \
						srcs/Channel.cpp \
						srcs/User.cpp \
						srcs/MainUtils.cpp \
						srcs/Parsing/Parsing.cpp \
						srcs/Parsing/Command.cpp \
						srcs/Parsing/Utils.cpp \
						srcs/Parsing/Commands.cpp \
						srcs/Commands/QUIT.cpp \
						srcs/Commands/PASS.cpp \
						srcs/Commands/USER.cpp \
						srcs/Commands/MOTD.cpp \
						srcs/Commands/PRIVMSG.cpp \
						srcs/Commands/NOTICE.cpp \
						srcs/Commands/LIST.cpp \
						srcs/Commands/KILL.cpp \
						srcs/Commands/OPER.cpp \
						srcs/Commands/PING.cpp \
						srcs/Commands/INVITE.cpp \
						srcs/Commands/JOIN.cpp \
						srcs/Commands/NAMES.cpp \
						srcs/Commands/NICK.cpp \
						srcs/Commands/PART.cpp \
						srcs/Commands/TOPIC.cpp \
						srcs/Commands/KICK.cpp \
						srcs/Commands/MODE.cpp

# Bonus source files
SRCS_BONUS_FILES 	=	srcs/main.cpp \
						srcs/Server.cpp \
						srcs/Channel.cpp \
						srcs/User.cpp \
						srcs/MainUtils.cpp \
						srcs/Parsing/Parsing.cpp \
						srcs/Parsing/Command.cpp \
						srcs/Parsing/Utils.cpp \
						srcs/Parsing/Commands.cpp \
						srcs/Commands/QUIT.cpp \
						srcs/Commands/PASS.cpp \
						srcs/Commands/USER.cpp \
						srcs/Commands/MOTD.cpp \
						srcs/Commands/PRIVMSG.cpp \
						srcs/Commands/NOTICE.cpp \
						srcs/Commands/LIST.cpp \
						srcs/Commands/KILL.cpp \
						srcs/Commands/OPER.cpp \
						srcs/Commands/PING.cpp \
						srcs/Commands/INVITE.cpp \
						srcs/Commands/JOIN.cpp \
						srcs/Commands/NAMES.cpp \
						srcs/Commands/NICK.cpp \
						srcs/Commands/PART.cpp \
						srcs/Commands/TOPIC.cpp \
						srcs/Commands/KICK.cpp \
						srcs/Commands/MODE.cpp

# Objects files built from .cpp files
OBJS_FILES			=	$(addprefix objects/, $(notdir $(SRCS_FILES:.cpp=.o)))
OBJS_BONUS_FILES	=	$(addprefix objectsBonus/, $(notdir $(SRCS_BONUS_FILES:.cpp=.o)))

# Dependencies files (handles .hpp modifications)
DEPS_FILES			=	$(addprefix dependencies/, $(notdir $(SRCS_FILES:.cpp=.d)))
DEPS_BONUS_FILES	=	$(addprefix dependenciesBonus/, $(notdir $(SRCS_BONUS_FILES:.cpp=.d)))

# Default program arguments (server port and password)
ARGUMENTS 			=	6667 password

# Rules (all must be first)
.PHONY: all
all: $(NAME)

$(NAME): $(OBJS_FILES)
	@echo "\033c"
	@echo "\n"
	@echo "$(shell tput setaf 198)██╗ ██████╗   ██████╗$(shell tput sgr0)"
	@echo "$(shell tput setaf 197)██║ ██╔══██╗ ██╔════╝$(shell tput sgr0)"
	@echo "$(shell tput setaf 196)██║ ██████╔╝ ██║     $(shell tput sgr0)"
	@echo "$(shell tput setaf 202)██║ ██╔══██╗ ██║     $(shell tput sgr0)"
	@echo "$(shell tput setaf 208)██║ ██║  ██║ ╚██████╗$(shell tput sgr0)"
	@echo "$(shell tput setaf 214)╚═╝ ╚═╝  ╚═╝  ╚═════╝$(shell tput sgr0)"

	@echo "$(shell tput setaf 198)██╗███╗   ██╗████████╗███████╗██████╗ ███╗   ██╗███████╗████████╗    ██████╗ ███████╗██╗      █████╗ ██╗   ██╗     ██████╗██╗  ██╗ █████╗ ████████╗$(shell tput sgr0)"
	@echo "$(shell tput setaf 197)██║████╗  ██║╚══██╔══╝██╔════╝██╔══██╗████╗  ██║██╔════╝╚══██╔══╝    ██╔══██╗██╔════╝██║     ██╔══██╗╚██╗ ██╔╝    ██╔════╝██║  ██║██╔══██╗╚══██╔══╝$(shell tput sgr0)"
	@echo "$(shell tput setaf 196)██║██╔██╗ ██║   ██║   █████╗  ██████╔╝██╔██╗ ██║█████╗     ██║       ██████╔╝█████╗  ██║     ███████║ ╚████╔╝     ██║     ███████║███████║   ██║   $(shell tput sgr0)"
	@echo "$(shell tput setaf 202)██║██║╚██╗██║   ██║   ██╔══╝  ██╔══██╗██║╚██╗██║██╔══╝     ██║       ██╔══██╗██╔══╝  ██║     ██╔══██║  ╚██╔╝      ██║     ██╔══██║██╔══██║   ██║   $(shell tput sgr0)"
	@echo "$(shell tput setaf 208)██║██║ ╚████║   ██║   ███████╗██║  ██║██║ ╚████║███████╗   ██║       ██║  ██║███████╗███████╗██║  ██║   ██║       ╚██████╗██║  ██║██║  ██║   ██║   $(shell tput sgr0)"
	@echo "$(shell tput setaf 214)╚═╝╚═╝  ╚═══╝   ╚═╝   ╚══════╝╚═╝  ╚═╝╚═╝  ╚═══╝╚══════╝   ╚═╝       ╚═╝  ╚═╝╚══════╝╚══════╝╚═╝  ╚═╝   ╚═╝        ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝   $(shell tput sgr0)"
	@echo "\n"

	@echo "$(shell tput setaf 255)              grannou                            ejahan                           efinicke         $(shell tput sgr0)" 

	@echo "$(shell tput setaf 214)   ▄▄▄▄▄▄▄ ▄▄      ▄  ▄  ▄▄▄▄▄▄▄      ▄▄▄▄▄▄▄   ▄ ▄   ▄  ▄  ▄▄▄▄▄▄▄      ▄▄▄▄▄▄▄ ▄▄▄ ▄ ▄▄▄   ▄ ▄▄▄▄▄▄▄$(shell tput sgr0)" 
	@echo "$(shell tput setaf 208)   █ ▄▄▄ █ ▄  ▄▄▄█▄▄▀▀ █ █ ▄▄▄ █      █ ▄▄▄ █ ▀ ▀ ▄ ▄▀  ▄▄▄ █ ▄▄▄ █      █ ▄▄▄ █ █▀█▄ ▀█  ▄ ██ █ ▄▄▄ █$(shell tput sgr0)"
	@echo "$(shell tput setaf 202)   █ ███ █ ██▄█ ███████▄ █ ███ █      █ ███ █ ▀█▀ ▀█▀ ▄▀▀█  █ ███ █      █ ███ █ ▀▀ ▀ ▀███  ▀▄ █ ███ █$(shell tput sgr0)"
	@echo "$(shell tput setaf 196)   █▄▄▄▄▄█ ▄▀▄ █ █ ▄▀▄▀█ █▄▄▄▄▄█      █▄▄▄▄▄█ █▀▄▀█ ▄▀█▀█ █ █▄▄▄▄▄█      █▄▄▄▄▄█ █ ▄▀█ ▄ █▀█▀▄ █▄▄▄▄▄█$(shell tput sgr0)"
	@echo "$(shell tput setaf 197)   ▄▄▄▄  ▄ ▄▀ ▀  █▀██ ▄▀▄  ▄▄▄ ▄      ▄▄▄▄▄ ▄▄▄█▀█ ▄▄█▀▄█  ▄ ▄ ▄ ▄       ▄▄  ▄▄▄  ▀ ▄▀  ▀ █▄▄▄  ▄ ▄▄▄▄$(shell tput sgr0)"
	@echo "$(shell tput setaf 198)       █ ▄▄ ▀   █  █▀█▀█▀███ ▄▄▀      ▄▄█▄▀▄▄▀█ █ ▀  ▄██▀▀▀██▀▀   ▀      ▀ ▄█▄█▄▄▀▀▀▄█ ▀█▀▀█  ▄▀██▀▀▀█$(shell tput sgr0)"
	@echo "$(shell tput setaf 197)    ▀▄▀█▄▄█ ▄ █▀█▄▀ ▄  ▄▀▀▀ ▄▄ ▀      ▄█ ▀ ▀▄▀█▄▄ █▄█ ▀▄▀▀▄  ▀▀█▄▀       █ ▀ ██▄▄█ █▀▄ ▀▄ █ █ ▄▀  ▀ █▀$(shell tput sgr0)"
	@echo "$(shell tput setaf 196)   ▀█  █ ▄▀▀█▀▀▄▀█▀ █▄█ ▄▀▄▄ ███      █▄ ▄▀▀▄██▀ ▄▄█▄▄▄▄▀▀▀▀██▀▄▄ ▀       █▄▀██▄ █▀▄  █▀█  █   ▀▀███▀█$(shell tput sgr0)"
	@echo "$(shell tput setaf 202)   █▄█ ▄▀▄█▀▀▀▄▀▄▀ ▄ █ ▀█ █▄▄ █       ▄▀▀▄▀█▄▄▄▀▄█   ▄▄▄▀ █▀ ▀ ▄▄▀       ▄▄██▀▀▄▄ █▀▄▀ ▀ ██ ▄▀█▀ ▀  █▀$(shell tput sgr0)"
	@echo "$(shell tput setaf 208)   ▄ █▄▀▀▄█ ▀ ▄█▀██ ▄█ ▀  ▀ ▀█▀       █ ▄▀▄ ▄▀▄██ ▀█▄▄▀▄▄▀▀▀▀▀▀ █ ▀      ▀▀▀█▄ ▄██ █▄█▄▀██     ███▀▄▀█$(shell tput sgr0)"
	@echo "$(shell tput setaf 214)    ▄  ▄█▄█ ▄▀▄█▄ ▀ █ ▀▄█▄█▄▄█        █ ██ █▄ ██  █▀▄▄▄▄███▄▄▄█ ▄█▄      ▄▄██  ▄▀▀ ▀▀▄ ▀ ██▄▀█▄██▄▄ ▀█$(shell tput sgr0)"
	@echo "$(shell tput setaf 208)   ▄▄▄▄▄▄▄ ▀█ ▄██  █▀█▄█ ▄ ██▀█▀      ▄▄▄▄▄▄▄ █▄▀▄▄  ▄██▀▄█ ▄ ███▀▀      ▄▄▄▄▄▄▄ ▀▄█  ▀██▀▀███ ▄ █▄▄ █$(shell tput sgr0)"
	@echo "$(shell tput setaf 202)   █ ▄▄▄ █  ▄▄ ▄ ▄▄ ▄▀ █▄▄▄█▀▄██      █ ▄▄▄ █ ▄ ▄█  ▀█▀▄ ▀█▄▄▄█ ▄█▄      █ ▄▄▄ █ █ ▀▄▀▄█▀ █▀██▄▄▄█▄ ▀▄$(shell tput sgr0)"
	@echo "$(shell tput setaf 196)   █ ███ █ ██▀█▀▄▀▀▀▀███  ▄▀▀▄ █      █ ███ █ █▄▀ ▀██▄█  ▀▄█▄█▄███▀      █ ███ █    ▄█▄██▀▄▄ █▄ ▀ ▄▄▄█$(shell tput sgr0)"
	@echo "$(shell tput setaf 197)   █▄▄▄▄▄█ █  ▀▄ █ ▄ ▄▄█ █▄▀█ █       █▄▄▄▄▄█ █▀  █▀▄▄▄▄ ▄▀▄█ ██▄▀       █▄▄▄▄▄█ ██▄▀▄█  ██▀ █ ▄▀▄▀ █▀$(shell tput sgr0)"
	@echo "\n"
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $(NAME) $(OBJS_FILES)
	@echo "🦊 $(shell tput setaf 002)OK $(shell tput setaf 198)$(NAME) is ready$(shell tput setaf sgr0) 🦊"

$(OBJS_DIR)/%.o: %.cpp
	@mkdir -p $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) -MT $(OBJS_DIR) -MP -c $< -o $@

-include $(DEPS_FILES)

$(DEPS_DIR)/%.d: %.cpp
	@mkdir -p $(DEPS_DIR)
	$(CXX) $(CFLAGS) -MT $(addprefix objects/, $(notdir $(DEPS_DIR))) -MM $< -o $@

.PHONY: run
run:
	@echo "$(shell tput setaf 198)       ██╗██╗██████╗  ██████╗███████╗███████╗██████╗ ██╗   ██╗     ██████╗  ██████╗  ██████╗███████╗    ██████╗  █████╗ ███████╗███████╗██╗    ██╗ ██████╗ ██████╗ ██████╗ $(shell tput sgr0)"
	@echo "$(shell tput setaf 197)      ██╔╝██║██╔══██╗██╔════╝██╔════╝██╔════╝██╔══██╗██║   ██║    ██╔════╝ ██╔════╝ ██╔════╝╚════██║    ██╔══██╗██╔══██╗██╔════╝██╔════╝██║    ██║██╔═══██╗██╔══██╗██╔══██╗$(shell tput sgr0)"
	@echo "$(shell tput setaf 196)     ██╔╝ ██║██████╔╝██║     ███████╗█████╗  ██████╔╝██║   ██║    ███████╗ ███████╗ ███████╗    ██╔╝    ██████╔╝███████║███████╗███████╗██║ █╗ ██║██║   ██║██████╔╝██║  ██║$(shell tput sgr0)"
	@echo "$(shell tput setaf 202)    ██╔╝  ██║██╔══██╗██║     ╚════██║██╔══╝  ██╔══██╗╚██╗ ██╔╝    ██╔═══██╗██╔═══██╗██╔═══██╗  ██╔╝     ██╔═══╝ ██╔══██║╚════██║╚════██║██║███╗██║██║   ██║██╔══██╗██║  ██║$(shell tput sgr0)"
	@echo "$(shell tput setaf 208)██╗██╔╝   ██║██║  ██║╚██████╗███████║███████╗██║  ██║ ╚████╔╝     ╚██████╔╝╚██████╔╝╚██████╔╝  ██║      ██║     ██║  ██║███████║███████║╚███╔███╔╝╚██████╔╝██║  ██║██████╔╝$(shell tput sgr0)"
	@echo "$(shell tput setaf 214)╚═╝╚═╝    ╚═╝╚═╝  ╚═╝ ╚═════╝╚══════╝╚══════╝╚═╝  ╚═╝  ╚═══╝       ╚═════╝  ╚═════╝  ╚═════╝   ╚═╝      ╚═╝     ╚═╝  ╚═╝╚══════╝╚══════╝ ╚══╝╚══╝  ╚═════╝ ╚═╝  ╚═╝╚═════╝ $(shell tput sgr0)"
	@./$(NAME) $(ARGUMENTS)

# No more norme... but still Norminet ;)
.PHONY: norme
norme:
	@echo "\033c"
	@echo "\n"
	@echo "$(shell tput setaf 46)No more norme... but still$(shell tput sgr0)"
	@echo "\n"
	@echo "$(shell tput setaf 201)███╗   ██╗ ██████╗ ██████╗ ███╗   ███╗██╗███╗   ██╗███████╗████████╗$(shell tput sgr0)"
	@echo "$(shell tput setaf 200)████╗  ██║██╔═══██╗██╔══██╗████╗ ████║██║████╗  ██║██╔════╝╚══██╔══╝$(shell tput sgr0)"
	@echo "$(shell tput setaf 199)██╔██╗ ██║██║   ██║██████╔╝██╔████╔██║██║██╔██╗ ██║█████╗     ██║   $(shell tput sgr0)"
	@echo "$(shell tput setaf 198)██║╚██╗██║██║   ██║██╔══██╗██║╚██╔╝██║██║██║╚██╗██║██╔══╝     ██║   $(shell tput sgr0)"
	@echo "$(shell tput setaf 197)██║ ╚████║╚██████╔╝██║  ██║██║ ╚═╝ ██║██║██║ ╚████║███████╗   ██║   $(shell tput sgr0)"
	@echo "$(shell tput setaf 196)╚═╝  ╚═══╝ ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚══════╝   ╚═╝   $(shell tput sgr0)"
	@echo "\n"

# Debug with valgrind
.PHONY: debug
debug:
	@echo "\n"
	@echo "$(shell tput setaf 201)██████╗ ███████╗██████╗ ██╗   ██╗ ██████╗$(shell tput sgr0)"
	@echo "$(shell tput setaf 200)██╔══██╗██╔════╝██╔══██╗██║   ██║██╔════╝$(shell tput sgr0)"
	@echo "$(shell tput setaf 199)██║  ██║█████╗  ██████╔╝██║   ██║██║  ███╗$(shell tput sgr0)"
	@echo "$(shell tput setaf 198)██║  ██║██╔══╝  ██╔══██╗██║   ██║██║   ██║$(shell tput sgr0)"
	@echo "$(shell tput setaf 197)██████╔╝███████╗██████╔╝╚██████╔╝╚██████╔╝$(shell tput sgr0)"
	@echo "$(shell tput setaf 196)╚═════╝ ╚══════╝╚═════╝  ╚═════╝  ╚═════╝$(shell tput sgr0)"
	@echo "\n"
	valgrind --leak-check=full ./$(NAME) $(ARGUMENTS)

# Clean objects (.o) and dependencies (.d)
.PHONY: clean
clean: 
	@echo "\033c"
	@echo "\n"
	@echo "$(shell tput setaf 51) ██████╗██╗     ███████╗ █████╗ ███╗   ██╗$(shell tput sgr0)"
	@echo "$(shell tput setaf 50)██╔════╝██║     ██╔════╝██╔══██╗████╗  ██║$(shell tput sgr0)"
	@echo "$(shell tput setaf 49)██║     ██║     █████╗  ███████║██╔██╗ ██║$(shell tput sgr0)"
	@echo "$(shell tput setaf 48)██║     ██║     ██╔══╝  ██╔══██║██║╚██╗██║$(shell tput sgr0)"
	@echo "$(shell tput setaf 47)╚██████╗███████╗███████╗██║  ██║██║ ╚████║$(shell tput sgr0)"
	@echo "$(shell tput setaf 46) ╚═════╝╚══════╝╚══════╝╚═╝  ╚═╝╚═╝  ╚═══╝$(shell tput sgr0)"
	@echo "\n"
	$(RM) $(OBJS_DIR) $(DEPS_DIR) $(OBJS_BONUS_DIR) $(DEPS_BONUS_DIR)

# Execute clean and clean program
.PHONY: fclean
fclean: clean
	@echo "\033c"
	@echo "\n"
	@echo "$(shell tput setaf 45)███████╗ ██████╗██╗     ███████╗ █████╗ ███╗   ██╗$(shell tput sgr0)"
	@echo "$(shell tput setaf 44)██╔════╝██╔════╝██║     ██╔════╝██╔══██╗████╗  ██║$(shell tput sgr0)"
	@echo "$(shell tput setaf 43)█████╗  ██║     ██║     █████╗  ███████║██╔██╗ ██║$(shell tput sgr0)"
	@echo "$(shell tput setaf 42)██╔══╝  ██║     ██║     ██╔══╝  ██╔══██║██║╚██╗██║$(shell tput sgr0)"
	@echo "$(shell tput setaf 41)██║     ╚██████╗███████╗███████╗██║  ██║██║ ╚████║$(shell tput sgr0)"
	@echo "$(shell tput setaf 40)╚═╝      ╚═════╝╚══════╝╚══════╝╚═╝  ╚═╝╚═╝  ╚═══╝$(shell tput sgr0)"
	@echo "\n"
	$(RM) $(NAME) $(NAME_BONUS)

# Clean all and make
.PHONY: re
re: fclean all
	@echo "\n"
	@echo "$(shell tput setaf 201)███╗   ███╗ █████╗ ██╗  ██╗███████╗    ██████╗ ███████╗$(shell tput sgr0)"
	@echo "$(shell tput setaf 200)████╗ ████║██╔══██╗██║ ██╔╝██╔════╝    ██╔══██╗██╔════╝$(shell tput sgr0)"
	@echo "$(shell tput setaf 199)██╔████╔██║███████║█████╔╝ █████╗      ██████╔╝█████╗$(shell tput sgr0)"
	@echo "$(shell tput setaf 198)██║╚██╔╝██║██╔══██║██╔═██╗ ██╔══╝      ██╔══██╗██╔══╝$(shell tput sgr0)"
	@echo "$(shell tput setaf 197)██║ ╚═╝ ██║██║  ██║██║  ██╗███████╗    ██║  ██║███████╗$(shell tput sgr0)"
	@echo "$(shell tput setaf 196)╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝    ╚═╝  ╚═╝╚══════╝$(shell tput sgr0)"
	@echo "\n"

# Bonus compilation
.PHONY: bonus
bonus: $(OBJS_BONUS_FILES)
	@echo "\033c"
	@echo "\n"
	@echo "$(shell tput setaf 226)██████╗  ██████╗ ███╗   ██╗██╗   ██╗███████╗$(shell tput sgr0)"
	@echo "$(shell tput setaf 220)██╔══██╗██╔═══██╗████╗  ██║██║   ██║██╔════╝$(shell tput sgr0)"
	@echo "$(shell tput setaf 214)██████╔╝██║   ██║██╔██╗ ██║██║   ██║███████╗$(shell tput sgr0)"
	@echo "$(shell tput setaf 208)██╔══██╗██║   ██║██║╚██╗██║██║   ██║╚════██║$(shell tput sgr0)"
	@echo "$(shell tput setaf 202)██████╔╝╚██████╔╝██║ ╚████║╚██████╔╝███████║$(shell tput sgr0)"
	@echo "$(shell tput setaf 196)╚═════╝  ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝ ╚══════╝$(shell tput sgr0)"
	@echo "\n"
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $(NAME_BONUS) $(OBJS_BONUS_FILES)
	@echo "🦊 $(shell tput setaf 002)OK $(shell tput setaf 198)$(NAME_BONUS) is ready$(shell tput setaf sgr0) 🦊"

$(OBJS_BONUS_DIR)/%.o: %.cpp
	@mkdir -p $(OBJS_BONUS_DIR)
	$(CXX) $(CXXFLAGS) -MT $(OBJS_BONUS_DIR) -MP -c $< -o $@

-include $(DEPS_BONUS_FILES)

$(DEPS_BONUS_DIR)/%.d: %.cpp
	@mkdir -p $(DEPS_BONUS_DIR)
	$(CXX) $(CFLAGS) -MT $(addprefix objects/, $(notdir $(DEPS_BONUS_DIR))) -MM $< -o $@
	
	
# Best rule <3
.PHONY: fox
fox:
	@echo "\033c"
	@echo "$(shell tput setaf 0)≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈$(shell tput sgr0)"
	@echo "$(shell tput setaf 0)≈≈≈≈≈≈≈$(shell tput sgr0)        $(shell tput setaf 0)≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈$(shell tput sgr0)        $(shell tput setaf 0)≈≈≈≈≈≈≈$(shell tput sgr0)"
	@echo "$(shell tput setaf 0)≈≈≈≈≈≈≈$(shell tput sgr0) $(shell tput setaf 94)∂∂∂∂$(shell tput setaf 202)ΩΩΩ$(tput sgr0)     $(shell tput setaf 0)≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈$(shell tput sgr0)      $(shell tput setaf 202)ΩΩ$(shell tput setaf 94)∂∂∂$(shell tput sgr0)  $(shell tput setaf 0)≈≈≈≈≈≈≈$(shell tput sgr0)"
	@echo "$(shell tput setaf 0)≈≈≈≈≈≈≈$(shell tput sgr0) $(shell tput setaf 94)∂∂∂$(shell tput setaf 202)ΩΩΩΩΩΩΩΩΩ$(tput sgr0)     $(shell tput setaf 0)≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈$(shell tput sgr0)     $(shell tput setaf 202)ΩΩΩΩΩΩ$(shell tput setaf 94)∂∂∂$(shell tput sgr0)  $(shell tput setaf 0)≈≈≈≈≈≈≈$(shell tput sgr0)"
	@echo "$(shell tput setaf 0)≈≈≈≈≈≈≈$(shell tput sgr0)  $(shell tput setaf 94)∂∂$(shell tput setaf 202)ΩΩΩΩΩΩΩΩΩΩΩΩΩ$(shell tput sgr0)  $(shell tput setaf 94)∂$(shell tput setaf 0)≈≈≈≈≈≈$(shell tput setaf 94)∂∂∂∂∂∂∂∂∂∂∂∂∂$(shell tput setaf 0)≈≈≈≈≈$(shell tput setaf 94)∂$(shell tput sgr0)   $(shell tput setaf 202)ΩΩΩΩΩΩΩΩΩΩΩΩΩ$(shell tput setaf 94)∂∂$(shell tput sgr0)  $(shell tput setaf 0)≈≈≈≈≈≈≈$(shell tput sgr0)"
	@echo "$(shell tput setaf 0)≈≈≈≈≈≈≈≈$(shell tput sgr0)  $(shell tput setaf 94)∂$(shell tput setaf 202)ΩΩΩΩΩΩΩΩΩΩΩ$(shell tput sgr0)  $(shell tput setaf 202)ΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩ$(shell tput sgr0)  $(shell tput setaf 202)ΩΩΩΩΩΩΩΩΩΩΩΩ$(shell tput setaf 94)∂$(shell tput sgr0)  $(shell tput setaf 0)≈≈≈≈≈≈≈$(shell tput sgr0)"
	@echo "$(shell tput setaf 0)≈≈≈≈≈≈≈≈$(shell tput sgr0)  $(shell tput setaf 94)∂$(shell tput setaf 202)ΩΩΩΩΩΩΩΩ$(shell tput sgr0)  $(shell tput setaf 202)ΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩ$(shell tput sgr0)  $(shell tput setaf 202)ΩΩΩΩΩΩΩΩΩ$(shell tput setaf 94)∂$(shell tput sgr0)  $(shell tput setaf 0)≈≈≈≈≈≈≈$(shell tput sgr0)"
	@echo "$(shell tput setaf 0)≈≈≈≈≈≈≈≈$(shell tput sgr0)  $(shell tput setaf 94)∂$(shell tput setaf 202)ΩΩΩΩΩΩ$(shell tput sgr0) $(shell tput setaf 202)ΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩ$(shell tput sgr0) $(shell tput setaf 202)ΩΩΩΩΩΩΩ$(shell tput setaf 94)∂$(shell tput sgr0)  $(shell tput setaf 0)≈≈≈≈≈≈≈≈$(shell tput sgr0)"
	@echo "$(shell tput setaf 0)≈≈≈≈≈≈≈≈$(shell tput sgr0)  $(shell tput setaf 94)∂$(shell tput setaf 202)ΩΩΩΩΩ$(shell tput sgr0) $(shell tput setaf 202)ΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩ$(shell tput sgr0) $(shell tput setaf 202)ΩΩΩΩΩΩ$(shell tput setaf 94)∂$(shell tput sgr0)  $(shell tput setaf 0)≈≈≈≈≈≈≈≈$(shell tput sgr0)"
	@echo "$(shell tput setaf 0)≈≈≈≈≈≈≈≈$(shell tput sgr0)  $(shell tput setaf 202)ΩΩΩΩΩ$(shell tput sgr0) $(shell tput setaf 202)ΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩ$(shell tput setaf 208)ππππππ$(shell tput setaf 202)ΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩ$(shell tput sgr0) $(shell tput setaf 202)ΩΩΩΩΩΩ  $(shell tput setaf 0)≈≈≈≈≈≈≈≈$(shell tput sgr0)"
	@echo "$(shell tput setaf 0)≈≈≈≈≈≈≈≈≈$(shell tput sgr0)  $(shell tput setaf 202)ΩΩ$(shell tput sgr0)  $(shell tput setaf 202)ΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩ$(shell tput setaf 208)πππππππππ$(shell tput setaf 202)ΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩ$(shell tput sgr0)  $(shell tput setaf 202)ΩΩΩΩ$(shell tput sgr0)  $(shell tput setaf 0)≈≈≈≈≈≈≈≈$(shell tput sgr0)"
	@echo "$(shell tput setaf 0)≈≈≈≈≈≈≈≈≈$(shell tput setaf 94)∂∂$(shell tput setaf 202)ΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩ$(shell tput setaf 208)πππππππππππππ$(shell tput setaf 202)ΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩ$(shell tput setaf 94)∂∂$(shell tput setaf 0)≈≈≈≈≈≈≈≈≈$(shell tput sgr0)"
	@echo "$(shell tput setaf 0)≈≈≈≈≈≈≈≈≈$(shell tput setaf 94)∂∂$(shell tput setaf 202)ΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩ$(shell tput setaf 208)πππππππππππππππππ$(shell tput setaf 202)ΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩ$(shell tput setaf 94)∂∂$(shell tput setaf 0)≈≈≈≈≈≈≈≈≈$(shell tput sgr0)"
	@echo "$(shell tput setaf 0)≈≈≈≈≈≈≈≈≈≈$(shell tput setaf 94)∂∂$(shell tput setaf 202)ΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩ$(shell tput setaf 208)πππππππππππππππππππππ$(shell tput setaf 202)ΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩ$(shell tput setaf 94)∂∂$(shell tput setaf 0)≈≈≈≈≈≈≈≈≈$(shell tput sgr0)"
	@echo "$(shell tput setaf 0)≈≈≈≈≈≈≈≈≈≈$(shell tput setaf 94)∂∂$(shell tput setaf 202)ΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩ$(shell tput setaf 208)πππππππππππππππππππππππππ$(shell tput setaf 202)ΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩ$(shell tput setaf 94)∂∂$(shell tput setaf 0)≈≈≈≈≈≈≈≈≈≈$(shell tput sgr0)"
	@echo "$(shell tput setaf 0)≈≈≈≈≈≈≈≈≈≈≈$(shell tput setaf 94)∂∂$(shell tput setaf 202)ΩΩΩΩΩΩΩΩΩΩΩΩΩΩ$(shell tput setaf 208)ππππππππππππππππππππππππππππ$(shell tput setaf 202)ΩΩΩΩΩΩΩΩΩΩΩΩΩ$(shell tput setaf 94)∂∂$(shell tput setaf 0)≈≈≈≈≈≈≈≈≈≈$(shell tput sgr0)"
	@echo "$(shell tput setaf 0)≈≈≈≈≈≈≈≈≈≈≈$(shell tput setaf 94)∂∂$(shell tput setaf 202)ΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩ$(shell tput setaf 208)ππππππππππππππππππππππππ$(shell tput setaf 202)ΩΩΩΩΩΩΩΩΩΩΩΩΩΩ$(shell tput setaf 94)∂∂$(shell tput setaf 0)≈≈≈≈≈≈≈≈≈≈≈$(shell tput sgr0)"
	@echo "$(shell tput setaf 0)≈≈≈≈≈≈≈≈≈≈≈$(shell tput setaf 94)∂∂$(shell tput setaf 202)ΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩ$(shell tput setaf 208)ππππππππππππππππππππππ$(shell tput setaf 202)ΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩ$(shell tput setaf 94)∂∂$(shell tput setaf 0)≈≈≈≈≈≈≈≈≈≈$(shell tput sgr0)"
	@echo "$(shell tput setaf 0)≈≈≈≈≈≈≈≈≈≈$(shell tput setaf 94)∂∂$(shell tput setaf 202)ΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩ$(shell tput setaf 94)∂$(shell tput setaf 208)ππππππππππππππππ$(shell tput setaf 94)∂$(shell tput setaf 202)ΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩ$(shell tput setaf 94)∂∂$(shell tput setaf 0)≈≈≈≈≈≈≈≈≈≈$(shell tput sgr0)"
	@echo "$(shell tput setaf 0)≈≈≈≈≈≈≈≈≈≈$(shell tput setaf 94)∂∂$(shell tput setaf 202)ΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩ$(shell tput setaf 94)∂$(shell tput setaf 208)ππππππππππππππ$(shell tput setaf 94)∂$(shell tput setaf 202)ΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩ$(shell tput setaf 94)∂∂$(shell tput setaf 0)≈≈≈≈≈≈≈≈≈$(shell tput sgr0)"
	@echo "$(shell tput setaf 0)≈≈≈≈≈≈≈≈≈$(shell tput setaf 94)∂∂$(shell tput setaf 202)ΩΩΩΩΩΩΩΩΩΩΩΩΩΩ$(shell tput sgr0) $(shell tput setaf 40)@@@$(shell tput sgr0) $(shell tput setaf 202)ΩΩΩΩ$(shell tput setaf 94)∂∂$(shell tput setaf 208)ππππππππππ$(shell tput setaf 94)∂$(shell tput setaf 202)ΩΩΩ$(shell tput sgr0) $(shell tput setaf 40)@@@$(shell tput sgr0) $(shell tput setaf 202)ΩΩΩΩΩΩΩΩΩΩΩΩΩΩ$(shell tput setaf 94)∂∂$(shell tput setaf 0)≈≈≈≈≈≈≈≈≈$(shell tput sgr0)"
	@echo "$(shell tput setaf 0)≈≈≈≈≈≈≈≈$(shell tput setaf 94)∂∂$(shell tput setaf 202)ΩΩΩΩΩΩΩΩΩΩΩΩΩΩ$(shell tput sgr0) $(shell tput setaf 40)@@@@$(shell tput setaf 40)@$(shell tput sgr0) $(shell tput setaf 202)ΩΩΩΩΩ$(shell tput setaf 94)∂$(shell tput setaf 208)ππππππππ$(shell tput setaf 94)∂$(shell tput setaf 202)ΩΩΩ$(shell tput sgr0) $(shell tput setaf 40)@@@@@@$(shell tput setaf 202)ΩΩΩΩΩΩΩΩΩΩΩΩΩΩ$(shell tput setaf 94)∂∂$(shell tput setaf 0)≈≈≈≈≈≈≈≈$(shell tput sgr0)"
	@echo "$(shell tput setaf 0)≈≈≈≈≈≈≈$(shell tput setaf 94)∂∂$(shell tput setaf 202)ΩΩΩΩΩΩΩΩΩΩΩΩΩΩ$(shell tput sgr0) $(shell tput setaf 40)@@@@@@$(shell tput setaf 40)@$(shell tput sgr0) $(shell tput setaf 202)ΩΩΩ$(shell tput setaf 94)∂∂$(shell tput setaf 208)ππππππππ$(shell tput setaf 94)∂$(shell tput setaf 202)ΩΩ$(shell tput sgr0) $(shell tput setaf 40)@@@@@$(shell tput setaf 40)@@$(shell tput sgr0) $(shell tput setaf 202)ΩΩΩΩΩΩΩΩΩΩΩΩΩΩ$(shell tput setaf 94)∂∂$(shell tput setaf 0)≈≈≈≈≈≈≈$(sh    ell tput sgr0)"
	@echo "$(shell tput setaf 0)≈≈≈≈≈≈$(shell tput setaf 94)∂∂$(shell tput setaf 202)ΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩ$(shell tput sgr0) $(shell tput setaf 40)@@@@@@@$(shell tput sgr0) $(shell tput setaf 202)ΩΩ$(shell tput setaf 94)∂∂$(shell tput setaf 208)πππππππππ$(shell tput setaf 94)∂$(shell tput setaf 202)ΩΩ$(shell tput sgr0) $(shell tput setaf 40)@@@@@@@$(shell tput sgr0) $(shell tput setaf 202)ΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩ$(shell tput setaf 94)∂∂$(shell tput setaf 0)≈≈≈≈≈≈$(shell tput sgr0)"
	@echo "$(shell tput setaf 0)≈≈≈≈$(shell tput setaf 94)∂∂$(shell tput setaf 202)ΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩ$(shell tput sgr0) $(shell tput setaf 40)@@@@@$(shell tput sgr0) $(shell tput setaf 202)ΩΩ$(shell tput setaf 94)∂∂$(shell tput setaf 208)πππππππππππ$(shell tput setaf 94)∂$(shell tput setaf 202)ΩΩ$(shell tput sgr0) $(shell tput setaf 40)@@@@@$(shell tput sgr0) $(shell tput setaf 202)ΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩ$(shell tput setaf 94)∂∂$(shell tput setaf 0)≈≈≈≈$(shell tput sgr0)"
	@echo "$(shell tput setaf 0)≈≈≈$(shell tput setaf 94)∂∂$(shell tput setaf 202)ΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩ$(shell tput sgr0) $(shell tput setaf 40)@@@$(shell tput sgr0) $(shell tput setaf 202)ΩΩ$(shell tput setaf 94)∂∂$(shell tput setaf 208)πππππππππππππ$(shell tput setaf 94)∂$(shell tput setaf 202)ΩΩ$(shell tput sgr0) $(shell tput setaf 40)@@@$(shell tput sgr0) $(shell tput setaf 202)ΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩ$(shell tput setaf 94)∂∂$(shell tput setaf 0)≈≈≈$(shell tput sgr0)"
	@echo "$(shell tput setaf 0)≈≈$(shell tput setaf 94)∂∂∂∂∂$(shell tput setaf 202)ΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩ$(shell tput setaf 94)∂∂$(shell tput setaf 208)ππππππππππππππ$(shell tput setaf 94)∂∂$(shell tput setaf 202)ΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩ∂∂$(shell tput setaf 0)≈≈$(shell tput sgr0)"
	@echo "$(shell tput setaf 0)≈$(shell tput setaf 94)∂∂$(shell tput setaf 0)≈≈$(shell tput setaf 94)∂∂$(shell tput setaf 202)ΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩ$(shell tput setaf 94)∂∂∂$(shell tput setaf 208)ππππππππππ$(shell tput setaf 94)∂∂∂$(shell tput setaf 202)ΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩ$(shell tput setaf 94)∂∂$(shell tput setaf 0)≈≈$(shell tput setaf 94)∂∂$(shell tput setaf 0)≈$(shell tput sgr0)"
	@echo "$(shell tput setaf 0)≈≈≈$(shell tput setaf 94)∂∂$(shell tput setaf 202)ΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩ$(shell tput setaf 94)∂∂∂$(shell tput setaf 208)ππππππππ$(shell tput setaf 94)∂∂∂$(shell tput setaf 202)ΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩ∂∂$(shell tput setaf 0)≈≈≈$(shell tput sgr0)"
	@echo "$(shell tput setaf 94)∂$(shell tput sgr0)ΩΩ$(shell tput setaf 94)∂∂∂∂∂∂∂∂∂∂∂∂∂∂∂∂∂$(shell tput sgr0)ΩΩΩΩΩΩ:::$(shell tput sgr0)ΩΩΩΩΩΩΩ$(shell tput setaf 202)ΩΩΩΩΩΩΩΩΩ$(shell tput sgr0)ΩΩΩΩΩΩ:::$(shell tput sgr0)ΩΩΩΩΩΩΩΩ$(shell tput setaf 94)∂∂∂∂∂∂∂∂∂∂∂∂∂∂∂$(shell tput sgr0)ΩΩ$(shell tput setaf 94)∂$(shell tput sgr0)"
	@echo "$(shell tput setaf 94)∂∂$(shell tput sgr0)ΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩ:$(shell tput sgr0)ΩΩΩΩΩΩΩΩ$(shell tput sgr0)     :::::$(shell tput sgr0)     $(shell tput sgr0)ΩΩΩΩΩΩ:$(shell tput sgr0)ΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩ$(shell tput setaf 94)∂∂$(shell tput sgr0)"
	@echo "$(shell tput setaf 0)≈≈≈$(shell tput sgr0)ΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩ:$(shell tput sgr0)ΩΩΩΩΩΩΩΩΩΩ$(shell tput sgr0)             $(shell tput sgr0)ΩΩΩΩΩΩΩΩ:$(shell tput sgr0)ΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩ$(shell tput setaf 0)≈≈≈$(shell tput sgr0)"
	@echo "$(shell tput setaf 0)≈≈$(shell tput setaf 94)∂∂$(shell tput setaf 0)≈≈$(shell tput sgr0)ΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩ:$(shell tput sgr0)ΩΩΩΩΩΩΩΩΩΩΩΩ$(shell tput sgr0)           $(shell tput sgr0)ΩΩΩΩΩΩΩΩΩΩ:$(shell tput sgr0)ΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩ$(shell tput setaf 0)≈≈∂∂$(shell tput setaf 0)≈≈$(shell tput sgr0)"
	@echo "$(shell tput setaf 0)≈≈≈$(shell tput setaf 94)∂∂∂∂$(shell tput sgr0)ΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩ:ΩΩΩΩΩΩΩΩΩΩΩΩ$(shell tput sgr0)         ΩΩΩΩΩΩΩΩΩΩ:ΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩ$(shell tput setaf 94)∂∂∂∂$(shell tput setaf 0)≈≈≈≈$(shell tput sgr0)"
	@echo "$(shell tput setaf 0)≈≈≈≈≈≈≈≈≈$(shell tput setaf 94)∂∂∂∂∂∂$(shell tput sgr0)ΩΩΩΩΩΩΩΩΩ:$(shell tput sgr0)ΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩ:$(shell tput sgr0)ΩΩΩΩΩΩΩΩΩΩΩΩΩ:$(shell tput sgr0)ΩΩΩΩΩΩΩΩΩΩΩΩΩ$(shell tput setaf 94)∂∂∂$(shell tput setaf 0)≈≈≈≈≈≈≈≈≈$(shell tput sgr0)"
	@echo "$(shell tput setaf 0)≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈$(shell tput setaf 94)∂∂∂∂$(shell tput sgr0)ΩΩΩ:$(shell tput sgr0)ΩΩΩΩΩΩΩΩΩΩΩΩΩΩ:$(shell tput sgr0)ΩΩΩΩΩΩΩΩΩΩΩΩ:$(shell tput sgr0)ΩΩΩΩ$(shell tput setaf 94)∂∂∂∂$(shell tput setaf 0)≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈$(shell tput sgr0)"
	@echo "$(shell tput setaf 0)≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈$(shell tput setaf 94)∂∂∂$(shell tput sgr0)ΩΩΩΩΩΩΩΩΩΩ::$(shell tput sgr0)$(shell tput setaf 196)ΩΩΩ$(shell tput sgr0)::ΩΩΩΩΩΩΩΩ$(shell tput setaf 94)∂∂∂$(shell tput setaf 0)≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈$(shell tput sgr0)"
	@echo "$(shell tput setaf 0)≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈$(shell tput setaf 94)∂∂$(shell tput sgr0):::$(shell tput sgr0)ΩΩΩΩ$(shell tput setaf 196)ΩΩΩ$(shell tput sgr0)ΩΩΩΩ:::$(shell tput setaf 94)∂∂$(shell tput setaf 0)≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈$(shell tput sgr0)"
	@echo "$(shell tput setaf 0)≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈$(shell tput setaf 94)∂∂$(shell tput sgr0)ΩΩΩ$(shell tput setaf 196)Ω$(shell tput sgr0)ΩΩΩΩ$(shell tput setaf 94)∂∂$(shell tput setaf 0)≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈$(shell tput sgr0)"
	@echo "$(shell tput setaf 0)≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈$(shell tput setaf 94)∂∂∂∂∂∂$(shell tput setaf 0)≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈$(shell tput sgr0)"
