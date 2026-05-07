#include <Pnt2d.hxx>
#include <Entity2d_Box.hxx>

#include <fstream>

// include headers that implement a archive in simple text format
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include <GCE2d_MakeSegment.hxx>
#include <GeomTools_Curve2dSet.hxx>
#include <Pln_Curve.hxx>
#include <Pln_CurveTools.hxx>
#include <Geo_Serialization.hxx>

using namespace tnbLib;

int main()
{
	// create and open a character archive for output
	std::ofstream ofs("filename");

	Pnt2d p0(0.1, 0.3);
	Pnt2d p1(1.1, 1.3);

	Entity2d_Box b(std::move(p0), std::move(p1));

	auto cc = GCE2d_MakeSegment(Pnt2d(0, 0), Pnt2d(1, 1));
	auto curve = Pln_Curve(cc.Value());

	gp_XY ax(0,1);

	// save data to archive
	{
		boost::archive::binary_oarchive oa(ofs);
		// write class instance to archive
		oa << curve;
		oa << ax;
		// archive and stream closed when destructors are called
	}

	// ... some time later restore the class instance to its orginal state
	//Entity2d_Box newg;
	Pln_Curve newg;
	{
		// create and open an archive for input
		std::ifstream ifs("filename");
		boost::archive::binary_iarchive ia(ifs);
		// read class state from archive
		ia >> newg;
		// archive and stream closed when destructors are called

		GeomTools_Curve2dSet::PrintCurve2d(newg.Geometry(), std::cout);
		//std::cout << newg << std::endl;
	}
	return 0;
}