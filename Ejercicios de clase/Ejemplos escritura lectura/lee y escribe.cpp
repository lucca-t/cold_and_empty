
#include <fstream>
#include <iostream>
using namespace std;

int main() {
  // writing on a text file
  ofstream archivo_salida("clase proga.txt");
  if (archivo_salida.is_open()) {
    archivo_salida << "This is a line.\n";
    archivo_salida << "This is another line.\n";
    archivo_salida.close();
  } else {
    cout << "Unable to open file";
  }

  // reading from on a text file
  string line;
  ifstream archivo_entrada("lee y escribe.cpp");
  if (archivo_entrada.is_open()) {
    while (getline(archivo_entrada, line)) {
      cout << line << '\n';
    }
    archivo_entrada.close();
  } else {
    cout << "Unable to open file\n";
  }

  return 0;
}
