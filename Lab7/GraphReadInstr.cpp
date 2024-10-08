#include"GraphReadInstr.h"
#include"PathUtil.h"
#include<iostream>

#include<locale>
#include<sstream>

// ANSI-escape codes ��� ����������� ������ (�������� �� �������� ���� ������)
#define RESET   L"\033[0m"
#define BOLD    L"\033[1m"
#define RED     L"\033[31m"
#define GREEN   L"\033[32m"
#define YELLOW  L"\033[33m"
#define BLUE    L"\033[34m"

std::wstring inputFileNPath() {
    std::locale::global(std::locale("uk_UA.UTF-8"));

    std::wstring path;
    while (true) {
        std::wcout << BOLD << YELLOW << L"������ ���� ��������� ����� �����, �� ������ ���� � �����������: " << RESET;
        std::getline(std::wcin, path);
        if (!FileValidator::existFile(path)) {
            std::wcout << RED << L"������� ����, ����� �� ������ ���� ���� �� ����� ������. ��������� �� ���.\n" << RESET;
            continue;
        }
        break;
    }
    return path;
}
