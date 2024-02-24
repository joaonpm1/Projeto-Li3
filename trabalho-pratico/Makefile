CC = gcc
CFLAGS = -Wall -Iinclude `pkg-config --cflags glib-2.0`
LDFLAGS = `pkg-config --libs glib-2.0` -lm

INC_DIR = include
SRC_DIR = src
RESULTS_DIR = Resultados

SRC_MAIN = main.c
SRC_MAIN_TESTING = mainTesting.c
OBJS = $(patsubst $(SRC_DIR)/%.c, $(SRC_DIR)/%.o, $(wildcard $(SRC_DIR)/*.c))

PROGRAM = programa-principal
PROGRAM_TEST = programa-testes

.DEFAULT_GOAL = build

build: setup $(PROGRAM) $(PROGRAM_TEST)

$(PROGRAM): $(OBJS) $(SRC_DIR)/$(SRC_MAIN)
	$(CC) -I $(INC_DIR) -o $@ $^ $(CFLAGS) $(LDFLAGS) -Wl,--allow-multiple-definition

$(PROGRAM_TEST): $(OBJS) $(SRC_DIR)/$(SRC_MAIN_TESTING)
	$(CC) -I $(INC_DIR) -o $@ $^ $(CFLAGS) $(LDFLAGS) -DTESTING_MAIN -Wl,--allow-multiple-definition

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -I $(INC_DIR) -o $@ -c $< $(CFLAGS)

.PHONY: setup

.PHONY: clean
clean:
	@-rm -rf $(SRC_DIR)/*.o
	@-rm -f $(PROGRAM)
	@-rm -f $(PROGRAM_TEST)
	@-rm -rf $(RESULTS_DIR)/*.txt
	@-rm -rf $(RESULTS_DIR)/*.csv

