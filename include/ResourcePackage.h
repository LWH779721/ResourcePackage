#include <string>

using namespace std;

class ResourcePackage
{
	private:
		FILE *code;
		FILE *head;
		string packageName;
		string codeName;
		string headName;
		int compile();
	public:
		ResourcePackage(const char *packageName);
		ResourcePackage(){};
		int init(char *path);
		int init();
		int append(char *resource);
		int package();
		int StaticPackage();
		int DPackage();
		int Unpackage(char *so, const char *res);
		int dump();
};