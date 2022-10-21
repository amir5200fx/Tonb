#include <Entity2d_Box.hxx>

#include <TecPlot.hxx>
#include <OSstream.hxx>
#include <OFstream.hxx>
#include <ISstream.hxx>
#include <token.hxx>

namespace tnbLib
{

	template<>
	std::ostream& operator<<(std::ostream& os, const Entity2d_Box& theBox)
	{
		os << theBox.P0() << " " << theBox.P1();
		return os;
	}

	template<>
	Ostream& operator<<(Ostream& os, const Entity2d_Box& theBox)
	{
		os << token::BEGIN_SQR;
		os << theBox.P0() << token::COMMA << token::SPACE << theBox.P1();
		os << token::END_SQR;

		// Check state of Ostream
		os.check("Ostream & operator<<(Ostream & os, const Entity_Box<Point> &)");
		return os;
	}

	template<>
	void Entity2d_Box::ExportToPlt
	(
		OFstream& theFile
	) const
	{
		Io::WriteVariables("X Y", theFile);

		Io::WriteFeTriangleZone(4, 4, theFile);

		Corner(Box2d_PickAlgorithm_SW).AddToPlt(theFile);
		theFile << endl;
		Corner(Box2d_PickAlgorithm_SE).AddToPlt(theFile);
		theFile << endl;
		Corner(Box2d_PickAlgorithm_NE).AddToPlt(theFile);
		theFile << endl;
		Corner(Box2d_PickAlgorithm_NW).AddToPlt(theFile);
		theFile << endl;

		theFile << "1 2 1" << endl;
		theFile << "2 3 2" << endl;
		theFile << "3 4 3" << endl;
		theFile << "4 1 4" << endl;
	}
}