all: clean
	mkdir build
	cd build && cmake -DCMAKE_BUILD_TYPE=Release .. && make
	mv ./build/gestione_farmacia .

.PHONY: clean
clean:
	-rm -rf build
	-unlink gestione_farmacia
