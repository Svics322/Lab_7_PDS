#pragma once

#include"Graph.h"

class IsolatedVertices {
public:
	static void printIsolated(Graph graph);
	static bool isIsolatedVertex(Graph graph, size_t vertexNum);
};