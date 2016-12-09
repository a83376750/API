#pragma once
#include <mutex>

namespace DataStruct
{
	template<class T>
	class List
	{
	public:
		struct Node
		{
			Node() : next(nullptr), prev(nullptr) {}

			T		data;
			Node	*next;
			Node	*prev;
		};

	public:
		List();
		~List();
		int			insert(T data, size_t index);
		void		pushfront(T data);
		void		pushback(T data);
		void		popfront();
		void		popback();
		T			front();
		T			back();
		size_t		count() {std::lock_guard<std::mutex> mtx{ _mutex };	return _size;}

		T			operator[](const size_t index);
	private:
		Node*		listHead() {std::lock_guard<std::mutex> mtx{ _mutex };	return _Head;}
		Node*		listTail() {std::lock_guard<std::mutex> mtx{ _mutex };	return _Tail;}
		Node*		listNext(const Node *Current) {std::lock_guard<std::mutex> mtx{ _mutex };	return Current->next; }
		Node*		listPrev(const Node *Current) {std::lock_guard<std::mutex> mtx{ _mutex };	return Current->prev; }
		Node*		nodeCreate() 
		{
			try 
			{ 
				Node *n = new Node(); 
				return n;
			}
			catch (const bad_alloc &e)
			{
				std::cout << e.what() << std::endl;
				return nodeCreate();
			}
		}
	private:
		std::mutex	_mutex;
		Node		*_Tail;
		Node		*_Head;
		size_t		_size;
	};

	template<class T>
	void DataStruct::List<T>::popfront()
	{
		if (_Head != nullptr)
		{
			Node *n = _Head->next;
			delete _Head;
			n->prev = nullptr;
			_Head = n;
			_size--;
		}
	}

	template<class T>
	void DataStruct::List<T>::pushfront(T data)
	{
		std::lock_guard<std::mutex> mtx{ _mutex };
		if (_Head == _Tail)
		{
			_Head->data = data;
			_Tail = nullptr;
			return;
		}
		Node *n = nodeCreate();
		n->data = data;
		n->next = _Head;
		_Head->prev = n;
		_Head = n;
		_size++;
	}

	template<class T>
	T DataStruct::List<T>::front()
	{
		try
		{
			if (_size < 1)
				throw _size;
			if (_Head == nullptr)
				throw nullptr;
			return _Head->data;
		}
		catch (size_t &t)
		{
			std::cerr << "没有元素:" << t << std::endl;
			exit(-1);
		}
	}

	template<class T>
	void DataStruct::List<T>::popback()
	{
		if (_Tail != nullptr)
		{
			Node *t = _Tail->prev;
			_Tail->prev->next = nullptr;
			delete _Tail;
			_Tail = t;
			_size--;
		}
	}

	template<class T>
	int DataStruct::List<T>::insert(T data, size_t index)
	{
		try
		{
			Node *n = _Head;
			for (int i = 0; i < index; ++i)
			{
				n = listNext(n);
			}
			if (n == nullptr)
				throw std::exception("空指针");
			
			Node *newNode = nodeCreate();
			newNode->data = data;

			if (n == _Head)
			{
				newNode->next = n;
				n->prev = newNode;
				_Head = newNode;
			}
			else
			{
				Node *p = n->prev;
				p->next = newNode;
				newNode->prev = p;
				newNode->next = n;
				n->prev = newNode;
			}

			//if (bf == nullptr)
			//{
			//	bf->next = newNode;
			//	newNode->prev = bf;
			//	newNode->next = after;
			//}
			//else
			//{
				//bf->next = newNode;
				//newNode->prev = bf->next;
				//newNode->next = n;
				//n->prev = newNode;
			//}
			_size++;
			return 0;
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
			return -1;
		}
		
	}

	template<class T>
	T DataStruct::List<T>::back()
	{
		size_t index = _size - 1;
		try
		{
			if (index < 0)
				throw _size;
			if (_Tail == nullptr)
				throw nullptr;
			T data = _Tail->data;
			Node *last = listPrev(_Tail);
			if (last == nullptr)
				throw nullptr;
			return data;
		}
		catch (size_t &t)
		{
			std::cerr << "没有数据, 当前链表大小:" << t << std::endl;
			exit(-1);
		}
		catch (void *e)
		{
			std::cerr << "最后一个元素的前一个数据丢失" << std::endl;
			exit(-1);
		}
	}

	template<class T>
	T DataStruct::List<T>::operator[](const size_t index)
	{
		try
		{
			if (_size < index + 1)
			{
				throw index;
			}
			Node *n = _Head;
			for (int i = 0; i < index; ++i)
			{
				n = listNext(n);
				if (n == nullptr)
					throw i;
			}
			return n->data;
		}
		catch (size_t &t)
		{
			std::cerr << "越界,索引为:" << index << std::endl;
			exit(-1);
		}
	}

	template<class T>
	DataStruct::List<T>::List()
	{
		_Head = nodeCreate();
		_Tail = _Head;
		_size = 1;
	}

	template<class T>
	DataStruct::List<T>::~List()
	{
		if (_Head == _Tail)
		{
			delete _Head;
			_Head = nullptr;
			_Tail = nullptr;
		}
		else
		{
			Node *cur = listNext(_Head);
			if (cur != nullptr)
			{
				do
				{
					delete _Head;
					_Head = cur;
					cur = listNext(_Head);
				} while (cur != nullptr);
			}
			delete _Head;
		}
	}

	template<class T>
	void DataStruct::List<T>::pushback(T data)
	{
		std::lock_guard<std::mutex> mtx{ _mutex };
		if (_Head == _Tail)
		{
			_Head->data = data;
			_Tail = nullptr;
			return;
		}
		
		if (_Tail == nullptr)
		{
			_Tail = nodeCreate();
			_Head->next = _Tail;
			_Tail->prev = _Head;
			_Tail->data = data;
			_Tail->next = nullptr;
		}
		else
		{
			_Tail->next = nodeCreate();
			_Tail->next->data = data;
			_Tail->next->prev = _Tail;
			_Tail = _Tail->next;
		}
		_size++;
		return;
	}

}
