all: build/hpm2tiff build/tiff2hpm
e: edit
edit:
	vi hpm2tiff.cc
t: test
test: build/hpm2tiff
	./build/hpm2tiff test.hpm test.tiff
build/hpm2tiff: hpm2tiff.cc
	cd build; cmake ..; make;
build/tiff2hpm: tiff2hpm.cc
	cd build; cmake ..; make;
c: clean
clean:
	cd build; make clean

