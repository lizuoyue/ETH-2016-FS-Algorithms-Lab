#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <iostream>
#include <vector>

typedef  CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef  CGAL::Min_circle_2_traits_2<K> Traits;
typedef  CGAL::Min_circle_2<Traits> Min_circle;

using namespace std;

double ceil_to_double(const K::FT& x) {
	double a = ceil(CGAL::to_double(x));
	while (a >= x + 1) {
		a -= 1;
	}
	while (a < x) {
		a += 1;
	}
	return a;
}

void antenna(int num) {

	vector<K::Point_2> points(num);

	for (int i = 0; i < num; i++) {
		double x, y;
		cin >> x >> y;
		points[i] = K::Point_2(x, y);
	}

	Min_circle mc(&*points.begin(), &*points.end(), true);
	Traits::Circle c = mc.circle();
	cout << setprecision(0) << setiosflags(ios::fixed) << ceil_to_double(sqrt(c.squared_radius())) << endl;
}

int main() {
	int num;
	cin >> num;
	while (num > 0) {
		antenna(num);
		cin >> num;
	}
	return 0;
}
