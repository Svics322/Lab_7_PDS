#include"GraphReader.h"
#include"PathUtil.h"

#include<fstream>
#include<iostream>
#include<sstream>

#include<algorithm>
#include<iterator>
#include<locale>
#include <regex>
#include<thread>
#include<chrono>

#define RESET   L"\033[0m"
#define RED     L"\033[31m"
#define GREEN   L"\033[32m"

// Init methods for check vertices and edges count validaton

bool GraphReader::readVerticesCount(const std::wstring& line, unsigned int& value) {
	try {
		size_t pos;
		int64_t tempValue = std::stoll(line, &pos);
		if (pos == line.length() && tempValue <= std::numeric_limits<unsigned int>::max() && tempValue > 0) {
			value = static_cast<unsigned int>(tempValue);
			return true;
		}
		else {
			std::wcerr << RED << L"�������: ������� ������ ����� �� � ������ unsigned int ";
			std::wcerr << L"��� �������� �� ��� ���������� �������!" << RESET << std::endl;
			return false;
		}
	}
	catch (const std::invalid_argument&) {
		std::wcerr << RED << L"�������: ������� �������� ������� ������ �����! " << RESET << std::endl;
		return false;
	}
	catch (const std::out_of_range&) {
		std::wcerr << RED << L"�������: �������� ������� ������ ����� �������� �� ��� ���������� �������! " << RESET << std::endl;
		return false;
	}
	catch (const std::exception& e) {
		std::wcerr << RED << L"������� ������� ��� ��������� ������� ������ �����: " << e.what() << RESET << std::endl;
		return false;
	}
	return true;
}

bool GraphReader::readEdgesCount(const std::wstring& line, unsigned int& value, unsigned int verticesCount) {
	try {
		size_t pos;
		int64_t tempValue = std::stoll(line, &pos);
		if (pos == line.length() && tempValue <= std::numeric_limits<unsigned int>::max() && tempValue > 0) {
			value = static_cast<unsigned int>(tempValue);
			double maxVal = pow(verticesCount, 2.0);
			if (value >= maxVal) {
				std::wcerr << RED << L"������� � �������� ����� � ����." << std::endl;
				std::wcerr << L"�������� ������� ����� � ������ ���� - " << value << std::endl;
				std::wcerr << L"����������� �������� ������� ����� - " << maxVal << std::endl;
				std::wcerr << L"����� ��������� ����� � ���� ��� ������� ";
				std::wcerr << L"����� ��������� ���� �����!" << RESET << std::endl;
				return false;
			}
			return true;
		}
		else {
			std::wcerr << RED << L"�������: ������� ����� ����� �� � ������ unsigned int ";
			std::wcerr << L"��� �������� �� ��� ���������� �������!" << RESET << std::endl;
			return false;
		}
	}
	catch (const std::invalid_argument&) {
		std::wcerr << RED << L"�������: ������� �������� ������� ����� �����! " << RESET << std::endl;
		return false;
	}
	catch (const std::out_of_range&) {
		std::wcerr << RED << L"�������: �������� ������� ����� ����� �������� �� ��� ���������� �������! " << RESET << std::endl;
		return false;
	}
	catch (const std::exception& e) {
		std::wcerr << RED << L"������� ������� ��� ��������� ������� ����� �����: " << e.what() << RESET << std::endl;
		return false;
	}
	return true;
}

bool GraphReader::readEdgeStartPoint(const std::wstring& line, unsigned int& value,
	unsigned int edgeIndex, const unsigned int verticesCount) {
	try {
		size_t pos;
		int64_t tempValue = std::stoll(line, &pos);
		if (pos == line.length() && tempValue <= std::numeric_limits<unsigned int>::max() && tempValue > 0) {
			value = static_cast<unsigned int>(tempValue);
			if (value > verticesCount) {
				std::wcerr << RED << L"������� � �������� ����� � ����." << std::endl;
				std::wcerr << L"�������� ��������� ����� ����� �� �������� " << edgeIndex;
				std::wcerr << L" � ������ ���� - " << value << std::endl;
				std::wcerr << L"����������� �������� ����� ����� - " << verticesCount << std::endl;
				std::wcerr << L"����� ��������� ����� � ���� ��� ������� ";
				std::wcerr << L"����� ��������� ���� �����!" << RESET << std::endl;
				return false;
			}
			return true;
		}
		else {
			std::wcerr << RED << L"������� � ���� " << edgeIndex << L": ��������� ����� �� � ������ unsigned int ��� �������� �� ��� ���������� �������!" << RESET << std::endl;
			return false;
		}
	}
	catch (const std::invalid_argument&) {
		std::wcerr << RED << L"������� � ���� " << edgeIndex << L": ������� �������� ��� ��������� �����!" << RESET << std::endl;
		return false;
	}
	catch (const std::out_of_range&) {
		std::wcerr << RED << L"������� � ���� " << edgeIndex << L": �������� ��� ��������� ����� �������� �� ��� ���������� �������!" << RESET << std::endl;
		return false;
	}
	catch (const std::exception& e) {
		std::wcerr << RED << L"������� ������� � ���� " << edgeIndex << L" ��� ��������� ��������� �����: " << e.what() << RESET << std::endl;
		return false;
	}
	return true;
}

bool GraphReader::readEdgeEndPoint(const std::wstring& line, unsigned int& value,
	unsigned int edgeIndex, const unsigned int verticesCount) {
	try {
		size_t pos;
		int64_t tempValue = std::stoll(line, &pos);
		if (pos == line.length() && tempValue <= std::numeric_limits<unsigned int>::max() && tempValue > 0) {
			value = static_cast<unsigned int>(tempValue);
			if (value > verticesCount) {
				std::wcerr << RED << L"������� � �������� ����� � ����." << std::endl;
				std::wcerr << L"�������� ������ ����� ����� �� �������� " << edgeIndex;
				std::wcerr << L" � ������ ���� - " << value << std::endl;
				std::wcerr << L"����������� �������� ����� ����� - " << verticesCount << std::endl;
				std::wcerr << L"����� ��������� ����� � ���� ��� ������� ";
				std::wcerr << L"����� ��������� ���� �����!" << RESET << std::endl;
				return false;
			}
			return true;
		}
		else {
			std::wcerr << RED << L"������� � ���� " << edgeIndex << L": ������ ����� �� � ������ unsigned int ��� �������� �� ��� ���������� �������!" << RESET << std::endl;
			return false;
		}
	}
	catch (const std::invalid_argument&) {
		std::wcerr << RED << L"������� � ���� " << edgeIndex << L": ������� �������� ��� ������ �����!" << RESET << std::endl;
		return false;
	}
	catch (const std::out_of_range&) {
		std::wcerr << RED << L"������� � ���� " << edgeIndex << L": �������� ��� ������ ����� �������� �� ��� ���������� �������!" << RESET << std::endl;
		return false;
	}
	catch (const std::exception& e) {
		std::wcerr << RED << L"������� ������� � ���� " << edgeIndex << L" ��� ��������� ������ �����: " << e.what() << RESET << std::endl;
		return false;
	}
	return true;
}

bool GraphReader::readEdges(std::wifstream& file,
	std::vector<std::pair<unsigned int, unsigned int>>& edges, const unsigned int verticesCount) {
	std::wstring line;
	unsigned int edgeIndex = 1;

	while (std::getline(file, line)) {
		std::wregex format(L"^\\d+\\s*,\\s*\\d+$");
		if (!std::regex_match(line, format)) {
			std::wcerr << RED << L"������� � �������� ����� � ����." << std::endl;
			std::wcerr << L"ϳ� ��� ����������� ����� � ���� ���� �������� �������." << std::endl;
			std::wcerr << L"����� �� ��������: " << edgeIndex << L" ����������� ��������." << std::endl;
			std::wcerr << L"����� ����� ������� ������ ������ \"����� ���� �����\"." << std::endl;
			std::wcerr << L"����� ��������� ����� � ���� ��� ������� ";
			std::wcerr << L"����� ��������� ���� �����!" << RESET << std::endl;
			return false;
		}
		std::wstringstream ss(line);
		std::wstring temp;
		unsigned int start, end;

		if (std::getline(ss, temp, L',')) {
			temp.erase(std::remove_if(temp.begin(), temp.end(), iswspace), temp.end());
			if (!readEdgeStartPoint(temp, start, edgeIndex, verticesCount)) {
				return false;
			}
		}

		if (std::getline(ss, temp)) {
			if (!readEdgeEndPoint(temp, end, edgeIndex, verticesCount)) {
				return false;
			}
		}
		if (auto it = std::find(edges.begin(), edges.end(), std::make_pair(start, end)); it != edges.end()) {
			size_t index = std::distance(edges.begin(), it) + 1;
			std::wcerr << RED << L"������� � �������� ����� � ����." << std::endl;
			std::wcerr << L"����� �� ������ �������������." << std::endl;
			std::wcerr << L"�������� �������� �������� ����� �� �������� - " << index;
			std::wcerr << L" �� " << edgeIndex << std::endl << L"����� ��������� ����� � ���� ��� ������� ";
			std::wcerr << L"����� ��������� ���� �����!" << RESET << std::endl;
			return false;
		}
		edges.emplace_back(start, end);
		edgeIndex++;
	}
	return true;
}

void GraphReader::initGraph(const std::wstring& path, Graph& obj) {
	unsigned int verticesCount{ 0 }, edgesCount{ 0 };
	std::vector<std::pair<unsigned int, unsigned int>> edges;

	std::wifstream file(path);
	if (!file.is_open()) {
		std::wcerr << RED << L"���� �� ������ " << path << " �� ��������!" << RESET << std::endl;
		return obj.makeAction();
	}

	std::wstring line;
	if (std::getline(file, line)) {

		std::wregex format(L"^\\d+\\s*,\\s*\\d+$");
		if (!std::regex_match(line, format)) {
			std::wcerr << RED << L"������� � �������� ����� � ����." << std::endl;
			std::wcerr << L"ϳ� ��� ����������� ����� � ���� ���� �������� �������." << std::endl;
			std::wcerr << L"������ ����� ����� ������� ������ ������ \"����� ���� �����\"." << std::endl;
			std::wcerr << L"����� ��������� ����� � ���� ��� ������� ";
			std::wcerr << L"����� ��������� ���� �����!" << RESET << std::endl;
			file.close();
			return obj.makeAction();
		}

		std::wstringstream ss(line);
		std::wstring temp;


		if (std::getline(ss, temp, L',')) {
			temp.erase(std::remove_if(temp.begin(), temp.end(), iswspace), temp.end());
			if (!GraphReader::readVerticesCount(temp, verticesCount)) {
				file.close();
				return obj.makeAction();
			}
			if (std::getline(ss, temp)) {
				if (!GraphReader::readEdgesCount(temp, edgesCount, verticesCount)) {
					file.close();
					return obj.makeAction();
				}
			}
		}
	}

	if (!readEdges(file, edges, verticesCount)) {
		file.close();
		return obj.makeAction();
	}

	if (edges.size() != edgesCount) {
		std::wcerr << RED << L"ʳ������ �������� ����� �� ������� ������� �������! " << RESET << std::endl;
		file.close();
		return obj.makeAction();
	}

	file.close();

	obj.setEdgesCount(edgesCount);
	obj.setVerticesCount(verticesCount);
	obj.setEdges(edges);

}

void GraphReader::ReadGraph(Graph obj) {
	std::wstring path;
	GraphReader::initGraph(path = inputFileNPath(), obj);

	std::wcout << GREEN << L"���� ����� �� �������������: " << path;
	std::wcout << L" ������ ������������� � �������!" << RESET << std::endl;

	std::this_thread::sleep_for(std::chrono::milliseconds(10'000));
	return obj.makeAction();
}