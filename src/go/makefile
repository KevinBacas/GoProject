
# r�gle pour Eclipse
all : compile

compile : $(BIN_FOLDER)/GoProject.out
	echo "Compilation des �x�cutables termin�e"
	
$(BIN_FOLDER)/GoProject.out : main.c $(DIST_FOLDER)/liste.o
	$(CC) $^ -L $(LIB_FOLDER) -l Matrice -o $@
	
$(DIST_FOLDER)/liste.o : liste.c $(INCLUDE_FOLDER)/liste.h
	$(CC) -c $< -o $@