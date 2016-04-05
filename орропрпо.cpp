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
	//virtual void sort(bool (*f) (T* first, T* second)) = 0;
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

///////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
class list : public AbstractList<T>
{
	T data;
	list* next;

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

	list (T sent)
	{
		data = sent;
		next = NULL;
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

	void insert(int index, T data)/////////////////////////
	{
		int i = 0;
		while (i != index && next != NULL)
		{
			next = next->next;
			i++;
		}
		list* pn = new list(data);
		pn->next = next->next;
		next = pn; 
	}

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
	string str = "Hello!";
	string def = "Error";
	list<string>* s = new list<string>(str, def);
	return s;
}


int main()
{
	list<string> a1 = list<string>();
	//a1.read(cin);
	a1.insert(0, "bye");
	//a1.set(0, "bye!");
	a1.print(cout);
	system("pause");
	return 0;
}