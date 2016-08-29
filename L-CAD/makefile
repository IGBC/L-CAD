SHELL=/bin/bash

all: clean
	mkdir -p build
	cd build && cmake ..
	cd build && make -j $$(($$(grep -c ^processor /proc/cpuinfo) * 2))

clean:
	rm -Rfv build
	


