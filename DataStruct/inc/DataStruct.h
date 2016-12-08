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

		int			pushback(T data);
		size_t		count()const {std::lock_guard<std::mutex> mtx{ _mutex };	return _size;}
		T			operator[](const size_t index);
	private:
		Node*		listHead() {std::lock_guard<std::mutex> mtx{ _mutex };	return _Head;}
		Node*		listTail() {std::lock_guard<std::mutex> mtx{ _mutex };	return _Tail;}
		Node*		listNext(const Node *Current) {std::lock_guard<std::mutex> mtx{ _mutex };	return Current->next; }
		Node*		listPrev(const Node *Current) {std::lock_guard<std::mutex> mtx{ _mutex };	return Current->prev; }
		Node*		NodeCreate() 
		{
			try 
			{ 
				Node *n = new Node(); 
				return n;
			}
			catch (const bad_alloc &e)
			{
				std::cout << e.what() << std::endl;
				return NodeCreate();
			}
		}
	private:
		std::mutex	_mutex;
		Node		*_Tail;
		Node		*_Head;
		size_t		_size;
	};

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
		_Head = NodeCreate();
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
	int DataStruct::List<T>::pushback(T data)
	{
		std::lock_guard<std::mutex> mtx{ _mutex };
		if (_Head == _Tail)
		{
			_Head->data = data;
			_Tail = nullptr;
			return 0;
		}
		
		if (_Tail == nullptr)
		{
			_Tail = NodeCreate();
			_Head->next = _Tail;
			_Tail->prev = _Head;
			_Tail->data = data;
			_Tail->next = nullptr;
		}
		else
		{
			_Tail->next = NodeCreate();
			_Tail->next->data = data;
			_Tail->next->prev = _Tail;
			_Tail = _Tail->next;
		}
		_size++;
		return 0;
	}

}
