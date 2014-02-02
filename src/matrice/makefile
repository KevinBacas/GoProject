# Point d'entré pour la génération des bibliothèques
matrice_libs : $(LIB_FOLDER)/Matrice.dll
	@echo "Compilation des bibliotèques terminé"

# .o de la matrice dynamique
$(DIST_FOLDER)/matriceShared.o : matrice.c $(INCLUDE_FOLDER)/matrice.h
	$(GCC) -c $< -o $@
	#$(GCC) -fPIC -c $< -o $@

# Génération de la bibliothèque dynamique (.so)
$(LIB_FOLDER)/Matrice.dll : $(DIST_FOLDER)/matriceShared.o
	$(GCC) -shared $< -o $@

$(DIST_FOLDER)/matriceTest.o : matriceTest.c $(INCLUDE_FOLDER)/matrice.h
	$(GCC) -c $< -o $@

$(BIN_FOLDER)/matriceTest.out : $(DIST_FOLDER)/matriceTest.o
	$(GCC) $< -o $@
