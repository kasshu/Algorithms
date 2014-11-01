/*Cat and dog queue problem:
*
*/

#include "time.h"
#include "stdio.h"
#include <queue>

enum PetType {
	CatType,
	DogType,
	UnknownType
};

class Pet {
public:
	Pet(){}
	virtual void print() {
		printf("I'm a pet.\n");
	}
	PetType type;
};

class Cat:public Pet {
public:
	Cat() {
		type = CatType;
	}
	virtual void print() {
		printf("I'm a cat, meow!\n");
	}
};

class Dog:public Pet {
public:
	Dog() {
		type = DogType;
	}
	virtual void print() {
		printf("I'm a dog, bark!\n");
	}
};

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
		e->time_stamp = time(NULL);
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
	//The queue will be cat cat dog cat dog dog
	Pet *p = NULL;
	p = new Cat();
	pq->add(p);
	p = new Cat();
	pq->add(p);
	p = new Dog();
	pq->add(p);
	p = new Cat();
	pq->add(p);
	p = new Dog();
	pq->add(p);
	p = new Dog();
	pq->add(p);
	//Test empty functions
	printf("Total is %s\n",pq->isEmpty()?"True":"False");
	printf("Cat is %s\n",pq->isCatEmpty()?"True":"False");
	printf("Dog is %s\n",pq->isDogEmpty()?"True":"False");
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
	printf("Total is %s\n",pq->isEmpty()?"True":"False");
	printf("Cat is %s\n",pq->isCatEmpty()?"True":"False");
	printf("Dog is %s\n",pq->isDogEmpty()?"True":"False");
	delete pq;
	return 0;
}
