kompilator=g++
standard=-std=c++23
optymalizacja=-O3
errors=-pedantic-errors -Wall

# debug=-g
debug=

.PHONY : clean 

__ : main
	./main

#	valgrind --leak-check=yes ./main

main.o : main.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(errors) -c -o $@ $^
main : main.o 
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(errors) -o $@ $^
clean : 
	rm main main.o 

