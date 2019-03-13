#include <iostream>
#include <ResourcePackage.h>

using namespace std;

int main(int argc, char **args)
{
	ResourcePackage package1("music");
	
	package1.dump();
	package1.init("");
	package1.append(args[1]);
	package1.DPackage();
	
	return 0;
}