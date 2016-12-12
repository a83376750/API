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
		size_t		count() {std::lock_guard<std::mutex> mtx{ mutex_ };	return size_;}
		void		clear();
		T			operator[](const size_t index);
	private:
		Node*		listHead() {std::lock_guard<std::mutex> mtx{ mutex_ };	return head_;}
		Node*		listTail() {std::lock_guard<std::mutex> mtx{ mutex_ };	return tail_;}
		Node*		listNext(const Node *Current) {std::lock_guard<std::mutex> mtx{ mutex_ };	return Current->next; }
		Node*		listPrev(const Node *Current) {std::lock_guard<std::mutex> mtx{ mutex_ };	return Current->prev; }
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
		std::mutex	mutex_;
		Node		*tail_;
		Node		*head_;
		size_t		size_;
	};

	template<class T>
	void DataStruct::List<T>::clear()
	{
		if (head_ != nullptr)
		{
			Node *n;
			for (int i = 0; i < count(); ++i)
			{
				n = listNext(head_);
				delete head_;
				head_ = n;
			}
		}
		tail_ = nullptr;
		size_ = 0;
	}

	template<class T>
	void DataStruct::List<T>::popfront()
	{
		if (head_ != nullptr)
		{
			Node *n = head_->next;
			delete head_;
			n->prev = nullptr;
			head_ = n;
			size_--;
		}
	}

	template<class T>
	void DataStruct::List<T>::pushfront(T data)
	{
		std::lock_guard<std::mutex> mtx{ mutex_ };
		if (head_ == nullptr)
		{
			head_ = nodeCreate();
			head_->data = data;
			tail_ = head_;
			return;
		}
		Node *n = nodeCreate();
		n->data = data;
		n->next = head_;
		head_->prev = n;
		head_ = n;
		size_++;
	}

	template<class T>
	T DataStruct::List<T>::front()
	{
		try
		{
			if (size_ < 1)
				throw size_;
			if (head_ == nullptr)
				throw nullptr;
			return head_->data;
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
		if (tail_ != nullptr)
		{
			Node *t = tail_->prev;
			tail_->prev->next = nullptr;
			delete tail_;
			tail_ = t;
			size_--;
		}
	}

	template<class T>
	int DataStruct::List<T>::insert(T data, size_t index)
	{
		try
		{
			Node *n = head_;
			for (int i = 0; i < index; ++i)
			{
				n = listNext(n);
			}
			if (n == nullptr)
				throw std::exception("空指针");
			
			Node *newNode = nodeCreate();
			newNode->data = data;

			if (n == head_)
			{
				newNode->next = n;
				n->prev = newNode;
				head_ = newNode;
			}
			else
			{
				Node *p = n->prev;
				p->next = newNode;
				newNode->prev = p;
				newNode->next = n;
				n->prev = newNode;
			}
			size_++;
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
		size_t index = size_ - 1;
		try
		{
			if (index < 0)
				throw size_;
			if (tail_ == nullptr)
				throw nullptr;
			T data = tail_->data;
			Node *last = listPrev(tail_);
			if (last == nullptr)
				throw nullptr;
			return data;
		}
		catch (size_t &t)
		{
			std::cerr << "没有数据, 当前链表大小:" << t << std::endl;
			exit(-1);
		}
		catch (...)
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
			if (size_ < index + 1)
			{
				throw index;
			}
			Node *n = head_;
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
			std::cerr << "越界,索引为:" << t << std::endl;
			exit(-1);
		}
	}

	template<class T>
	DataStruct::List<T>::List():head_(nullptr), tail_(nullptr), size_(0)
	{

	}

	template<class T>
	DataStruct::List<T>::~List()
	{
		if (head_ == tail_)
		{
			delete head_;
			head_ = nullptr;
			tail_ = nullptr;
		}
		else
		{
			Node *cur = listNext(head_);
			if (cur != nullptr)
			{
				do
				{
					delete head_;
					head_ = cur;
					cur = listNext(head_);
				} while (cur != nullptr);
			}
			delete head_;
		}
	}

	template<class T>
	void DataStruct::List<T>::pushback(T data)
	{
		std::lock_guard<std::mutex> mtx{ mutex_ };
		if (head_ == nullptr)
		{
			head_ = nodeCreate();
			head_->data = data;
			tail_ = head_;
		}
		else
		{
			if (tail_ == nullptr)
			{
				tail_ = nodeCreate();
				head_->next = tail_;
				tail_->prev = head_;
				tail_->data = data;
				tail_->next = nullptr;
			}
			else
			{
				tail_->next = nodeCreate();
				tail_->next->data = data;
				tail_->next->prev = tail_;
				tail_ = tail_->next;
			}
		}
		size_++;
		return;
	}

}
