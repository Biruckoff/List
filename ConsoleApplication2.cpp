#include <iostream>
#include <fstream>
using namespace std;


struct List {

	List* next;
	List* prev;
	int value;

};
void push(List*& A, int val) {
	//push добавляет элемент в начало списка
	if (A) {
		List* L = new List();
		L->next = A;
		L->prev = 0;
		A->prev = L;
		L->value = val;
		A = L;

	}
	else {
		List* L = new List();
		L->value = val;
		L->prev = 0;
		L->next = 0;
		A = L;

	}
}

void pop(List*& A, ofstream &ofs) {
	//pop выводит и удаляет первый элемент списка
	ofs << A->value << " ";

	if (A->next) {
		A = A->next;
		delete A->prev;
	}
	else {
		delete A;
		A = 0;

	}


}

void sort(List*& A) {
	/*В сортировке рассмотрены  три сценария:
	1)Сравнивается первый и следующий элемент
	2)Сравниваются два рядом стоящих элемента
	3)Сравнивается последний и предпоследний элемент
	*/
	bool flag = true;
	List* head = A;

	while (flag) {

		flag = false;
		A = head;

		while (A->next) {
			if (A->value > A->next->value) {
				if (!A->prev) {
					A->next->prev = 0;
					A->prev = A->next;
					head = A->next;
				}
				else {
					A->next->prev = A->prev;
					A->prev->next = A->next;
					A->prev = A->next;
				}
				if (!A->next->next) {
					A->next->next = A;
					A->next = 0;
					A = A->prev;

				}
				else {
					A->next->next->prev = A;
					List* B = A->next->next;
					A->next->next = A;
					A->next = B;

				}
				flag = true;
			}
			A = A->next;
		}
	}
	A = head;
}
int getFromFile(List* &list, ifstream &ifs) {
	//Получаем информацию из файла
	int y;
	int n = 0;
	while (ifs >> y) {

		n++;
		push(list, y);
	}

	return n;

}

void outInFile(List* &list, ofstream &ofs) {
	//Выводим в файл
	while (list) {
		pop(list, ofs);
	}

}

int main() {
	List* l = new List;
	int chooseSort;
	l = 0;
	ifstream ifs("input.txt");
	ifs >> chooseSort; //Определяем способ сортировки
	int n = getFromFile(l, ifs); //Получаем данные из файла
	ifs.close();
	ofstream ofs("output.txt");
	if (chooseSort) {
		sort(l); //Сортируем пузырьком
	}
	else {
		//Возможность добавить ещё одну сортировку
	}
	ofs << n << " ";
	outInFile(l, ofs); //Вывод в файл
	ofs.close();
	delete l;
	return 0;
}
