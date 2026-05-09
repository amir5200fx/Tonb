#include <Fade_3D.h>
#include <stdio.h>

using namespace FADE3D;

int example0_main()
{
	std::cout<<"\n";
	std::cout<<"example0: HelloTriangulation - 10 lines of code\n";
	std::cout<<"* Triangulate 4 points\n";
	std::cout<<"* Visualize the result\n\n";

	// Create a triangulation
	Fade_3D dt;

	// Create and insert 4 points
	Point3 p0(0.0,0.0,0.0);
	Point3 p1(1.0,0.0,0.0);
	Point3 p2(0.5,2.0,0.0);
	Point3 p3(0.5,0.5,1.0);
	dt.insert(p0);
	dt.insert(p1);
	dt.insert(p2);
	dt.insert(p3);

	// Draw a file for the Geomview viewer
	dt.show("example0.list");
	return 0;
}

