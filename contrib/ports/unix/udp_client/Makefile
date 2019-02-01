TARGET=udp_client

CC = gcc
LD = ld
OBJCOPY = objcopy
SIZE = size
CFLAGS =  -g -Wall
CFLAGS += -Wl,-Map=$(TARGET).map
LDFLAGS	= 

SRC = udp_client.c
#$(warning $$SRC is $(SRC))
OBJS = $(addsuffix .o, $(basename $(SRC)))
#$(warning $$OBJS is $(OBJS))

all:$(TARGET)

$(TARGET):$(OBJS)
	@echo "开始生成最终执行文件，请稍候..."
#	@echo "Full Version is:\033[31m\033[1m v1.0 \033[0m";
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) -c -o $@ $(CFLAGS) $<

clean:
	rm $(OBJS) $(TARGET) $(TARGET).map

debug:
	@echo $(OBJS)
	$(warning is $(OBJS))
