#pragma once

#include<vector>

class Graph {
private:

	/*N  - кількість вершин графу
	 M  - кількість ребер графу*/

	size_t N, M;
	std::vector<std::pair<unsigned int, unsigned int>> E;

	unsigned int Introduction();
	unsigned int Action();

	void Clean();
public:
	void makeAction();

	size_t getVerticesCount() const { return this->N; };
	size_t getEdgesCount() const { return this->M; };
	std::vector<std::pair<unsigned int, unsigned int>> getEdges() const { return this->E; };
	void setVerticesCount(const unsigned int& N) { this->N = N; };
	void setEdgesCount(const unsigned int& M) { this->M = M; };
	void setEdges(const std::vector <std::pair<unsigned int, unsigned int>>& E) { this->E = E; };

	bool checkValid(size_t N, size_t M, std::vector<std::pair<unsigned int, unsigned int>> E);

	Graph();
	Graph(size_t N, size_t M, std::vector<std::pair<unsigned int, unsigned int>> E, bool test = false);

};