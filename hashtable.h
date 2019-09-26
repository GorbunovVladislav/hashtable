#include <string>
#include <fstream>
#include <iostream>
#include "list.h"

using std::string;
using std::cout;
using std::endl;
using std::to_string;
using std::ifstream;
using std::ofstream;

class Auto {

  int number;
  int year;
  string model;

public:

  Auto() {

  }

  Auto(int number, int year, string model) : 
    number(number), year(year), model(model)
  {

  }

  string getModel() {
    return model;
  }

  int getYear() {
    return year;
  }

  int getNumber() {
    return number;
  }

  bool operator ==(const Auto &a) const {
    return number == a.number;
  }
};

class Hashtable {
  int count = 0; // число элементов в таблице
  int size;
  List<Auto>* autos;

public:

  Hashtable(int size) : size(size) {
    autos = new List<Auto>[size];
  }

  int hashFunc(int number) {
    return number % size;
  }

  bool add(Auto _auto) {
    int index = hashFunc(_auto.getNumber());
    int number = _auto.getNumber();

    auto node = autos[index].find([number](Auto _auto) {
      return number == _auto.getNumber();
    });

    if (node) {
      node->setValue(_auto);
      return true;
    }

    autos[index].addHead(_auto);

    count++;

    return false;
  }

  bool remove(int number) {
    int index = hashFunc(number);

    if (autos[index].remove([number](Auto _auto) {
      return number == _auto.getNumber();
    })) {

      count--;

      return true;
    }

    return false;
  }

  bool open(const char* filepath) {
    ifstream file = ifstream(filepath);

    if (!file.is_open())
      return false;

    int number, year;
    string modelName;

    while(!file.eof()) {
      file >> number >> year;

      file.ignore(1);

      getline(file, modelName);

      add(Auto(number, year, modelName));

      // пропустить символ переноса строки
      file.ignore(1);
    }

    file.close();

    return true;
  }

  void save(const char* filepath) {
    ofstream file = ofstream(filepath);

    for(int i = 0; i < size; i++) {
      auto list = autos[i];

      for(auto node = list.getTail();
        node != nullptr;
        node = node->getNext()) {

          Auto _auto = node->getValue();
          
          file << _auto.getNumber() << " "
            << _auto.getYear()  << " "
            << _auto.getModel() << endl;
      }
    }

    file.close();
  }

  bool remove(Auto _auto) {
    int index = hashFunc(_auto.getNumber());

    return autos[index].removeByValue(_auto);
  }

  bool find(int number, Auto& result) {
    int index = hashFunc(number);

    auto node = autos[index].find([number](Auto _auto) {
      return number == _auto.getNumber();
    });

    if (node)
      result = node->getValue();

    return node;
  }

  void checkCollisions() {
    for(int i=0; i<size; i++) {
      cout << autos[i].getCount() << "  ";
    }

    cout << "\n";
  }

  void print() {

    if (count == 0) {
      cout << "=============" << endl;
      cout << "|   Пусто   |" << endl;
      cout << "=============" << endl;
      return;
    }
  
    cout << "===============================================" << endl;
    cout << "| Номер      | Год     | Модель               |" << endl;
    cout << "|            | выпуска |                      |" << endl;
    cout << "===============================================" << endl;

    for(int i = 0; i < size; i++) {
      auto list = autos[i];
      char buff[21];
      int size;

      for(auto node = list.getTail();
        node != nullptr;
        node = node->getNext()) {

        Auto _auto = node->getValue();

        size = to_string(_auto.getNumber()).copy(buff, 9, 0);
        for(int j = size; j < 11; j++)
          buff[j] = ' ';
        buff[11] = '\0';

        cout << "| " << buff;

        size = to_string(_auto.getYear()).copy(buff, 4, 0);
        for(int j = size; j < 8; j++)
          buff[j] = ' ';
        buff[8] = '\0';

        cout << "| " << buff;

        size = _auto.getModel().copy(buff, 19, 0);
        for(int j = size; j < 20; j++)
          buff[j] = ' ';

        if (_auto.getModel().length() > 20)
          buff[19] = '.';
        buff[20] = '\0';

        cout << "| " << buff << " |" << endl;
      }
    }

      cout << "===============================================" << endl;
  }

};