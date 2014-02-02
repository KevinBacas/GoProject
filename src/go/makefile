
# règle pour Eclipse
all : compile

compile : $(BIN_FOLDER)/GoProject.out
	echo "Compilation des éxécutables terminée"
	
$(BIN_FOLDER)/GoProject.out : main.c $(DIST_FOLDER)/liste.o
	$(CC) $< -L $(LIB_FOLDER) -l Matrice -o $@
	
$(DIST_FOLDER)/liste.o : $(INCLUDE_FOLDER)/liste.h
	$(CC) $< -o $@