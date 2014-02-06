
# r�gle pour Eclipse
all : compile

compile : $(BIN_FOLDER)/GoProject.out
	echo "Compilation des �x�cutables termin�e"
	
$(BIN_FOLDER)/GoProject.out : main.c $(DIST_FOLDER)/chaine.o $(DIST_FOLDER)/fonction.o $(DIST_FOLDER)/liste.o $(DIST_FOLDER)/pile.o $(DIST_FOLDER)/pion.o $(DIST_FOLDER)/plateau.o $(DIST_FOLDER)/position.o
	$(CC) $^ -L $(LIB_FOLDER) -l Matrice -o $@
	
$(DIST_FOLDER)/chaine.o : chaine.c $(INCLUDE_FOLDER)/chaine.h
	$(CC) -c $< -o $@
	
$(DIST_FOLDER)/fonction.o : fonction.c $(INCLUDE_FOLDER)/fonction.h
	$(CC) -c $< -o $@
	
$(DIST_FOLDER)/liste.o : liste.c $(INCLUDE_FOLDER)/liste.h
	$(CC) -c $< -o $@

$(DIST_FOLDER)/pile.o : pile.c $(INCLUDE_FOLDER)/pile.h
	$(CC) -c $< -o $@

$(DIST_FOLDER)/pion.o : pion.c $(INCLUDE_FOLDER)/pion.h
	$(CC) -c $< -o $@

$(DIST_FOLDER)/plateau.o : plateau.c $(INCLUDE_FOLDER)/plateau.h
	$(CC) -c $< -o $@

$(DIST_FOLDER)/position.o : position.c $(INCLUDE_FOLDER)/position.h
	$(CC) -c $< -o $@