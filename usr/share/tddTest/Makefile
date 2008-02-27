all: 
	mkdir -p bin
	g++ -o bin/tddTest *.cpp -fprofile-arcs -ftest-coverage -L../../lib -I../../include ../../lib/libUnitTest++.a
	#g++ -o bin/tddTest *.cpp -fprofile-arcs -ftest-coverage -lunittest++ -L../../lib -I../../include ../../lib/libUnitTest++.a

.PHONY: clean
clean:
	rm *.o bin/tddTest *.gcov *.gc* || true
	rmdir -rf bin || true

.PHONY: run
run:
	bin/tddTest

.PHONY: cov
cov:
	gcov *.cpp
	grep -H "####" *.cpp.gcov |sed "s/\.gcov:/:/g;s/[\ ]*#####:[\ ]*//g;s/$$/  \/\/warning: line not covered\./g"
