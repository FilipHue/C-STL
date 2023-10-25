# Created by: Secareanu Filip
# Project: Generic data structures
# Date: 2023-22-10

# Variables
CC = gcc
CFLAGS = -Wall -Wno-unused-function -Isrc/common/error -Isrc/common/generic -Isrc/list -Itest/test_list
OBJDIR = obj

# Containers
LIST = list.o
STACK = stack.o

# All object files
OBJS = $(OBJDIR)/main.o \
<<<<<<< HEAD
       $(OBJDIR)/t_list.o \
	   $(OBJDIR)/t_stack.o \
=======
>>>>>>> main
       $(OBJDIR)/container_utils.o \
       $(OBJDIR)/memory_utils.o \
       $(OBJDIR)/$(LIST) \
	   $(OBJDIR)/$(STACK)

# Binary directory
BINDIR = bin

# Default target
all: $(BINDIR)/main

# Test target
test: $(BINDIR)/main
	valgrind --leak-check=full $(BINDIR)/main

# Linking the executable
$(BINDIR)/main: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files to object files

# Main
$(OBJDIR)/main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

# Common
$(OBJDIR)/container_utils.o: src/common/generic/container_utils.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/memory_utils.o: src/common/generic/memory_utils.c
	$(CC) $(CFLAGS) -c $< -o $@

# Test list
$(OBJDIR)/t_list.o: test/test_list/t_list.c
	$(CC) $(CFLAGS) -c $< -o $@

# Test stack
$(OBJDIR)/t_stack.o: test/test_stack/t_stack.c
	$(CC) $(CFLAGS) -c $< -o $@

# List
$(OBJDIR)/list.o: src/list/list.c
	$(CC) $(CFLAGS) -c $< -o $@

# Stack
$(OBJDIR)/stack.o: src/stack/stack.c
	$(CC) $(CFLAGS) -c $< -o $@

# Create the binary directory
$(BINDIR)/main: | $(BINDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

# Create the object directory
$(OBJS): | $(OBJDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

# Clean up the object files and the executable
.PHONY: clean
clean:
	rm -rf $(OBJDIR) $(BIN)
