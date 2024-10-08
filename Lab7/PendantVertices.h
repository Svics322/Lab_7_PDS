#pragma once
#include"Graph.h"

class PendantVertices {
public:
	static void printPendants(Graph graph);
	static bool isPendantVertex(Graph graph, size_t vertexNum);
};