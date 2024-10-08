#include<Windows.h>
#include"Graph.h"
#include<locale>
#include<codecvt>

int main(int argc, char** argv[]) {
	std::locale::global(std::locale("uk_UA.UTF-8"));
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
	Graph graph = Graph();

	return 0;
}