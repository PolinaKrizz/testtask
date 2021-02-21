/*****************************************************************************/
/* Реализация циклического буфера FIFO с помощью библиотечного контейнера    */
/* +: буфер хранит данные, которые в него положили не перезаписывая их       */
/* -: если буфер заполнен, новые данные теряются                             */
/* Implementing a circular FIFO with a library container                     */
/* +: the buffer stores the data that was put into it without overwriting it */
/* -: if the buffer is full, new data is lost                                */
/*****************************************************************************/

#include <iostream>
#include <vector>
#include <string>
class MyException							// Exception handling class. Класс обработки исключений
{
public:
	std::string stringWhat_;
	MyException() {};
	MyException(const std::string stringWhat) : stringWhat_(stringWhat) {};
};

template <typename T>
class Queue									// FIFO circular buffer class. Класс циклического буфера FIFO
{
private:
	size_t size_ = 3;						// Buffer size. Размер буфера
	std::vector<T> queue_;
	size_t head_;							// Push. Кладем
	size_t tail_;							// Pop. Забираем
public:
	Queue() : queue_(size_), head_(0), tail_(0) {};
	void enqueue(T data);
	T dequeue();
	bool isEmpty();
};

template <typename T>
void Queue<T>::enqueue(T data)
{
	if (tail_ != (head_ + 1) % size_) {		// The array stores size-1 elements. В массиве хранится size-1 элементов
		queue_[head_] = data;
		if (head_ == size_ - 1) {
			head_ = 0;
		}
		else {
			head_++;
		}
	}
	else throw MyException("Queue is full"); // An exception is thrown when trying to add another item
											 // Выдается исключение при попытке добавить еще один элемент
}

template <typename T>
T Queue<T>::dequeue()
{
	if (!isEmpty()) {
		T temp = queue_[tail_];
		queue_[tail_] = 0;
		if (tail_ == size_ - 1) {
			tail_ = 0;
		}
		else {
			tail_++;
		}
		return temp;
	}
	else {
		throw MyException("Queue is empty");
	}
}

template <typename T>
bool Queue<T>::isEmpty()					// If the head and tail point to the same place in the array, then it is empty
{											// Если голова и хвост указывают на одно место в массиве значит он пуст
	return (head_ == tail_);
}


int main() {
	try {
		Queue<int> q;
		q.enqueue(1);
		q.enqueue(2);
		q.enqueue(1);
		std::cout<< q.dequeue();
		q.enqueue(3);
		std::cout << q.dequeue();
		std::cout << q.dequeue();
	}
	catch (MyException& e) { std::cout << e.stringWhat_ << std::endl; }
	return 0;
}