CC= g++

main:
	${CC} -g -o main main.cpp Sorting.cpp CompSorting.cpp DataGenerator.cpp

test: test/sorting_test.cpp
	${CC} -g -o sorting_test Sorting.cpp DataGenerator.cpp test/sorting_test.cpp

clean:
	rm -f main
	rm -f sorting_test
	rm -f output.txt