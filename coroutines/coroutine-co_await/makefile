
############################################
# Prosty generator plikow makefile dla g++ #
# Simple generator of makefiles for g++    #
#          Krzysztof Siminski, 2023        #
############################################

# [PL] OPCJE:
# [EN] OPTIONS:

compiler=g++
standard=-std=c++23

# [PL] optymalizacja [EN] optimisation
optRelease=-O3
optDebug=

errors=-pedantic-errors

release=
#debug=-g
# [PL] opcja -pg dla profilowania:
# [EN] -pg option for profiling:
debug=-pg

#parallel=-fopenmp
parallel=

release_folder=_release
debug_folder=_debug

#sanitizer=-fsanitize=address
#libasan=-static-libasan
sanitizer=
libasan=

#############################

.PHONY : clean $(debug_folder) $(release_folder)

# [PL] opcje uruchomienia projektu:
# [EN] project run options:

release : $(release_folder) $(release_folder)/main
	./$(release_folder)/main

debug : $(debug_folder) $(debug_folder)/main
	valgrind --leak-check=yes ./$(debug_folder)/main
#	./$(debug_folder)/main

# [PL] profilowanie [EN] profiling
gprof : $(debug_folder) $(debug_folder)/main
	./$(debug_folder)/main
	gprof ./$(debug_folder)/main gmon.out
	rm gmon.out

# [PL] utworzenie folderow:
# [EN] create directories:

$(release_folder) : 
	mkdir -p $(release_folder)
$(debug_folder) : 
	mkdir -p $(debug_folder)

# [PL] kompilacja zrodel:
# [EN] source compilation:

$(release_folder)/main.o : main.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/main.o : main.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^

# [PL] linkowanie:
# [EN] linking:

$(release_folder)/main : \
$(release_folder)/main.o \

	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -o $@ $^

$(debug_folder)/main : \
$(debug_folder)/main.o \

	$(compiler) $(standard) $(debug) $(optDebug) $(parallel) $(errors) $(sanitizer) $(libasan) -o $@ $^

# [PL] usuniecie plikow skompilowanych:
# [EN] remove compiled files:

clean : 
	if [ -d $(debug_folder)      ] ; then rm -r $(debug_folder)   ; fi
	if [ -d $(release_folder)    ] ; then rm -r $(release_folder) ; fi;


5-minutes:
	find $(release_folder)/ -maxdepth 1 -type f -mmin -5 -delete
	find $(debug_folder)/ -maxdepth 1 -type f -mmin -5 -delete

10-minutes:
	find $(release_folder)/ -maxdepth 1 -type f -mmin -10 -delete
	find $(debug_folder)/ -maxdepth 1 -type f -mmin -10 -delete

30-minutes:
	find $(release_folder)/ -maxdepth 1 -type f -mmin -30 -delete
	find $(debug_folder)/ -maxdepth 1 -type f -mmin -30 -delete

60-minutes:
	find $(release_folder)/ -maxdepth 1 -type f -mmin -60 -delete
	find $(debug_folder)/ -maxdepth 1 -type f -mmin -60 -delete

1-days:
	find $(release_folder)/ -maxdepth 1 -type f -mtime -1 -delete
	find $(debug_folder)/ -maxdepth 1 -type f -mtime -1 -delete

doxygen:
	doxygen doxyfile

