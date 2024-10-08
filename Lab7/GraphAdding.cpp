#include"GraphAdding.h"
#include"GraphAddInstr.h"

#include<fstream>
#include<filesystem>
#include<iostream>

#include<thread>
#include<chrono>

#define RESET   L"\033[0m"
#define RED     L"\033[31m"
#define GREEN   L"\033[32m"

void CreateGraph::createFile() {
	std::wstring dir = inputPath();
	std::wstring name = inputName(dir);
	unsigned int verticesCount = getVerticesCount();
	uint64_t edgesCount = getEdgesCount(verticesCount);
	std::vector<std::pair<unsigned int, unsigned int>> edges;

	edges = getEdges(verticesCount, edgesCount);

	std::wstring filePath = dir + L"/" + name + L".txt";
	std::ofstream outFile(filePath);

	if (!outFile) {
		std::wcerr << "�� ������� ������� ���� ��� ������: " << filePath << std::endl;
		return;
	}
	outFile << verticesCount << ", " << edgesCount << std::endl;

	for (const auto& edge : edges) {
		outFile << edge.first << ", " << edge.second << std::endl;
	}

	outFile.close();

	std::wcout << GREEN << L"���� ����� �� �������������: " << filePath;
	std::wcout << L" ������ ���������!" << RESET << std::endl;

	system(std::string("notepad.exe ").append(std::filesystem::path(filePath).string().c_str()).c_str());
}

void CreateGraph::Create(Graph obj) {
	createFile();

	std::this_thread::sleep_for(std::chrono::milliseconds(10'000));
	return obj.makeAction();
}