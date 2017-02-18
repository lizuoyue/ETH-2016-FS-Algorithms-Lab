#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;

using namespace std;

struct segment {
	K::Segment_2 seg;
	K::FT dist;
	bool operator< (const segment &seg_inst) const {
		return dist < seg_inst.dist;
	}
};

double floor_to_double(const K::FT& x) {
	double a = floor(CGAL::to_double(x));
	while (a > x) {
		a -= 1;
	}
	while (a + 1 <= x) {
		a += 1;
	}
	return a;
}

void first_hit(int num) {
	double x0, y0, x1, y1;
	cin >> x0 >> y0 >> x1 >> y1;

	K::Point_2 origin(x0, y0), direction(x1, y1);
	K::Ray_2 ray(origin, direction);

	vector<segment> seg_list(num);
	for (int i = 0; i < num; i++) {
		cin >> x0 >> y0 >> x1 >> y1;
		K::Point_2 point1(x0, y0), point2(x1, y1);
		seg_list[i].seg = K::Segment_2(point1, point2);
		seg_list[i].dist = CGAL::squared_distance(origin, seg_list[i].seg);
	}
	sort(seg_list.begin(), seg_list.end());

	int flag = 0;
	K::Point_2 first_point;
	K::FT min_dist;
	for (int i = 0; i < num; i++) {
		if (flag == 0) {
			if (CGAL::do_intersect(ray, seg_list[i].seg)) {
				auto intersection = CGAL::intersection(ray, seg_list[i].seg);
				if (const K::Point_2 *pp = boost::get<K::Point_2>(&*intersection)) {
					first_point = *pp;
					min_dist = CGAL::squared_distance(origin, first_point);
					flag = 1;
				} else if (const K::Segment_2 *ps = boost::get<K::Segment_2>(&*intersection)) {
					K::FT result = CGAL::compare_distance_to_point(origin, ps->source(), ps->target());
					if (result == CGAL::SMALLER) {
						first_point = ps->source();
					} else {
						first_point = ps->target();
					}
					min_dist = CGAL::squared_distance(origin, first_point);
					flag = 1;
				} else {
					continue;
				}
			}
		} else {
			if (seg_list[i].dist > min_dist) {
				break;
			}
			if (CGAL::do_intersect(ray, seg_list[i].seg)) {
				auto intersection = CGAL::intersection(ray, seg_list[i].seg);
				if (const K::Point_2 *pp = boost::get<K::Point_2>(&*intersection)) {
					K::FT temp_dist = CGAL::squared_distance(origin, *pp);
					if (temp_dist < min_dist) {
						first_point = *pp;
						min_dist = temp_dist;
					}
				} else if (const K::Segment_2 *ps = boost::get<K::Segment_2>(&*intersection)) {
					K::Point_2 temp_point;
					K::FT result = CGAL::compare_distance_to_point(origin, ps->source(), ps->target());
					if (result == CGAL::SMALLER) {
						temp_point = ps->source();
					} else {
						temp_point = ps->target();
					}
					K::FT temp_dist = CGAL::squared_distance(origin, temp_point);
					if (temp_dist < min_dist) {
						first_point = *pp;
						min_dist = temp_dist;
					}
				} else {
					continue;
				}
			}
		}
	}
	if (!flag) {
		cout << "no" << endl;
	} else {
		cout << setprecision(0) << setiosflags(ios::fixed) << floor_to_double(first_point.x()) << " " << floor_to_double(first_point.y()) << endl;
	}
}

int main() {
	int num;
	cin >> num;
	while (num > 0) {
		first_hit(num);
		cin >> num;
	}
	return 0;
}
