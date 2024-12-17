//Вариант списка - 3 (Циклический односвязанный список); Вариант задания - (5;1).

#include <iostream>
#include "LinearList.cpp"

using namespace std;

void find_primes(int N, LinkedList<int> list) {
	if (N < 2) // Не существует простых чисел
	{
		cout << "No prime numbers ";
		return;
	}
	cout << "Prime numbers: ";
	for (int num = 2; num <= N; num++) {
		bool isPrime = true;
		for (int i = 2; i * i <= num; i++) {
			if (num % i == 0) {
				isPrime = false;
				break;
			}
		}
		if (isPrime) {
			if (list.find_term(num))
				cout << num << " "; // Выводим простое число
		}
	}
	return;
}

int main()
{
	LinkedList<int> l1(7, 3, 15);
	LinkedList<int> l2(4, 1, 9);
	l1[0] = 52;
	cout << "list: ";
	for (size_t i = 0; i < l1.size(); ++i)
	{
		cout << l1[i] << " ";
	}
	cout << endl;
	for (size_t i = 0; i < l2.size(); ++i)
	{
		cout << l2[i] << " ";
	}
	cout << endl;

	l1.push_head(l2);
	cout << "list l1 after push_head: ";
	for (size_t i = 0; i < l1.size(); ++i)
	{
		cout << l1[i] << " ";
	}
	cout << endl;

	find_primes(100, l1);

}