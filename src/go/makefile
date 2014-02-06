
# regle pour Eclipse
all : compile

compile : $(BIN_FOLDER)/GoProject.out
	echo "Compilation des executables terminee"
	
$(BIN_FOLDER)/GoProject.out : main.c $(DIST_FOLDER)/chaine.o $(DIST_FOLDER)/ensembleColore.o $(DIST_FOLDER)/liste.o $(DIST_FOLDER)/partie.o $(DIST_FOLDER)/pile.o $(DIST_FOLDER)/pion.o $(DIST_FOLDER)/plateau.o $(DIST_FOLDER)/position.o $(DIST_FOLDER)/utilsGo.o
	$(CC) $^ -L $(LIB_FOLDER) -l Matrice -o $@
	
$(DIST_FOLDER)/chaine.o : chaine.c $(INCLUDE_FOLDER)/chaine.h
	$(CC) -c $< -o $@
	
$(DIST_FOLDER)/ensembleColore.o : ensembleColore.c $(INCLUDE_FOLDER)/ensembleColore.h
	$(CC) -c $< -o $@
	
$(DIST_FOLDER)/liste.o : liste.c $(INCLUDE_FOLDER)/liste.h
	$(CC) -c $< -o $@
	
$(DIST_FOLDER)/partie.o : partie.c $(INCLUDE_FOLDER)/partie.h
	$(CC) -c $< -o $@

$(DIST_FOLDER)/pile.o : pile.c $(INCLUDE_FOLDER)/pile.h
	$(CC) -c $< -o $@

$(DIST_FOLDER)/pion.o : pion.c $(INCLUDE_FOLDER)/pion.h
	$(CC) -c $< -o $@

$(DIST_FOLDER)/plateau.o : plateau.c $(INCLUDE_FOLDER)/plateau.h
	$(CC) -c $< -o $@

$(DIST_FOLDER)/position.o : position.c $(INCLUDE_FOLDER)/position.h
	$(CC) -c $< -o $@
	
$(DIST_FOLDER)/utilsGo.o : utilsGo.c $(INCLUDE_FOLDER)/utilsGo.h
	$(CC) -c $< -o $@
