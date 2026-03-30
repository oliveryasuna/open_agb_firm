build:
	cmake -B build -DCMAKE_TOOLCHAIN_FILE=cmake/DevkitARM.cmake
	cmake --build build

release:
	cmake -B build -DCMAKE_TOOLCHAIN_FILE=cmake/DevkitARM.cmake -DNO_DEBUG=ON
	cmake --build build

clean:
	rm -rf build
