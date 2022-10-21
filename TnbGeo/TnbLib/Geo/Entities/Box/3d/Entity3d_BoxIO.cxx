#include <Entity3d_Box.hxx>

#include <TecPlot.hxx>
#include <OSstream.hxx>
#include <OFstream.hxx>
#include <ISstream.hxx>
#include <token.hxx>

namespace tnbLib
{

	template<>
	std::ostream& operator<<(std::ostream& os, const Entity3d_Box& theBox)
	{
		os << theBox.P0() << " " << theBox.P1();
		return os;
	}

	template<>
	Ostream& operator<<(Ostream& os, const Entity3d_Box& theBox)
	{
		os << token::BEGIN_SQR;
		os << theBox.P0() << token::COMMA << token::SPACE << theBox.P1();
		os << token::END_SQR;

		// Check state of Ostream
		os.check("Ostream & operator<<(Ostream & os, const Entity_Box<Point> &)");
		return os;
	}
}