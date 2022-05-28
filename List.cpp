#include <iostream>
#include <fstream>
using namespace std;


struct List {

	List* next;
	List* prev;
	int value;

};
void push(List*& A, int val) {
	//push ��������� ������� � ������ ������
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
	//pop ������� � ������� ������ ������� ������
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
	/*� ���������� �����������  ��� ��������:
	1)������������ ������ � ��������� �������
	2)������������ ��� ����� ������� ��������
	3)������������ ��������� � ������������� �������
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
	//�������� ���������� �� �����
	int y;
	int n = 0;
	while (ifs >> y) {

		n++;
		push(list, y);
	}

	return n;

}

void outInFile(List* &list, ofstream &ofs) {
	//������� � ����
	while (list) {
		pop(list, ofs);
	}

}

int main() {
	List* l = new List;
	int chooseSort;
	l = 0;
	ifstream ifs("input.txt");
	ifs >> chooseSort; //���������� ������ ����������
	int n = getFromFile(l, ifs); //�������� ������ �� �����
	ifs.close();
	ofstream ofs("output.txt");
	if (chooseSort) {
		sort(l); //��������� ���������
	}
	else {
		//����������� �������� ��� ���� ����������
	}
	ofs << n << " ";
	outInFile(l, ofs); //����� � ����
	ofs.close();
	delete l;
	return 0;
}
