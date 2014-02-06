# Flags de compilation pour le C
CFLAGS = -Wall

# R�cup�ration du dossier courant, on admet que l'utilisateur fait un make � partir de la racine du projet.
TOP_FOLDER = $(shell pwd)

# Construction des variables contenant les chemins des dossiers
export LIB_FOLDER = $(TOP_FOLDER)/lib
export INCLUDE_FOLDER = $(TOP_FOLDER)/include
export SRC_FOLDER = $(TOP_FOLDER)/src
export BIN_FOLDER = $(TOP_FOLDER)/bin
export DIST_FOLDER = $(BIN_FOLDER)/dist

#Commande GCC G�n�rique
export CC = gcc $(CFLAGS) -I $(INCLUDE_FOLDER)

# r�gle pour la build eclipse
all : compile

# Compilation de tout le projet (G�n�ration des biblioth�que et des executables)
compile : 
	@cd $(SRC_FOLDER)/matrice && make --no-print-directory
	@cd $(SRC_FOLDER)/go && make --no-print-directory

# Clean de tout les fichiers .o dans le dossier dist
clean : 
	@rm -rvf $(DIST_FOLDER)/*.o
	@rm -rvf $(BIN_FOLDER)/*.out
