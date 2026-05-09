#include <Fade_3D.h>
#include <stdio.h>
using namespace FADE3D;

// Make sure that you link this example against the fast
// release version of the library. 
int example1_main()
{
	std::cout<<"example1: Benchmark Fade3D"<<std::endl<<std::endl;
	
	std::vector<int> vNumPoints;
	vNumPoints.push_back(100000);
	vNumPoints.push_back(500000);
	vNumPoints.push_back(1000000);

	// Benchmark loop
	for(size_t i=0;i<vNumPoints.size();++i)
	{
		int numPoints(vNumPoints[i]);
		
		// Generate random points
		std::vector<Point3> vInputPoints;
		for(int i=0;i<numPoints;++i)
		{
			double x=-100+(200.0*rand()/(RAND_MAX+1.0));
			double y=-100+(200.0*rand()/(RAND_MAX+1.0));
			double z=-100+(200.0*rand()/(RAND_MAX+1.0));
			vInputPoints.push_back(Point3(x,y,z));
		}
		
		// Triangulation inside two timer calls
		std::cout<<std::endl<<"Inserting "<<vInputPoints.size()<<" points"<<std::endl;
		timer("Insert Points"); // Start timer
	
			Fade_3D dt;
			dt.insert(vInputPoints);
		
		double elapsed=timer("Insert Points"); // Stop timer
		std::cout<<"Vertices per second: "<<int(vInputPoints.size()/elapsed)<<std::endl;	
		std::cout<<"Tetrahedra per second: "<<std::flush;
		std::vector<Tet3*> vTets;
		dt.getTetrahedra(vTets);
		std::cout<<int(vTets.size()/elapsed)<<std::endl<<std::endl;
	}	
	return 0;	
}


