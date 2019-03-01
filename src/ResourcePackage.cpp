#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <ResourcePackage.h>

#include "mlibc/mfile.h"

ResourcePackage::ResourcePackage(const char *packageName)
{
	this->packageName = packageName;
}

int ResourcePackage::init(char *path)
{	
	if (packageName.length() == 0)
	{
		packageName = path;
	}
	
	codeName.append(packageName.data());
	codeName.append(".c");
	code = fopen(codeName.data(), "w");
	if (NULL == code)
	{
		return -1;
	}
	
	headName.append(packageName.data());
	headName.append(".h");
	head = fopen(headName.data(), "w");
	if (NULL == head)
	{
		return -1;
	}
	
	return 0;
}

int ResourcePackage::append(char *resource)
{	
	FILE *res = NULL;
	string res_var_name(resource), tmp; 
	unsigned char data;
	char buf[10];
	int ret, count = 0;
	
	res = fopen(resource, "rb");
	
	res_var_name.replace(res_var_name.find_last_of("."), 1, "_");
	sprintf(buf, "%d", get_file_size(resource));
	
	tmp.append("int ");
	tmp += res_var_name;
	tmp.append("_len = ");
	tmp.append(buf);
	tmp.append(";\n");
	
	tmp.append("unsigned char ");
	tmp += res_var_name;
	tmp.append("[");
	
	tmp.append(buf);
	tmp.append("] = {\n");
	
	fwrite(tmp.data(), 1, tmp.length(), code);
	
	do{
		ret = fread(&data, 1, 1, res);
		if (ret <= 0)
		{
			break;
		}
		
		if (count == 0)
		{
			fwrite("\t", 1, strlen("\n"), code);	
		}
		
		sprintf(buf, "0x%02x,", data);
		fwrite(buf, 1, strlen(buf), code);
		count++;
		if (count == 10)
		{
			fwrite("\n", 1, strlen("\n"), code);
			count = 0;			
		}
	}while (!feof(res));
		
	fwrite("\n};", 1, 3, code);
	
	fclose(res);
	
	return 0;
}

int ResourcePackage::compile()
{
	string compileCmd = "gcc -c ";
	
	compileCmd.append(codeName.data());
	
	system(compileCmd.data());	
	return 0;
}

int ResourcePackage::package()
{
	fflush(code);
	fflush(head);
	fclose(code);
	fclose(head);
	
	compile();
	return 0;
}

int ResourcePackage::StaticPackage()
{
	string compileCmd = "ar rcs ";
	
	fflush(code);
	fflush(head);
	fclose(code);
	fclose(head);
	
	compile();
	
	compileCmd.append(packageName.data());
	compileCmd.append(".a ");
	compileCmd.append(packageName.data());
	compileCmd.append(".o");
	system(compileCmd.data());	
	return 0;
}

int ResourcePackage::DPackage()
{
	string compileCmd = "gcc -shared -o ";
	
	fflush(code);
	fflush(head);
	fclose(code);
	fclose(head);
	
	compile();
	
	compileCmd.append(packageName.data());
	compileCmd.append(".so ");
	compileCmd.append(packageName.data());
	compileCmd.append(".o");
	system(compileCmd.data());
	return 0;
}

int ResourcePackage::Unpackage(char *so, const char *res)
{
    void *handle = NULL;
	unsigned char *buf = NULL;
	int *len;
	int length;
	string res_len = res;
	FILE *resource = NULL;
	
    if((handle = dlopen(so, RTLD_NOW)) == NULL) 
	{
        printf("dlopen - %sn", dlerror());
        return -1;
    }
    
	res_len.append("_len");
	len = (int *)dlsym(handle, res_len.data());
    buf = (unsigned char *)dlsym(handle, res);
    
	resource = fopen(res, "wb");
	length = *len;
	while (length--)
	{
		fwrite(buf++, 1, 1, resource);	
	}
	
	fclose(resource);

	return 0;
}

int ResourcePackage::dump()
{
	std::cout << packageName << std::endl;
	
	return 0;
}