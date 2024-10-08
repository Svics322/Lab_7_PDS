#include"IsolatedVertices.h"

#include<iostream>

#define RESET   L"\033[0m"
#define RED     L"\033[31m"
#define GREEN   L"\033[32m"
#define BLUE    L"\033[34m"

void IsolatedVertices::printIsolated(Graph graph) {
	std::vector<unsigned int> inDegree(graph.getVerticesCount(), 0);
	std::vector<unsigned int> outDegree(graph.getVerticesCount(), 0);

	for (const auto& edge : graph.getEdges()) {
		outDegree[edge.first - 1]++;
		inDegree[edge.second - 1]++;
	}

	size_t isolatedCount = 0;

	for (size_t i = 0; i < graph.getVerticesCount(); i++)
		if (outDegree[i] == 0 && inDegree[i] == 0)
			isolatedCount++;
	if (isolatedCount == 0) {
		std::wcout << RED << L"Ініціалізований граф не містить ізольованих вершин.";
		std::wcout << RESET << std::endl;
		return;
	}
	else {
		for (size_t i = 0; i < graph.getVerticesCount(); i++) 
			if (outDegree[i] == 0 && inDegree[i] == 0) {
				std::wcout << BLUE << L"Вершина v" << (i + 1);
				std::wcout << GREEN << L"   є ізольованою" << RESET << std::endl;
			}
	}
}

bool IsolatedVertices::isIsolatedVertex(Graph graph, size_t vertexNum) {
	std::vector<unsigned int> inDegree(graph.getVerticesCount(), 0);
	std::vector<unsigned int> outDegree(graph.getVerticesCount(), 0);

	for (const auto& edge : graph.getEdges()) {
		outDegree[edge.first - 1]++;
		inDegree[edge.second - 1]++;
	}

	return outDegree[vertexNum - 1] == 0 && inDegree[vertexNum - 1] == 0;
}