#include"Graph.h"

#include"GraphAdding.h"
#include"GraphReader.h"
#include"GraphDegrees.h"
#include"IsolatedVertices.h"
#include"PendantVertices.h"

#include"InstructionUtil.h"
#include<iostream>
#include<iomanip>
#include<thread>
#include<chrono>
#include <set>

#define RESET   L"\033[0m"
#define BOLD    L"\033[1m"
#define RED     L"\033[31m"
#define GREEN   L"\033[32m"
#define YELLOW  L"\033[33m"
#define BLUE    L"\033[34m"

// Private

unsigned int Graph::Introduction() {
	printInstructions();
	printUserOptions();
	return handleUserInput();
}

unsigned int Graph::Action() {
	printInstructions();
	printInitUserOptions();
	return handleInitUserInput();
}

void Graph::Clean() {
	this->N = 0;
	this->M = 0;
	this->E.clear();
}
// Public

void Graph::makeAction() {
	if (this->N == 0) {
		unsigned int action = this->Introduction();
		switch (action) {
		case 1:
			return CreateGraph::Create(*this);
			break;
		case 2:
			return GraphReader::ReadGraph(*this);
			break;
		case 3:
			return;
		}
	}
	else {
		unsigned int action = this->Action();
		switch (action) {
		case 1:
			return CreateGraph::Create(*this);
			break;
		case 2:
			this->Clean();
			return GraphReader::ReadGraph(*this);
			break;
		case 3:
			this->Clean();
			return this->makeAction();
			break;
		case 4:
			GraphDegrees::printDegrees(*this);
			std::this_thread::sleep_for(std::chrono::milliseconds(5'000));
			return this->makeAction();
			break;
		case 5:
			GraphDegrees::saveDegrees(*this);
			std::this_thread::sleep_for(std::chrono::milliseconds(5'000));
			return this->makeAction();
			break;
		case 6:
			IsolatedVertices::printIsolated(*this);
			std::this_thread::sleep_for(std::chrono::milliseconds(2'500));
			PendantVertices::printPendants(*this);
			std::this_thread::sleep_for(std::chrono::milliseconds(2'500));
			return this->makeAction();
			break;
		case 7:
			return;
		}
	}
}

bool Graph::checkValid(size_t N, size_t M, std::vector<std::pair<unsigned int, unsigned int>> E) {
	if (N < 1 || M > pow(N, 2.0f))
		return false;

	std::set<std::pair<unsigned int, unsigned int>> uniqueEdges;
	for (const auto& edge : E) {
		unsigned int u = edge.first;
		unsigned int v = edge.second;

		if (u < 1 || v < 1)
			return false;

		if (uniqueEdges.count(edge) > 0)
			return false;
		uniqueEdges.insert(edge);
	}
	return true;
}

// Constructors

Graph::Graph() : N(0), M(0) {
	this->makeAction();
}

Graph::Graph(size_t N, size_t M, std::vector<std::pair<unsigned int, unsigned int>> E, bool test): N(N), M(M), E(E){
	if (!this->checkValid(N, M, E))
		this->Clean();
	if(test == false)
		this->makeAction();
}