#include <iostream>
#include <string>
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
public :
	virtual void sort(bool (*f) (T* first, T* second)) = 0;
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
		for (int i = 0 ; i < count ; i ++)
		{
			T tmp;
			in >> tmp;
			insert(len(), tmp);
		}
		return in;
	}

};

///////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
class list : public AbstractList<T>
{
	T data;
	list* next;

protected:
	T _default;

public:

	list()
	{
		//data = NULL;
		next = NULL;
	}

	list (T sent, T d)
	{
		_default = d;
		data = sent;
		next = NULL;
	}

	list (T d)
	{
		_default = d;
		next = NULL;
	}

	list (const list& a)
	{
		data = a.data;
		_default = a._default;
		next = a.next;
	}

	list

	~list()
	{
		delete this;
	}

	T get(int index)
	{
		int i = 0;
		list* tmp = this;
		while (i != index && tmp->next != NULL)
		{
			cout <<"in get" << endl;
			tmp = tmp->next;
			i++;
		}
		return tmp->data;
	}

	void set(int index, T data)
	{
		if(index < len())
		{
			cout << "here1" << endl;
			int i = 0;
			while (i != index && next != NULL)
			{
				cout << "here3" << endl;
				next = next->next;
				i++;
			}
			this->data = data;
		}
	}

	void insert ()
	{

	}

	/*
	void insert(int index, T data)
	{
		if(index == 0)
		{
			list* tmp = this;
			list* pn = new list(data, tmp->_default);
			pn = this;
		}else{
			if (index < len())
			{
				cout << "here2" << endl;
				int i = 0;
				list* eqv = this;
				while (i != index)
				{
					eqv = eqv->next;
					i++;
				}
				list* pn = new list(data, eqv->_default);
				eqv->next = pn;
				pn->next = eqv->next->next;
			} else {
				while(next != NULL)
				{
					cout << "here3" << endl;
					next = next->next;
				}
				list* pn = new list(data, _default);
				next = pn; pn->next = NULL;
			}
		}
	}*/

	T remove(int index)
	{
		if(index < len())
		{
			int i = 0;
			list* prev = this;
			while (i != index && next != NULL)
			{
				next = next->next;
				i++;
			}
			list* tmp = this;
			next = next->next->next;
			return this->data;
		}
	}

	int len()
	{
		int i = 1;
		while (next != NULL)
		{
			next = next->next;
			i++;
		}
		return i;
	}

	void sort(bool (*f) (T* first, T* second))
	{
	}
};


AbstractList<string>* get_init()
{
	string str = "Hello!";
	string def = "Error";
	list<string>* s = new list<string>(str, def);
	return s;
}

/*
int main ()
{
	AbstractList<string>* a = get_init();
	a->insert(0, "Bye");
	//cout << a->len() << endl;
	//a->insert(1, "Good morning");
	
    //a->print(cout);
	//cout << a->get(0) << endl << a->get(1) << endl << a->get(2) << endl << a->get(3) << endl;
	system ("pause");
	return 0;
}
*/