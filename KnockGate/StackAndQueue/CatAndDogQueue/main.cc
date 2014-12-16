/*Cat and dog queue problem:
*
*Implement a cat/dog queue, which has:
*1.add function to push cat or dog into queue
*2.pollAll function to pop cat or dog in the sequence they are pushed
*3.pollDog function to pop dog in the sequence dogs are pushed
*3.pollCat function to pop cat in the sequence cats are pushed
*4.isEmpty function to check whether this queue is emtpy
*5.isDogEmpty function to check that there are no dogs in this queue
*6.isCatEmpty function to check that there are no cats in this queue
*
*/

#include "time.h"
#include "stdio.h"
#include <unistd.h>
#include <queue>

enum PetType {
	CatType,
	DogType,
	UnknownType
};

enum Color {
	Red,
	Orange,
	Yellow,
	Green,
	Cyan,
	Blue,
	Purple
};

const char *color_str [] = {
	"Red",
	"Orange",
	"Yellow",
	"Green",
	"Cyan",
	"Blue",
	"Purple"
};

class Pet {
public:
	explicit Pet(Color c) {
		color = c;
	}
	virtual void print() {
		printf("I'm a pet with no color.\n");
	}
	PetType type;
	Color color;
};

class Cat:public Pet {
public:
	explicit Cat(Color c):Pet(c) {
		type = CatType;
	}
	virtual void print() {
		printf("I'm a %s cat, meow!\n", color_str[color]);
	}
};

class Dog:public Pet {
public:
	explicit Dog(Color c):Pet(c) {
		type = DogType;
	}
	virtual void print() {
		printf("I'm a %s dog, bark!\n", color_str[color]);
	}
};

/*
*Solution:
*1.There are two queues inside, one cat queue and one dog queue
*2.Wrap pet with a timetamp and add function will put it into the corresponding queue
*3.IsEmpty function will check the specified queue
*4.pollCat/Dog will poll from the cat/dog queue
*5.pollAll will compare the timestamp of both front of cat queue and dog queue and return the earlier one
*/

struct Element {
	Element(Pet *p) {
		pet = p;
		time_stamp = time(NULL);
	}
	Pet *pet;
	time_t time_stamp;
};

class PetQueue {
private:
	std::queue<Element *> CatQueue;
	std::queue<Element *> DogQueue;
public:
	PetQueue() {}
	~PetQueue() {
		while(!CatQueue.empty()) {
			Element *e = CatQueue.front();
			delete e->pet;
			delete e;
			CatQueue.pop();
		}
		while(!DogQueue.empty()) {
			Element *e = DogQueue.front();
			delete e->pet;
			delete e;
			DogQueue.pop();
		}
	}
	void add(Pet *p) {
		Element *e = new Element(p);
		switch(p->type) {
			case CatType:
			{
				CatQueue.push(e);
				break;
			}
			case DogType:
			{
				DogQueue.push(e);
				break;
			}
			default:
			{
				printf("You should add a cat or dog!\n");
				delete e;
			}
		}
	}
	bool isEmpty() {
		return CatQueue.empty() && DogQueue.empty();
	}
	bool isCatEmpty() {
		return CatQueue.empty();
	}
	bool isDogEmpty() {
		return DogQueue.empty();
	}
	Pet * pollAll() {
		if(isEmpty()) {
			return NULL;
		}
		Pet *p = NULL;
		Element *e1 = NULL;
		Element *e2 = NULL;
		if(!isCatEmpty()) {
			e1 = CatQueue.front();
		}
		if(!isDogEmpty()) {
			e2 = DogQueue.front();
		}
		if(e1 == NULL) {
			p = e2->pet;
			delete e2;
			DogQueue.pop();
		} else if(e2 == NULL) {
			p = e1->pet;
			delete e1;
			CatQueue.pop();
		} else if(e1->time_stamp > e2->time_stamp) {
			p = e2->pet;
			delete e2;
			DogQueue.pop();
		} else {
			p = e1->pet;
			delete e1;
			CatQueue.pop();
		}
		return p;
	}
	Dog * pollDog() {
		if(isDogEmpty()) {
			return NULL;
		}
		Element *e = DogQueue.front();
		Dog *d = dynamic_cast<Dog *>(e->pet);
		delete e;
		DogQueue.pop();
		return d;
	}
	Cat * pollCat() {
		if(isCatEmpty()) {
			return NULL;
		}
		Element *e = CatQueue.front();
		Cat *c = dynamic_cast<Cat *>(e->pet);
		delete e;
		CatQueue.pop();
		return c;
	}
};

int main(int argc, char *argv[]) {
	PetQueue *pq = new PetQueue();
	//The queue will be cat cat dog cat dog dog cat
	Pet *p = NULL;
	p = new Cat(Red);
	pq->add(p);
	sleep(1);
	p = new Cat(Orange);
	pq->add(p);
	sleep(1);
	p = new Dog(Yellow);
	pq->add(p);
	sleep(1);
	p = new Cat(Green);
	pq->add(p);
	sleep(1);
	p = new Dog(Cyan);
	pq->add(p);
	sleep(1);
	p = new Dog(Blue);
	pq->add(p);
	sleep(1);
	p = new Cat(Purple);
	pq->add(p);
	//Test empty functions
	printf("Total is empty:%s\n",pq->isEmpty()?"True":"False");
	printf("Cat is empty:%s\n",pq->isCatEmpty()?"True":"False");
	printf("Dog is empty:%s\n",pq->isDogEmpty()?"True":"False");
	//Test poll dog
	Dog *d = pq->pollDog();
	d->print();
	delete d;
	//Test poll cat
	Cat *c = pq->pollCat();
	c->print();
	delete c;
	//Test poll all
	while(!pq->isEmpty()) {
		p = pq->pollAll();
		p->print();
		delete p;
	}
	//Test empty functions again
	printf("Total is empty:%s\n",pq->isEmpty()?"True":"False");
	printf("Cat is empty:%s\n",pq->isCatEmpty()?"True":"False");
	printf("Dog is empty:%s\n",pq->isDogEmpty()?"True":"False");
	delete pq;
	return 0;
}
