# Flags de compilation pour le C
CFLAGS = -Wall

# Recuperation du dossier courant, on admet que l'utilisateur fait un make a partir de la racine du projet.
TOP_FOLDER = $(shell pwd)

# Construction des variables contenant les chemins des dossiers
export LIB_FOLDER = $(TOP_FOLDER)/lib
export INCLUDE_FOLDER = $(TOP_FOLDER)/include
export SRC_FOLDER = $(TOP_FOLDER)/src
export BIN_FOLDER = $(TOP_FOLDER)/bin
export DIST_FOLDER = $(BIN_FOLDER)/dist

#Commande GCC Generique
export CC = gcc $(CFLAGS) -I $(INCLUDE_FOLDER)

# regle pour la build eclipse
all : compile

# Compilation de tout le projet (Generation des bibliotheque et des executables)
compile : 
	@cd $(SRC_FOLDER)/matrice && make --no-print-directory
	@cd $(SRC_FOLDER)/go && make --no-print-directory

# Clean de tout les fichiers .o dans le dossier dist
clean : 
	@rm -rvf $(LIB_FOLDER)/*.so
	@rm -rvf $(DIST_FOLDER)/*.o
	@rm -rvf $(BIN_FOLDER)/*.out
	
rebuild : clean compile
	@echo "Rebuild fait."
