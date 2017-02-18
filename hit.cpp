#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <iostream>
#include <stdexcept>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;

using namespace std;

void hit(int num) {
	double x0, y0, x1, y1;
	cin >> x0 >> y0 >> x1 >> y1;

	K::Point_2 origin(x0, y0), direction(x1, y1);
	K::Ray_2 ray(origin, direction);

	int flag = 0;
	for (int i = 0; i < num; i++) {
		cin >> x0 >> y0 >> x1 >> y1;
		if (flag == 0) {
			K::Point_2 point1(x0, y0), point2(x1, y1);
			K::Segment_2 seg(point1, point2);
			if (CGAL::do_intersect(ray, seg)) {
				flag = 1;
			}
		}
	}
	if (flag == 1) {
		cout << "yes" << endl;
	} else {
		cout << "no" << endl;
	}
}


int main() {
	int num;
	cin >> num;
	while (num > 0) {
		hit(num);
		cin >> num;
	}
	return 0;
}
