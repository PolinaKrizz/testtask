/*****************************************************************************/
/* Реализация циклического буфера FIFO с помощью структуры Node              */
/* +: данные в памяти хранятся не последовательно                            */
/*    буфер хранит данные, которые в него положили не перезаписывая их       */
/* -: если буфер заполнен, новые данные теряются                             */
/* Implementing a circular FIFO with a library container                     */
/* +: data in memory is not stored sequentially                              */
/*    the buffer stores the data that was put into it without overwriting it */
/* -: if the buffer is full, new data is lost                                */
/*****************************************************************************/


#include <iostream>
#include <string>
class MyException								// Exception handling class. Класс обработки исключений
{
public:
	std::string stringWhat_;
	MyException() {};
	MyException(const std::string stringWhat) : stringWhat_(stringWhat) {};
};

template <typename T>
class QueueLinkedList
{
	struct  Node
	{
		T data_;
		Node* next_;
	};
	Node *head_, *tail_;						// Push, pop. Кладем, забираем
	size_t size_ = 3;							// Buffer size. Размер буфера
	int counter_;								// Number of elements in the buffer. Кол-во элементов в буффере
public:
	QueueLinkedList();
	~QueueLinkedList();
	void push(T data);
	T pop();

};

template <typename T>
QueueLinkedList<T>::QueueLinkedList()			//Buffer creation. Создание буфера
{
	Node* temp = new Node;
	head_ = temp;
	tail_ = temp;

	for (size_t i = 1; i < size_; i++) {
		Node* temp = new Node;
		head_->next_ = temp;
		head_ = temp;
	}
	head_->next_ = tail_;
	head_ = tail_;

	counter_ = 0;
}

template <typename T>
QueueLinkedList<T>::~QueueLinkedList()			//Delete buffer. Удаление буфера
{
	while (size_ != 0)							//While the size of the list is not 0. Пока размерность списка не станет нулевой
	{
		Node* temp = head_->next_;
		delete head_;                           //Remove each element in turn
		head_ = temp;                           //Удаляем каждый элемент по очереди
		size_--;                                
	}
}

template <typename T>
void QueueLinkedList<T>::push(T data) {			// Push. Добавление в буфер
	if (counter_ != size_) {					// Check if there is a place. Проверяем есть ли место
		counter_++;								// Increasing the number of elements in the buffer
												// Увеличиваем кол-во элементов в буфере
		head_->data_ = data;					// Add data. Добавляем элемент
		head_ = head_->next_;					// Move head. Сдвигаем голову
	}
	else throw MyException("Queue is full");
}

template <typename T>
T QueueLinkedList<T>::pop() {					// Pop. Берем из буфера
	if (counter_ != 0) {						// Checking if there are elements. Проверяем есть ли элементы
		counter_--;								// Reducing the number of elements 
												// Уменьшаем кол-во элементов
		T temp = tail_->data_;					// Remember the data. Запоминаем данные
		tail_ = tail_->next_;					// Move tail. Сдвигаем хвост
		return temp;
	}
	else throw MyException("Queue is empty");
}

int main() {
	try {
		QueueLinkedList<int> q;
		q.push(1);
		q.push(2);
		q.push(3);
		std::cout << q.pop();
		q.push(4);
		std::cout << q.pop();
		std::cout << q.pop();
	}
	catch (MyException& e) { std::cout << e.stringWhat_ << std::endl; }
	return 0;
}