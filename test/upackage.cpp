#include <iostream>
#include <ResourcePackage.h>

using namespace std;

int main(int argc, char **args)
{
	ResourcePackage package1("music");
#if 0	
	package1.dump();
	package1.init("");
	package1.append("snowboy.wav");
	package1.DPackage();
#endif	
	package1.Unpackage("/home/lwh/workspace/ResourcePackage/src/music.so", "snowboy_wav");
	
	return 0;
}