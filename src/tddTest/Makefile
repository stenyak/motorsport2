all: 
	g++ -o tddTest *.cpp -fprofile-arcs -ftest-coverage -lunittest++

.PHONY: clean
clean:
	rm *.o tddTest *.gcov *.gc* || true

.PHONY: run
run:
	./tddTest

.PHONY: cov
cov:
	gcov *.cpp
	grep -H "####" *.cpp.gcov |sed "s/\.gcov:/:/g;s/[\ ]*#####:[\ ]*//g;s/$$/  \/\/warning: line not covered\./g"
