# Point d'entr� pour la g�n�ration des biblioth�ques
matrice_libs : $(LIB_FOLDER)/libMatrice.so
	@echo "Compilation des bibliot�ques termin�"

# .o de la matrice dynamique
$(DIST_FOLDER)/matriceShared.o : matrice.c $(INCLUDE_FOLDER)/matrice.h
	$(CC) -fPIC -c $< -o $@

# G�n�ration de la biblioth�que dynamique (.so)
$(LIB_FOLDER)/libMatrice.so : $(DIST_FOLDER)/matriceShared.o
	$(CC) -shared $< -o $@

$(DIST_FOLDER)/matriceTest.o : matriceTest.c $(INCLUDE_FOLDER)/matrice.h
	$(CC) -c $< -o $@

$(BIN_FOLDER)/matriceTest.out : $(DIST_FOLDER)/matriceTest.o
	$(CC) $< -o $@
