
# règle pour Eclipse
all : compile

compile : $(BIN_FOLDER)/GoProject.out
	echo "Compilation des éxécutables terminée"
	
$(BIN_FOLDER)/GoProject.out : main.c
	$(CC) $< -L $(LIB_FOLDER) -l Matrice -I $(INCLUDE_FOLDER) -o $@
	
