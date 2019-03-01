all:upackage package
	
upackage:
	g++ upackage.cpp ../src/ResourcePackage.cpp -I ../include/ -I ../../platform/include/ -L ../../platform/libs/ -lmlibc -ldl -o upackage

package:
	g++ package.cpp ../src/ResourcePackage.cpp -I ../include/ -I ../../platform/include/ -L ../../platform/libs/ -lmlibc -ldl -o package
	
clean:
	@rm test
