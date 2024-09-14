template:
	g++ ./src/template_main.cpp -o template_main -O3 -Wall -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

default:
	@echo "append a option"