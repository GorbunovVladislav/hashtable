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

  cout << "Введите номер авто" << endl;
  cout << "> ";
  cin >> number;

  cout << "Введите год выпуска" << endl;
  cout << "> ";
  cin >> year;

  cout << "Введите название модели" << endl;
  cout << "> ";
  cin.ignore(1024, '\n');
  getline(cin, modelName);

  if (database.add(Auto(number, year, modelName)))
    cout << "Автомобиль с номером " << number << " был изменен" << endl;
  else
    cout << "Автомобиль добавлен в список" << endl;

  saveFile();
}

void cmdRemove() {
  int number;

  cout << "Введите номер авто, который хотите удалить" << endl;
  cout << "> ";
  cin >> number;

  bool removed = database.remove(number);

  if (removed)
    cout << "Автомобиль под номером " << number << " удален" << endl;
  else
    cout << "Автомобиль под номером " << number << " не найден" << endl;

  saveFile();
}

void cmdFind() {
  int number;

  cin >> number;

  cout << "Введите номер автомобиля, который вы ищете" << endl;
  cout << "> ";
  cin >> number;

  Auto _auto;
  bool found = database.find(number, _auto);

  if (found)
    cout << "Найдено: "
      << "№" << _auto.getNumber()
      << " год " << _auto.getYear()
      << " " << _auto.getModel();
  else
    cout << "Не найдено автомобиля с таким номером";
}

void cmdPrint() {
  database.print();
}

void cmdHelp() {
  cout << "Список команд:" << endl;
  cout << ">> 1 - добавить автомобиль/переписать автомобиль по номеру" << endl;
  cout << ">> 2 - удалить автомобиль с заданным номером" << endl;
  cout << ">> 3 - поиск по номеру" << endl;
  cout << ">> 4 - вывод" << endl;
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
  SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
  SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода

  openFile();

  cmdMenu();

  return 0;
}
