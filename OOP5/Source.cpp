#include<iostream>
#include<string>
#include<Windows.h>
#include<assert.h>

class Worker
{
	int id;
	std::string name;
	std::string surname;
	unsigned int age;
	int page_count;
public:
	static int myid;
	Worker():id(0),name(""),surname(""),age(0),page_count(0){}
	Worker(std::string name, std::string surname, unsigned int age, int page_count)
	{
		setID();
		setName(name);
		setSurname(surname);
		setAge(age);
		setPageCount(page_count);
	}
	//Setter
	void setID()
	{
		this->id = ++myid;
	}
	void setName(std::string name)
	{
		this->name = name;
	}
	void setSurname(std::string surname)
	{
		this->surname = surname;
	}
	void setAge(unsigned int age)
	{
		this->age = age;
	}
	void setPageCount(int page_count)
	{
		this->page_count = page_count;
	}
	//Getter
	int getID()const
	{
		return id;
	}
	std::string getName()const
	{
		return name;
	}
	std::string getSurname()const
	{
		return surname;
	}
	unsigned int getAge()const
	{
		return age;
	}
	int getPageCount()const
	{
		return page_count;
	}
	//
	friend std::ostream& operator<<(std::ostream& out, const Worker& worker);
};

std::ostream& operator<<(std::ostream& out, const Worker& worker)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	out << "===================================\n";
	out << "ID: ";
	SetConsoleTextAttribute(hConsole, 12);
	out << worker.getID() << std::endl;
	SetConsoleTextAttribute(hConsole, 15);
	out << "Name: ";
	SetConsoleTextAttribute(hConsole, 10);
	out << worker.getName() << std::endl;
	SetConsoleTextAttribute(hConsole, 15);
	out << "Surname: ";
	SetConsoleTextAttribute(hConsole, 10);
	out << worker.getSurname() << std::endl;
	SetConsoleTextAttribute(hConsole, 15);
	out << "Age: ";
	SetConsoleTextAttribute(hConsole, 10);
	out << worker.getAge() << std::endl;
	SetConsoleTextAttribute(hConsole, 15);
	out << "Page Count: ";
	SetConsoleTextAttribute(hConsole, 10);
	out << worker.getPageCount() << std::endl;
	SetConsoleTextAttribute(hConsole, 15);
	return out;
}

int Worker::myid = 0;

class Queue
{
	Worker* workers;
	size_t capacity;
	size_t count;
	size_t front;
	size_t rear;

public:
	Queue():workers(nullptr),capacity(0),count(0),front(0),rear(0){}
	Queue(int size)
	{
		workers = new Worker[size];
		capacity = size;
		count = 0;
		front = 0;
		rear = 0;
	}
	void enqueue(Worker& worker)
	{
		assert(!isFull());
		this->workers[rear] = worker;
		++rear;
		count++;
	}
	Worker dequeue()
	{
		assert(!isEmpty());
		Worker deleted = workers[front];
		auto temp = new Worker[size() - 1];
		for (size_t i = 0; i < size() - 1; i++)
		{
			temp[i] = workers[i + 1];
		}
		delete[] workers;
		count = size() - 1;
		workers = temp;
		rear--;
		return deleted;
	}
	size_t size() const
	{
		return count;
	}
	Worker& peek()
	{
		return workers[front];
	}
	bool isFull()
	{
		return size() == capacity;
	}
	bool isEmpty()
	{
		return size() == 0;
	}
	~Queue()
	{
		if (workers != nullptr)
		{
			delete[] workers;
			workers = nullptr;
		}
	}
};
class Print
{
	Queue* queue;
public:

	Print() :queue(nullptr) {}
	Print(const Queue* queue)
	{
		setQueue(queue);
	}
	//Setter
	void setQueue(const Queue* queue)
	{
		this->queue = new Queue(*queue);
	}
	//
	void start()
	{
		for (;!queue->isEmpty();)
		{
			Worker rear = queue->dequeue();
			std::cout << rear << std::endl;
			std::cout << "Worker " << rear.getName() << "'s papers was printed." << std::endl;
			Sleep(500);
		}
	}
	//
	~Print()
	{
		if (queue != nullptr)
		{
			delete queue;
			queue = nullptr;
		}
	}
};
int main()
{

	Worker w1("name1","surname1",20,10);
	Worker w2("name2","surname2",20,10);
	Worker w3("name3","surname3",20,10);
	Queue* queue = new Queue(3);
	queue->enqueue(w1);
	queue->enqueue(w2);
	queue->enqueue(w3);
	Print printer(queue);
	printer.start();
	return 0;
}
