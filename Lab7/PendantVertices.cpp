#include"PendantVertices.h"

#include<iostream>

#define RESET   L"\033[0m"
#define RED     L"\033[31m"
#define GREEN   L"\033[32m"
#define BLUE    L"\033[34m"

void PendantVertices::printPendants(Graph graph) {
	std::vector<unsigned int> inDegree(graph.getVerticesCount(), 0);
	std::vector<unsigned int> outDegree(graph.getVerticesCount(), 0);

	for (const auto& edge : graph.getEdges()) {
		outDegree[edge.first - 1]++;
		inDegree[edge.second - 1]++;
	}

	size_t pendantCount = 0;

	for (size_t i = 0; i < graph.getVerticesCount(); i++)
		if (outDegree[i] + inDegree[i] == 1)
			pendantCount++;
	if (pendantCount == 0) {
		std::wcout << RED << L"≤н≥ц≥ал≥зований граф не м≥стить вис€чих(к≥нцевих) вершин.";
		std::wcout << RESET << std::endl;
		return;
	}
	else {
		for (size_t i = 0; i < graph.getVerticesCount(); i++)
			if (outDegree[i] + inDegree[i] == 1) {
				std::wcout << BLUE << L"¬ершина v" << (i + 1);
				std::wcout << GREEN << L"   Ї вис€чою(к≥нцевою)" << RESET << std::endl;
			}
	}
}

bool PendantVertices::isPendantVertex(Graph graph, size_t vertexNum) {
	std::vector<unsigned int> inDegree(graph.getVerticesCount(), 0);
	std::vector<unsigned int> outDegree(graph.getVerticesCount(), 0);

	for (const auto& edge : graph.getEdges()) {
		outDegree[edge.first - 1]++;
		inDegree[edge.second - 1]++;
	}

	return outDegree[vertexNum - 1] + inDegree[vertexNum - 1] == 1;
}