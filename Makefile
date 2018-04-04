all: build/hpm2tiff build/tiff2hpm
e: edit
edit:
	vi hpm2tiff.cc
t: test
test: build/hpm2tiff build/tiff2hpm
	./build/hpm2tiff examples/test.hpm test.tiff
	./build/tiff2hpm examples/desk.tiff desk.hpm
	./build/hpm2tiff desk.hpm desk.tiff
cmake:
	cd build; cmake ..
build/hpm2tiff: cmake hpm2tiff.cc
	cd build; $(MAKE)
build/tiff2hpm: cmake tiff2hpm.cc
	cd build; $(MAKE)
c: clean
clean:
	rm -f desk.hpm desk.tiff test.tiff
	cd build; $(MAKE) clean; rm -rf *
install: build/hpm2tiff build/tiff2hpm
	cp $^ ~/bin

.PHONY: all e edit t test cmake c clean install

