#pragma once

#include"Graph.h"

class GraphDegrees {
public:
	static void printDegrees(Graph graph);
	static void saveDegrees(Graph graph);

	static bool isHomogeneus(Graph graph);
};
