#pragma once

#include <iostream>
#include <random>
#include <stdexcept>
#include <type_traits>

using namespace std;

template <typename T>
class LinkedList {
	struct Node {
		T _data;
		Node* _next;

		Node() = default;
		Node(const T& data) : _data(data), _next(nullptr) {}
	};

	Node* _head;
	Node* _tail;
	size_t _size;
public:
	//Конструктор по умолчанию.
	LinkedList() : _head(nullptr), _tail(nullptr), _size(0) {};

	//Конструктор копирования.
	LinkedList(const LinkedList& other)
	{
		_head = _tail = nullptr;
		_size = 0;

		Node* curr = other._head;
		while (curr != other._tail)
		{
			push_tail(curr->_data);
			curr = curr->_next;
		}
	}

	//Конструктор, заполняющий список случайными значениями согласно заданию.
	LinkedList(size_t n, const T& lower_value, const T& upper_value) : LinkedList()
	{
		random_device rd;
		mt19937 gen(rd());
		if constexpr (is_integral<T>::value)
		{
			uniform_int_distribution<T> dist(lower_value, upper_value);
			for (size_t i = 0; i < n; i++) {
				push_tail(dist(gen));
			}
		}
		if constexpr (is_floating_point<T>::value)
		{
			uniform_real_distribution<T> dist(lower_value, upper_value);
			for (size_t i = 0; i < n; i++) {
				push_tail(dist(gen));
			}
		}
	}

	size_t size() const
	{
		return _size;
	}

	//Операция присваивания.
	LinkedList& operator=(const LinkedList& other)
	{
		if (this == &other)
		{
			return *this;
		}

		while (_head)
		{
			pop_tail();
		}

		(*this)(other);

		return *this;
	}

	//Добавление элемента в конец списка.
	void push_tail(const T& data)
	{
		Node* new_node = new Node(data);

		if (!_head)
		{
			_head = _tail = new_node;
		}
		else
		{
			_tail->_next = new_node;
			_tail = new_node;
		}
		++_size;
		_tail->_next = _head;
	}

	//Добавление другого списка LinkedList в конец списка.
	void push_tail(const LinkedList& other)
	{
		if (!other._head)
		{
			return;
		}

		else
		{
			Node* curr = other._head;
			for (int i = 0; i < other.size(); ++i)
			{
				push_tail(curr->_data);
				curr = curr->_next;
			}
		}
	}

	//Добавление элемента в начало списка.
	void push_head(const T& data)
	{
		Node* new_node = new Node(data);

		if (!_head) {
			_head = _tail = new_node;
		}
		else {
			new_node->_next = _head;
			_head = new_node;
		}
		++_size;
		_tail->_next = _head;
	}

	//Добавление списка LinkedList в начало списка.
	void push_head(const LinkedList& other)
	{
		if (!other._head)
		{
			return;
		}

		else
		{
			LinkedList* tmp = new LinkedList();

			Node* tmp_cur = other._head;
			for (int i = 0; i < other.size(); ++i)
			{
				tmp->push_head(tmp_cur->_data);
				tmp_cur = tmp_cur->_next;
			}

			Node* curr = tmp->_head;
			for (int i = 0; i < tmp->size(); ++i)
			{
				push_head(curr->_data);
				curr = curr->_next;
			}

		/*	Node* curr = other._head;
			for (int i = 0; i < other.size(); ++i)
			{
				push_head(curr->_data);
				curr = curr->_next;
			}*/
		}
	}

	//Удаление элемента из начала списка.
	void pop_head()
	{
		if (!_head)
		{
			return;
		}

		if (_head == _tail)
		{
			delete _head;
			_head = _tail = nullptr;
		}
		else
		{
			Node* temp = _head;
			_head = _head->_next;
			_tail->_next = _head;
			delete temp;
		}

		--_size;
	}


	//Удаление элемента из конца списка.
	void pop_tail()
	{
		if (!_head)
		{
			return;
		}

		if (_head == _tail)
		{
			delete _head;
			_head = _tail = nullptr;
		}
		else
		{
			Node* curr = _head;
			while (curr->_next != _tail)
			{
				curr = curr->_next;
			}

			delete _tail;
			_tail = curr;
			_tail->_next = _head;
		}

		--_size;
	}

	//Удаление всех элементов Node с информационным полем, равным переданному.
	void delete_node(const T& data)
	{
		if (!_head)
		{
			return;
		}

		if (_head == _tail && _head->_data == data)
		{
			delete _head;
			_head = _tail = nullptr;
			_size = 0;
			return;
		}

		while (_head->_data == data)
		{
			Node* temp = _head;
			_head = _head->_next;
			_tail->_next = _head;
			delete temp;
			--_size;
			if (!_head)
			{
				break;
			}
		}

		while (_tail->_data == data)
		{

			Node* curr = _head;
			while (curr->_next != _tail)
			{
				curr = curr->_next;
			}

			delete _tail;
			--_size;
			if (!_head)
			{
				break;
			}

			_tail = curr;
			_tail->_next = _head;
		}

		Node* curr = _head;
		while (curr->_next != _tail)
		{
			if (curr->_next->_data == data)
			{
				Node* temp = curr->_next;
				curr->_next = temp->_next;
				delete temp;
				--_size;
			}
			else
			{
				curr = curr->_next;
			}
		}
	}

	//Операция доступа по индексу.
	T& operator[](size_t idx)
	{
		if (idx >= _size)
		{
			throw out_of_range("Index out of list");
		}

		Node* curr = _head;
		for (size_t i = 0; i < idx; i++)
		{
			curr = curr->_next;
		}

		return curr->_data;
	}

	//Операция доступа по индексу.
	T& operator[](size_t idx) const
	{
		if (idx >= size)
		{
			throw out_of_range("Index out of list");
		}

		Node* curr = _head;
		for (size_t i = 0; i < idx; i++)
		{
			curr = curr->_next;
		}

		return curr->_data;
	}

	//Вспомогательная функция поиска по значению.
	Node* find_term(int num) const {
		if (!_head) return nullptr; 
		Node* current = _head;
		do {
			if (current->_data == num) {
				return current; 
			}
			current = current->_next;
		} while (current != _head);
		return nullptr;
	}
	
	//Деструктор
	~LinkedList()
	{
		while (_head)
		{
			pop_tail();
		}
	}
};