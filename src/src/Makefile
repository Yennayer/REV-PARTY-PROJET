CC=gcc
CFLAGS=-Wall -g
EXEC=main_program

# Liste des fichiers source
SRCS= condorcet.c condorcet_paires.c condorcet_Schulze.c    utils_sd.c

# Convertir les fichiers source en fichiers objets
OBJS=$(SRCS:.c=.o)

# Règle par défaut
all: $(EXEC)

# Règle pour créer l'exécutable
$(EXEC): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

# Règle générique pour les fichiers objet
%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

# Nettoyage
.PHONY: clean
clean:
	rm -f $(OBJS) $(EXEC)


