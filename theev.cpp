#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <CGAL/Min_circle_2.h>
#include <iostream>
#include <cmath>
#include <vector>

typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef CGAL::Min_circle_2_traits_2<K> Traits;
typedef CGAL::Min_circle_2<Traits> Min_circle;

using namespace std;

struct Point{
	K::Point_2 point;
	double squared_distance;
	bool operator< (const Point &Point_inst) const {
		return squared_distance < myPoint_inst.squared_distance;
	}
};

double ceil_to_double(const K::FT &x) {
	double a = ceil(CGAL::to_double(x));
	while (a >= x + 1) {
		a -= 1;
	}
	while (a < x) {
		a += 1;
	}
	return a;
}

void theev() {

	int n;
	cin >> n;

	vector<K::Point_2> points(n);
	vector<myPoint> myPoints(n);

	double x0, y0;
	cin >> x0 >> y0;
	myPoints[0].point = K::Point_2(0, 0);
	myPoints[0].squared_distance = 0;
	for (int i = 1; i < n; i++) {
		double x, y, xx, yy;
		cin >> x >> y;
		xx = x - x0;
		yy = y - y0;
		myPoints[i].point = K::Point_2(xx, yy);
		myPoints[i].squared_distance = xx * xx + yy * yy;
	}
	sort(myPoints.begin(), myPoints.end());
	for (int i = 0; i < n; i++) {
		points[i] = myPoints[i].point;
	}

	vector<double> record;
	int left = 0, right = n;
	while (left < right) {
		int i = (left + right) / 2;
		double r_left = myPoints[i].squared_distance;
		Min_circle mc(&(points[i + 1]), &*points.end(), true);
		Traits::Circle c = mc.circle();
		double r_right = CGAL::to_double((c.squared_radius()));

		record.push_back(max(r_left, r_right));
		
		if (left == right - 1) {
			break;
		}

		if (r_right > r_left) {
			left = i;
		} else if (r_right < r_left) {
			right = i;
		} else {
			break;
		}
	}

	double min_r = record[0];
	for (int i = 1; i < record.size(); i++) {
		if (record[i] < min_r) {
			min_r = record[i];
		}
	}

	cout << setprecision(0) << setiosflags(ios::fixed) << ceil_to_double(min_r) << endl;	
}

int main() {
	ios_base::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {
		theev();
	}
	return 0;
}
