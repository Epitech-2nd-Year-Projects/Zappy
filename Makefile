.PHONY: all server client ai

all: server client ai

server:
	make -C zappy_server/

client:
	make -C zappy_client/

ai:
	make -C zappy_ai/