PROJECT = 	myshell
HEADERS = 	$(PROJECT).h
OBJ		= 	myshell.o globals.o execute.o parser.o step1_external.o step2_searchPath.o step3_internalCommand.o step4_sequential.o step5_subshell.o step6_fileRedirection.o step7_pipeline.o step8_shellScript.o step9_background.o

C99 = cc -std=c99
CFLAGS = -Wall -pedantic -Werror

$(PROJECT) : $(OBJ)
	$(C99) $(CFLAGS) -o $(PROJECT) $(OBJ)

%.o : %.c $(HEADERS)
	$(C99) $(CFLAGS) -c $<

clean:
	rm -f $(PROJECT) $(OBJ)