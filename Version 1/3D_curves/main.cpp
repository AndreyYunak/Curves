#include <iostream>
#include <list>
#include "3D_curves.h"
#include <memory>
#include <vector>
#include <random>
#include <algorithm>


double pi = 3.1415926535;

int main() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist1(0, 2);
	std::uniform_int_distribution<> dist2(0, 30);

	std::list<std::shared_ptr<Geometric_curves_3D>> container1;
	std::vector<std::shared_ptr<Circle>> container2;

	std::cout << "\tType: 0 - circle, 1 - ellipse, 2 - helix"<< std::endl;
	std::cout << "====================================================" << std::endl;
	//Populate a container (list) of objects created in random manner with
	//random parameters.
	for (int N = 0; N < 10; ) {

		#ifdef _DEBUG
		std::cout << "N: " << N << std::endl;
		#endif
		
		int key = dist1(gen);

		#ifdef _DEBUG
		std::cout << "key: " << key << std::endl;
		#endif

		switch (key)
		{
		case 0:
			try {
				container1.emplace_back(std::make_shared<Circle>(dist2(gen)));
			}
			catch (const char* error) {
				#ifdef _DEBUG
				std::cerr << error << std::endl;
				#endif
				break;
			};
			N++;
			break;
		case 1:
			try {
				container1.emplace_back(std::make_shared<Ellipse>(dist2(gen), dist2(gen)));
			}
			catch (const char* error) {
				#ifdef _DEBUG
				std::cerr << error << std::endl;
				#endif
				break;
			};
			N++;
			break;
		case 2:
			try {
				container1.emplace_back(std::make_shared<Helix>(dist2(gen), dist2(gen)));

			}
			catch (const char* error) {
				#ifdef _DEBUG
				std::cerr << error << std::endl;
				#endif
				break;
			};
			N++;
			break;
		default:
			break;
		};
	};
	//Print coordinates of points and derivatives of all curves in the container at t=PI/4.
	std::cout << "_________container1__size: " << container1.size() << " _____" << std::endl;
	double t = (pi / 4);
	for (auto it = container1.begin(); it != container1.end(); it++) {
		point3D point = (*it)->get_point3D(t);
		point3D point2 = (*it)->get_first_derivative(t);
		std::cout << "* Type: " << static_cast<int> ((*it)->get_type()) << std::endl;
		std::cout << "1. coordinates of point at t=PI/4: " << std::endl << "\t( " << point.x << ", " << point.y << ", " << point.z << " )" << std::endl;
		std::cout << "2. derivatives at t=PI/4: " << std::endl << "\t( " << point2.x << ", " << point2.y << ", " << point2.z << " )" << std::endl;
	};

	//Populate a second container that would contain only circles from the first container. Make sure the
	//second container shares(i.e. not clones) circles of the first one, e.g.via pointers.
	for (auto it = container1.begin(); it != container1.end(); it++) {
		if (static_cast<int> ((*it)->get_type()) == 0) {
			container2.push_back(std::static_pointer_cast<Circle> (*it));
		};
	};
	// Print a second container
	std::cout << std::endl << "_________container2__size: " << container2.size() <<" _____" << std::endl;
	std::for_each(container2.begin(), container2.end(), [](std::shared_ptr<Circle> c)
		{
			std::cout << "* Type: " << static_cast<int> (c->get_type()) << std::endl;
			std::cout << "R: " << (c)->get_R() << std::endl;
		});
	//Sort the second container in the ascending order of circles’ radii. That is, the first element has the
	//smallest radius, the last - the greatest.
	std::sort(container2.begin(), container2.end(),
		[](const std::shared_ptr<Circle>& c1, const std::shared_ptr<Circle>& c2)
		{
			return ((c1)->get_R()) < ((c2)->get_R());
		});  
	
	std::cout << std::endl << "________Sort_container2__size: " << container2.size() << " _____" << std::endl;
	std::for_each(container2.begin(), container2.end(), [](std::shared_ptr<Circle> c)
		{
			std::cout << "* Type: " << static_cast<int> (c->get_type()) << std::endl;
			std::cout << "R: " << (c)->get_R() << std::endl;
		});

	//Compute the total sum of radii of all curves in the second container.
	double sum = 0;
	std::for_each(container2.begin(), container2.end(), [&sum](std::shared_ptr<Circle> c)
		{
			sum += c->get_R();
		});
	std::cout << "Sum of radii: " << sum << std::endl;
	return 0;

};


 

