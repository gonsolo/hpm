all: build/hpm2tiff build/tiff2hpm
e: edit
edit:
	vi hpm2tiff.cc
t: test
test: build/hpm2tiff build/tiff2hpm
	./build/hpm2tiff examples/test.hpm test.tiff
	./build/tiff2hpm examples/desk.tiff desk.hpm
	./build/hpm2tiff desk.hpm desk.tiff
build/hpm2tiff: hpm2tiff.cc
	cd build; cmake ..; make;
build/tiff2hpm: tiff2hpm.cc
	cd build; cmake ..; make;
c: clean
clean:
	rm -f desk.hpm desk.tiff test.tiff
	cd build; make clean

