#include <iostream>
using namespace std;

ostream& operator<<(ostream& o, string& s)
{
	o << s.c_str();
	return o;
}

istream& operator>>(istream& i, string& s)
{
	char buf[256];
	i >> buf;
	string tmp(buf);
	s = tmp;

	return i;
}


template<typename T>
class AbstractList
{
protected:
	T _default;
public:
	virtual void sort(bool(*f) (T* first, T* second)) = 0;
	virtual T get(int index) = 0;
	virtual void set(int index, T data) = 0;
	virtual void insert(int index, T data) = 0;
	virtual T remove(int index) = 0;
	virtual int len() = 0;

	void push(T data)
	{
		insert(0, data);
	}
	virtual T pop()
	{
		if (empty())
			return _default;
		else
			return remove(0);
	}

	virtual bool empty()
	{
		return len() == 0;
	}

	virtual ostream& print(ostream& o)
	{
		for (int i = 0; i < len(); i++)
		{
			o << get(i) << endl;
		}
		return o;
	}

	virtual istream& read(istream& in)
	{
		int count;
		in >> count;
		for (int i = 0; i < count; i++)
		{
			T tmp;
			in >> tmp;
			insert(len(), tmp);
		}
		return in;
	}

};

template<typename T>
class List : public AbstractList < T >
{
	T data;
	List* next;
	T _default;
public:

	List(T data, T def)
	{
		this->data = data;
		_default = def;
		next = NULL;
	}

	List(T def)
	{
		_default = def;
		next = NULL;
	}

	List(const List& a)
	{
		this->data = a.data;
		this->next = a.next;
		this->_default = a._default;
	}

	~List()
	{
		next = NULL;
	}

	List& operator= (List& a)
	{
		data = a.data;
		next = a.next;
		_default = a._default;
		return List(*this);
	}

	int len()
	{
		int i = 0;
		List* l = this;
		while (l->next != NULL)
		{
			l = l->next;
			i++;
		}
		return i;
	}

	void set(int index, T data)
	{
		if (index < len()){
			List* tmp = this;
			int i = 0;
			while (i != index && tmp->next != NULL)
			{
				tmp = tmp->next;
				i++;
			}
			tmp->data = data;

		}
	}

	T get(int index)
	{
		if (index >= len()){ return _default; }
		else{
			List* tmp = this;
			int i = 0;
			while (i != index && tmp->next != NULL)
			{
				tmp = tmp->next;
				i++;
			}
			return tmp->next->data;
		}
	}

	void insert(int index, T data)
	{
		List* n = new List(data, this->_default);
		List* tmp1 = this;

		int i = 0;
		while (i != index && tmp1->next != NULL)
		{
			tmp1 = tmp1->next;
			i++;
		}
		n->next = tmp1->next;
		tmp1->next = n;
	}

	T remove(int index)
	{
		List* tmp = this;
		if (tmp->next == NULL)
		{
			T d = tmp->data;
			tmp = NULL;
			return d;
		}
		else{
			int i = 0;
			List* prev = tmp;
			while (i != index && tmp->next != NULL)
			{
				prev = tmp;
				tmp = tmp->next;
				i++;
			}
			List* del = tmp;
			prev->next = tmp->next;
			return del->next->data;
		}
	}

	bool comp(T* first, T* second)
	{
		if (&first < &second) { return true; }
		else { return false; }
	}

	void sort(bool(*f) (T* first, T* second))
	{
		List* tmp1; List* tmp2;
		for (tmp1 = this; tmp1->next != NULL; tmp1 = tmp1->next)
		{
			for (tmp2 = this; tmp2->next != NULL; tmp2 = tmp2->next)
			{
				if (comp(&(tmp2->data), &(tmp2->next->data)))
				{
					List* tmp = tmp2;
					tmp2 = tmp2->next;
					tmp2->next = tmp;
				}
			}
		}
	}
};

AbstractList<string>* get_init()
{
	List<string>* a = new List<string>("Error");
	return a;
}
/*
int main()
{
	AbstractList<string>* a = get_init();
	a->insert(0, "Data");
	a->push("Hello");
	cout << a->pop();
	a->print(cout);
	system("pause");
	return 0;
}
*/