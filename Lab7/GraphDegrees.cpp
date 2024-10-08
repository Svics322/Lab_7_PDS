#include"GraphDegrees.h"
#include"GraphAddInstr.h"

#include<iostream>

#include<fstream>
#include<filesystem>

#define RESET   L"\033[0m"
#define RED     L"\033[31m"
#define GREEN   L"\033[32m"
#define BLUE    L"\033[34m"

void GraphDegrees::printDegrees(Graph graph) {
	std::vector<unsigned int> inDegree(graph.getVerticesCount(), 0);
	std::vector<unsigned int> outDegree(graph.getVerticesCount(), 0);

	std::wcout << RED << L"Ступені вершин графа:" << RESET << std::endl;

	for (const auto& edge : graph.getEdges()) {
		outDegree[edge.first - 1]++;
		inDegree[edge.second - 1]++;
	}

	for (size_t i = 0; i < graph.getVerticesCount() + 0; i++) {
		std::wcout << BLUE << L"Вершина v" << (i + 1) << RESET;
		std::wcout << RED << L"   deg+(v" << (i + 1) << L") = " << inDegree[i];
		std::wcout << L";  deg-(v" << (i + 1) << L") = " << outDegree[i] << RESET << std::endl;
	}

	bool isSHomogeneus = true;
	
	for (size_t i = 0; i < graph.getVerticesCount(); i++) 
		if (inDegree[0] != inDegree[i] || outDegree[0] != outDegree[i]) {
			isSHomogeneus = false;
			break;
		}
	
	if (isSHomogeneus) {
		std::wcout << RED << L"Граф є однорідним." << RESET << std::endl;
		std::wcout << RED << L"Степінь однорідності deg+ = deg- = " << inDegree[0] << RESET << std::endl;
	}
	else
		std::wcout << RED << L"Граф не є однорідним." << RESET << std::endl;
	
};

void GraphDegrees::saveDegrees(Graph graph) {
	std::vector<unsigned int> inDegree(graph.getVerticesCount(), 0);
	std::vector<unsigned int> outDegree(graph.getVerticesCount(), 0);
	
	for (const auto& edge : graph.getEdges()) {
		outDegree[edge.first - 1]++;
		inDegree[edge.second - 1]++;
	}

	bool isSHomogeneus = true;

	for (size_t i = 0; i < graph.getVerticesCount(); i++)
		if (inDegree[0] != inDegree[i] || outDegree[0] != outDegree[i]) {
			isSHomogeneus = false;
			break;
		}

	std::wstring dir = inputPath();
	std::wstring name = inputName(dir);

	std::filesystem::path filePath = std::filesystem::path(dir) / (name + L".txt");
	std::ofstream outFile(filePath);

	if (!outFile) {
		std::wcerr << L"Не вдалося відкрити файл для запису: " << filePath << std::endl;
		return;
	}

	outFile << graph.getVerticesCount() << ", " << graph.getEdgesCount()<< std::endl;

	for (const auto& edge : graph.getEdges()) {
		outFile << edge.first << ", " << edge.second << std::endl;
	}

	for (size_t i = 0; i < graph.getVerticesCount() + 0; i++) {
		outFile << "Вершина v" << (i + 1) << "   deg+(v" << (i + 1) << ") = " << inDegree[i];
		outFile << ";  deg-(v" << (i + 1) << ") = " << outDegree[i] <<  std::endl;
	}
	if (isSHomogeneus) {
		outFile << "Граф є однорідним." << std::endl;
		outFile << "Степінь однорідності deg+ = deg- = " << inDegree[0] << std::endl;
	}
	else
		outFile << "Граф не є однорідним." << std::endl;
	outFile.close();

	std::wcout << GREEN << L"Файл графу з степенями вершин збережено за розташуванням:";
	std::wcout << RED << dir + L"/" + name + L".txt" << RESET << std::endl;
		
	system(std::string("notepad.exe ").append(filePath.string().c_str()).c_str());
}

bool  GraphDegrees::isHomogeneus(Graph graph) {
	std::vector<unsigned int> inDegree(graph.getVerticesCount(), 0);
	std::vector<unsigned int> outDegree(graph.getVerticesCount(), 0);

	for (const auto& edge : graph.getEdges()) {
		outDegree[edge.first - 1]++;
		inDegree[edge.second - 1]++;
	}

	bool isSHomogeneus = true;

	for (size_t i = 0; i < graph.getVerticesCount(); i++)
		if (inDegree[0] != inDegree[i] || outDegree[0] != outDegree[i]) {
			isSHomogeneus = false;
			break;
		}

	return isSHomogeneus;
}