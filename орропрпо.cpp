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
public :
	//virtual void sort(bool (*f) (T* first, T* second)) = 0;
	virtual T get(int index) = 0;
	//virtual void set(int index, T data) = 0;
	virtual void insert(int index, T data) = 0;
	//virtual T remove(int index) = 0;
	virtual int len() = 0;
	/*void push(T data)
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
	}*/

	virtual ostream& print(ostream& o)
	{
		for (int i = 0; i < len(); i ++)
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

class list : public AbstractList<string>
{
	string data;
	list* next;

protected:
	string _default;

public:
	list()
	{
		data = "Hello!";
		next = NULL;
		_default = "Empty:(";
	}

	list (string sent)
	{
		data = sent;
		next = NULL;
		_default = "Empty:(";
	}

	list (const list& a)
	{
		data = a.data;
		next = a.next;
	}

	string get(int index)
	{
		int i = 0;
		list* tmp = new list (*this);
		while (i != index && tmp->next != NULL)
		{
			tmp = tmp->next;
			i++;
		}
		return (list(*tmp)).data;
	}

	void insert(int index, string data)
	{
		if (index != 0){
			int i = 0;
			while (i != index && next != NULL)
			{
				cout << "here3" << endl;
				next = next->next;
				i++;
			}
			list* pn = new list(next->data);
			this->data = data;
			next = pn; pn->next = next->next;
		}
	}

	int len()
	{
		int i = 0;
		while (next != NULL)
		{
			next = next->next;
			i++;
		}
		return i;
	}

	ostream& print(ostream& o)
	{
		for (int i = 0; i < len(); i ++)
		{
			o << get(i) << endl;
		}
		return o;
	}
};


AbstractList<string>* get_init()
{
	string d("Hello world!");
	list* s = new list(d);
	return s;
}


int main()
{
	list a1 = list();
	//al->read(cin);
	a1.insert(1, "bye");
	a1.print(cout);
	system("pause");
	return 0;
}