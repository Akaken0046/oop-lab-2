#include <cstdio>
#include <clocale>

class Point {
protected:
	int x;
	int y;
public:
	Point() {		//конструктор
		this->x = 0;
		this->y = 0;
		printf("Point()\n");
	}
	Point(int x, int y) {	//конструктор с параметрами
		this->x = x;
		this->y = y;
		printf("Point(%i,%i)\n", x, y);
	}
	Point(const Point& p) {	//копирующий конструктор
		this->x = p.x;
		this->y = p.y;
		printf("Point(const Point &p)\n");
	}
	void SetX(int x) {
		this->x = x;
	}
	void SetY(int y) {
		this->y = y;
	}
	int GetX() {
		return this->x;
	}
	int GetY() {
		return this->y;
	}
	void Reset();
	virtual ~Point() {	//деструктор
		printf("~Point()\n");
	}
};

void Point::Reset() {
	this->x = 0;
	this->y = 0;
}

class PointDOT : public Point {	//потомок
private:
	int z;
public:
	PointDOT() : Point() {
		this->z = 0;
		printf("PointDOT()\n");
	}
	PointDOT(int x, int y, int z) : Point(x, y) {
		this->z = z;
		printf("PointDOT(%i)\n", z);
	}
	PointDOT(const PointDOT& p) {
		this->x = p.x;
		this->y = p.y;
		this->z = p.z;
		printf("PointDOT(const PointDOT &p)\n");
	}
	void SetZ(int z) {
		this->z = z;
	}
	int GetZ() {
		return this->z;
	}
	virtual ~PointDOT() {
		printf("~PointDOT()\n");
	}
};

class Direction {
private:
	Point* p1;
	Point* p2;
public:
	Direction() {
		p1 = new Point;
		p2 = new Point;
		printf("Direction()\n");
	}
	Direction(int x1, int x2, int y1, int y2) {
		p1 = new Point(x1, y1);
		p2 = new Point(x2, y2);
		printf("Direction(%i,%i,%i,%i)\n", x1, x2, y1, y2);
	}
	Direction(const Direction& v) {	//копирующий конструктор
		p1 = new Point(*(v.p1));	//глубокое копирование
		p2 = new Point(*(v.p2));
		printf("Direction(const Direction &v)\n");
	}
	~Direction() {
		delete p1;
		delete p2;
		printf("~Direction()\n");
	}
};

int main() {
	setlocale(LC_ALL, "rus");

	{
		printf("---------------------------------\n");
		printf("Статическое создание объектов\n");
		printf("---------------------------------\n");
		Point p1;
		Point p2 = Point(1, 2);
		Point p3 = Point(p2);
	}
	{
		printf("---------------------------------\n");
		printf("Динамическое создание объектов\n");
		printf("---------------------------------\n");
		Point* p1 = new Point;
		Point* p2 = new Point(1, 2);
		Point* p3 = new Point(*p2);

		delete p1;
		delete p2;
		delete p3;
	}
	{
		printf("---------------------------------\n");
		printf("Геттер динамического объекта класса\n");
		printf("---------------------------------\n");
		Point* p = new Point(2, 3);
		printf("X:%i\n", p->GetX());
		p->Reset();

		delete p;
	}
	{
		printf("---------------------------------\n");
		printf("Помещение объекта в свой тип\n");
		printf("---------------------------------\n");
		PointDOT* p = new PointDOT(1, 2, 3);

		delete p;
	}
	{
		printf("---------------------------------\n");
		printf("Помещение объекта в родительский тип\n");
		printf("---------------------------------\n");
		Point* p = new PointDOT(1, 2, 3);

		delete p;
	}
	{
		printf("---------------------------------\n");
		printf("Создание вектора\n");
		printf("---------------------------------\n");
		Direction* v1 = new Direction;
		printf("---------------------------------\n");
		printf("Создание вектора c параметрами\n");
		printf("---------------------------------\n");
		Direction* v2 = new Direction(1, 2, 1, 3);
		printf("---------------------------------\n");
		printf("Создание вектора конструктором копирования\n");
		printf("---------------------------------\n");
		Direction* v3 = new Direction(*v2);
		printf("---------------------------------\n");
		printf("Удаление векторов\n");
		printf("---------------------------------\n");
		delete v1;
		delete v2;
		delete v3;
	}

	return 0;
}
