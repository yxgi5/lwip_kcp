#TARGETS=udp_server udp_client
TARGETS=kcp_client

CC = gcc
LD = ld
OBJCOPY = objcopy
SIZE = size
CC_FLAGS = -g -Wall -pedantic -std=c99
CL_FLAGS = -lpthread
INC = .

SRC = ikcp.c \
    kcp_client.c
#	udp_server.c \
#	udp_client.c

OBJS = $(addsuffix .o, $(basename $(SRC)))
#$(warning $$OBJS is $(OBJS))
#OBJS = server.o \
#	client.o \
#	sendfile.o \
#	buffer.o \
#	recvfile.o

all:$(TARGETS)

$(TARGETS):%:%.o ikcp.o
	$(CC) $(CC_FLAGS) -I. $< ikcp.o -o $@ $(CL_FLAGS)
#$(TARGETS):$(OBJS)
#	@echo "开始生成最终执行文件，请稍候..."
#	@echo "Full Version is:\033[31m\033[1m v1.0 \033[0m";
#	$(CC) $(CC_FLAGS) $(OBJS) -o $@ $(CL_FLAGS)

$(OBJS):%.o:%.c $(INC) Makefile
#	$(CC) $(CC_FLAGS) -I../src -c $<
#%.o: %.c
	$(CC) $(CC_FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGETS)

debug:
	@echo $(OBJS)
	$(warning is $(OBJS))
