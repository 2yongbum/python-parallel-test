// reading an entire binary file
#include <Python.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>         // std::thread
#include <vector>
using namespace std;

int read_file(const char* fname) {
  streampos size;
  char * memblock;

  ifstream file (fname, ios::in|ios::binary|ios::ate);
  if (file.is_open())
  {
    uint32_t length = 0;
    size = file.tellg();
    memblock = new char [size];
    file.seekg (0, ios::beg);
    file.read (memblock, size);
    file.close();
    
    for (int i = 0; i < size; i++) {
      length++;
    }

    cout << "the entire file content is in memory size: " << size << " count: " << length << endl;

    delete[] memblock;
  }
  else cout << "Unable to open file\n";
  return 0;
}

int serial_read() 
{
  auto start = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < 4; i++) {
    char filename[80];
    sprintf(filename, "%d.bmp", i);
    read_file(filename);
  }
  auto finish = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> duration = finish-start;
  std::cout << "serial duration:" << duration.count() << "s\n";
  return 0;
}

int thread_read() {
  std::vector<std::thread> threads;
  auto start = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < 4; i++) {
    char filename[80];
    sprintf(filename, "%d.bmp", i);
    threads.emplace_back(std::thread{read_file, filename});
  }

  // synchronize threads:
  for (auto& th : threads) {
    th.join();
  }

  auto finish = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> duration = finish-start;
  std::cout << "thread duration:" << duration.count() << "s\n";

  std::cout << "foo and bar completed.\n";

  return 0;
}

int main() {
  serial_read();
  thread_read();
  return 0;
}
PyObject* c_thread(PyObject*, PyObject* args) {
  thread_read();
  Py_RETURN_NONE;;
}

static PyMethodDef c_reader_methods[] = {
	{ "c_thread", (PyCFunction)c_thread, METH_VARARGS, nullptr },
	{ nullptr, nullptr, 0, nullptr }
};

static PyModuleDef c_reader_module = {
	PyModuleDef_HEAD_INIT,
	"c_reader",                        // Module name to use with Python import statements
	"c_reader robot controller",  // Module description
	0,
	c_reader_methods                   // Structure that defines the methods of the module
};

PyMODINIT_FUNC PyInit_c_reader() {
	return PyModule_Create(&c_reader_module);
}