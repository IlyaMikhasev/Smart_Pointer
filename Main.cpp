#include <iostream>
#include <memory>
class A {
public: 
	A() {
		std::cout << "конструктор A\n";
	}
	~A() {
		std::cout << "деструктор A\n";
	}

};
class Point {
	public:
		Point(int x, int y) :_x(x), _y(y) {
			std::cout << "Constraction Point\n";
		}
		int getX()const {
			return _x;
		}
		~Point() {
			std::cout << "destraction Point\n";
		}
private:
	int _x;
	int _y;
};
template<typename T>
class Smart_ptr {
public:
	Smart_ptr(T* t) :_ptr(t) {}
	T* operator->() {
		return _ptr;
	}
	~Smart_ptr() {
		delete _ptr;
	}
private:
	T* _ptr;
};
//unique_ptr можно передать в параметры функции по ссылке
void basicFunc(const std::unique_ptr<Point>& p) {
	std::cout << p->getX() << '\n';
}
class Parent {};
class Child: public Parent {};
std::shared_ptr<Parent> SomeMethod() {
	Child ch;
	std::shared_ptr<Parent> pP = std::make_shared<Parent>(ch);//static_cast из child  в Parent
	return pP;
}
class Ivehicle {
public:
	virtual int getSpeed() const = 0;
	virtual const std::string& getType() const = 0;
	virtual ~Ivehicle() {}
};
class Car : public Ivehicle {
public:
	Car(int speed):_speed(speed){}
	int getSpeed() const override {
		return _speed;
	}
	const std::string& getType()const override {
		return _type;
	}
private:
	int _speed;
	std::string _type = "Car";

};
class Van :public Car {
public:
	Van(int speed) :Car(speed) {}
	const std::string& getType()const override {
		return _type;
	}
private:
	std::string _type = "Van";
};
void FuncCar(std::shared_ptr<Car> carPtr) {
	std::cout<<"Inside func Car" << '\n';
	std::cout<<carPtr->getSpeed() << '\n';
	std::cout<<carPtr->getType() << '\n';
}
int main() {
	setlocale(LC_ALL, "Russian");
	//std::auto_ptr<A> p(new A());//уже удалили такой вид указателей
	// 
	//shared_ptr -имеет контрольный блок , в котором лежит счетчик указателей
	// 
	//unique_ptr - гарантирует , что только один указатель будет владеть одним обьектом


	/*std::unique_ptr<A> uptr(new A());*/

	//std::unique_ptr<Point> pPoint(new Point(5, 4));
	//std::cout << pPoint->getX() << '\n';

	Smart_ptr<Point> sm(new Point(3, 3));
	std::cout << sm->getX() << '\n';
	std::unique_ptr<Point> OkPtr = std::make_unique<Point>(4, 5);//правильное создание указателя
	std::shared_ptr<Point> sPrt = std::make_shared<Point>(2, 3);
	basicFunc(OkPtr);

	std::cout << "***********************\n";
	std::shared_ptr<Van> van = std::make_shared<Van>(50);
	std::cout << van->getSpeed() << '\n';
	std::cout << van->getType() << '\n';
	std::cout << "***********************\n";
	std::shared_ptr<Car> pCarv = std::dynamic_pointer_cast<Car>(van);//динамик каст указателей
	std::cout << pCarv->getSpeed() << '\n';
	std::cout << pCarv->getType() << '\n';
	std::cout << "***********************\n";
	FuncCar(pCarv);

	return 0;
}