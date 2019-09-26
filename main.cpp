// Example program
#include <string>
#include <iostream>
#include "hashtable.h"
#include <fstream>
#include <windows.h>

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::ifstream;
using std::ofstream;

Hashtable database(10);

void openFile() {
  database = Hashtable(10);

  bool found = database.open("database.txt");
}

void saveFile() {
  database.save("database.txt");
}

void cmdAdd() {
  int number, year;
  string modelName;

  cout << "������� ����� ����" << endl;
  cout << "> ";
  cin >> number;

  cout << "������� ��� �������" << endl;
  cout << "> ";
  cin >> year;

  cout << "������� �������� ������" << endl;
  cout << "> ";
  cin.ignore(1024, '\n');
  getline(cin, modelName);

  if (database.add(Auto(number, year, modelName)))
    cout << "���������� � ������� " << number << " ��� �������" << endl;
  else
    cout << "���������� �������� � ������" << endl;

  saveFile();
}

void cmdRemove() {
  int number;

  cout << "������� ����� ����, ������� ������ �������" << endl;
  cout << "> ";
  cin >> number;

  bool removed = database.remove(number);

  if (removed)
    cout << "���������� ��� ������� " << number << " ������" << endl;
  else
    cout << "���������� ��� ������� " << number << " �� ������" << endl;

  saveFile();
}

void cmdFind() {
  int number;

  cin >> number;

  cout << "������� ����� ����������, ������� �� �����" << endl;
  cout << "> ";
  cin >> number;

  Auto _auto;
  bool found = database.find(number, _auto);

  if (found)
    cout << "�������: "
      << "�" << _auto.getNumber()
      << " ��� " << _auto.getYear()
      << " " << _auto.getModel();
  else
    cout << "�� ������� ���������� � ����� �������";
}

void cmdPrint() {
  database.print();
}

void cmdHelp() {
  cout << "������ ������:" << endl;
  cout << ">> 1 - �������� ����������/���������� ���������� �� ������" << endl;
  cout << ">> 2 - ������� ���������� � �������� �������" << endl;
  cout << ">> 3 - ����� �� ������" << endl;
  cout << ">> 4 - �����" << endl;
}

void cmdMenu() {
  int cmd;

  cmdHelp();

  do {
    cout << ">> ";
    cin >> cmd;

    switch(cmd) {
      case 1:
        cmdAdd();
        break;
      case 2:
        cmdRemove();
        break;
      case 3:
        cmdFind();
        break;
      case 4:
        cmdPrint();
        break;
      case 5:
        cmdHelp();
        break;
    }
  } while (cmd != 0);
}

int main()
{
  SetConsoleCP(1251);// ��������� ������� �������� win-cp 1251 � ����� �����
  SetConsoleOutputCP(1251); // ��������� ������� �������� win-cp 1251 � ����� ������

  openFile();

  cmdMenu();

  return 0;
}
