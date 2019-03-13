#include <iostream>
#include <ResourcePackage.h>

using namespace std;

int main(int argc, char **args)
{
	ResourcePackage package1("music");
	
	package1.Unpackage("/home/lwh/workspace/ResourcePackage/src/music.so", "snowboy_wav");
	
	return 0;
}