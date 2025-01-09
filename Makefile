# Variáveis para o compilador e flags
CC = gcc
CFLAGS = -Wall

# Regra para compilar os arquivos
All: main.c src/io/fileReader/fileReader.c src/io/fileWriter/fileWriter.c src/dynamicProgramming/dynamicProgramming.c src/generateRandomDungeon/generateRandomDungeon.c src/utils/utils.c
	$(CC) $(CFLAGS) main.c src/io/fileReader/fileReader.c src/io/fileWriter/fileWriter.c src/dynamicProgramming/dynamicProgramming.c src/generateRandomDungeon/generateRandomDungeon.c src/utils/utils.c -o exec

# Regra para executar o código após compilar
Run: All
	./exec

# Tornar o alvo padrão o "Run"
.DEFAULT_GOAL := Run

# Regra para limpar os arquivos gerados
clean:
	rm -f exec