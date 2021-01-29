#include <clocale>
#include "List.h"
#include "CircularList.h"


void listTest();
void CircularListTest();


int main() {
	
	// listTest();
	CircularListTest();

	return 0;
}


void CircularListTest()
{
	// Задача Иосифа Флавия
	using namespace std;
	setlocale(LC_ALL, "ru");

	size_t people = 0, step = 0;
	while (people < 2)
	{
		cout << "Людей не может быть меньше 2!\n";
		cin >> people;
	}
	while (step < 2)
	{
		cout << "Шаг не может быть меньше 2!\n";
		cin >> step;
	}

	CircularList<int> circle;
	for (size_t i = people; i > 0; i--)
		circle.insertFront(i);

	cout << "Люди: " << circle << endl;

	Node<int>* temp = circle.getStart();
	size_t cnt = 1;
	while (circle.size() != 1)
	{
		while (++cnt != step)
			temp = temp->getNext();
		circle.deleteAfter(temp);
		temp = temp->getNext();
		cnt = 1;
	}
	cout << "Выживший: " << temp->getData() << endl << endl;
}


void listTest()
{
	using namespace std;
	setlocale(LC_ALL, "ru");

	List<int> list;
	for (int i = 1; i <= 5; i++)
		list.insertBack(i);

	cout << "Список после вставки 5 натуральных чисел:\n"
		<< list << endl << endl;

	list.deleteBack();
	cout << "Список после удаления последнего элемента:\n"
		<< list << endl << endl;

	Node<int>* temp = list.getStart()->getNext();
	list.insertAfter(temp, 10);
	cout << "Список после вставки элемента после 2 элемента:\n"
		<< list << endl << endl;

	temp = temp->getNext();
	list.deleteAfter(temp);
	cout << "Список после удаления элемента после последнего:\n"
		<< list << endl << endl;
}
