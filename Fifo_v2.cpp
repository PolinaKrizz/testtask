/*****************************************************************************/
/* Реализация циклического буфера FIFO с помощью библиотечного контейнера    */
/* +: буфер хранит последние полученные данные                               */
/* -: буфер перезаписывает данные, старые данные теряются                    */
/* Implementing a circular FIFO with a library container                     */
/* +: the buffer stores the last put data                                    */
/* -: buffer overwrites data, old data is lost                               */
/*****************************************************************************/

#include <iostream>
#include <vector>
#include <string>
class MyException								// Exception handling class. Класс обработки исключений
{
public:
	std::string stringWhat_;
	MyException() {};
	MyException(const std::string stringWhat) : stringWhat_(stringWhat) {};
};

template <typename T>
class Queue
{
private:
	size_t size_ = 3;							// Buffer size. Размер буфера
	std::vector<T> queue_;
	size_t head_;								// Push. Кладем
	size_t tail_;								// Pop. Забираем
	bool isEmpty_;
	bool isFull_;
public:
	Queue() : queue_(size_), head_(0), tail_(0), isEmpty_(true), isFull_(false) {};
	void enqueue(T data);
	T dequeue();
};

template <typename T>
void Queue<T>::enqueue(T data)
{
	if (head_ == tail_ && !isEmpty_) {			// If the head has caught up with the tail, move it
		isFull_ = true;							// Если голова догнала хвост, сдвигаем его
		tail_++;
	}
	queue_[head_] = data;						// Add data. Добавляем элемент
	if (head_ == size_ - 1) {					// Move head. Сдвигаем голову
		head_ = 0;
	}
	else {
		head_++;
	}

	if (isEmpty_ == true) {						// If it was empty, change the flag
		isEmpty_ = false;						// Если был пуст, меняем
	}

}

template <typename T>
T Queue<T>::dequeue()
{
	if (!isEmpty_) {							
		T temp = queue_[tail_];
		queue_[tail_] = '\0';
		if (tail_ == size_ - 1) {
			tail_ = 0;
		}
		else {
			tail_++;
		}

		if (isFull_ == true) {					// If it was full, change the flag
			isFull_ = false;					// Если был занят, меняем
		}

		if (tail_ == head_) {					// If the tail has caught up with the head, the array is empty
			isEmpty_ = true;					// Если хвост догнал голову, массив пуст
		}
		return temp;
	}
	else {
		throw MyException("Queue is empty");
	}
}


int main() {
	try {
		Queue<std::string> s;
		s.enqueue("a");
		s.enqueue("sS");
		s.enqueue("d");
		s.enqueue("f");
		std::cout << s.dequeue();
		std::cout << s.dequeue();
		std::cout << s.dequeue() << std::endl;

		Queue<char> c;
		c.enqueue('c');
		c.enqueue('z');
		c.enqueue('a');
		c.enqueue('1');
		std::cout << c.dequeue();
		std::cout << c.dequeue();
		std::cout << c.dequeue() << std::endl;

		Queue<int> i;
		i.enqueue(1);
		i.enqueue(2);
		i.enqueue(3);
		i.enqueue(4);
		std::cout << i.dequeue();
		std::cout << i.dequeue();
		std::cout << i.dequeue();
		std::cout << i.dequeue();
	}
	catch (MyException& e) { std::cout << e.stringWhat_ << std::endl; }
	return 0;
}