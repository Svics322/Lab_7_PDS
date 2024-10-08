#include "pch.h"
#include "CppUnitTest.h"
#include<vector>
#include<filesystem>

#include"..\Lab7\Graph.cpp"
#include"..\Lab7\GraphAdding.cpp"
#include"..\Lab7\GraphReader.cpp"
#include"..\Lab7\GraphDegrees.cpp"
#include"..\Lab7\IsolatedVertices.cpp"
#include"..\Lab7\PendantVertices.cpp"

#include"..\Lab7\GraphAddInstr.cpp"
#include"..\Lab7\GraphReadInstr.cpp"
#include"..\Lab7\InstructionUtil.cpp"
#include"..\Lab7\PathUtil.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(TestPendantVertices)
		{
			size_t N = 10, M = 5;
			std::vector<std::pair<unsigned int, unsigned int>> E;
			E = { {1, 2}, {2, 3}, {1, 1}, {1, 9}, {9, 10} };
			Graph graph = Graph(N, M, E, true);
			Assert::IsTrue(PendantVertices::isPendantVertex(graph, 3));
			Assert::IsTrue(PendantVertices::isPendantVertex(graph, 10));
		}
		TEST_METHOD(TestIsolatedVertices)
		{
			size_t N = 10, M = 5;
			std::vector<std::pair<unsigned int, unsigned int>> E;
			E = { {1, 2}, {2, 3}, {1, 1}, {1, 9}, {9, 10} };
			Graph graph = Graph(N, M, E, true);
			Assert::IsTrue(IsolatedVertices::isIsolatedVertex(graph, 4));
			Assert::IsTrue(IsolatedVertices::isIsolatedVertex(graph, 5));
			Assert::IsTrue(IsolatedVertices::isIsolatedVertex(graph, 6));
			Assert::IsTrue(IsolatedVertices::isIsolatedVertex(graph, 7));
			Assert::IsTrue(IsolatedVertices::isIsolatedVertex(graph, 8));
		}
		TEST_METHOD(TestIsolatedVertices_ERROR)
		{
			size_t N = 10, M = 5;
			std::vector<std::pair<unsigned int, unsigned int>> E;
			E = { {1, 2}, {2, 3}, {1, 1}, {1, 9}, {9, 10} };
			Graph graph = Graph(N, M, E, true);
			Assert::IsTrue(IsolatedVertices::isIsolatedVertex(graph, 9));			
		}
	};
}
