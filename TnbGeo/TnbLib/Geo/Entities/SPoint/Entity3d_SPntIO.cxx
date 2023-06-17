#include <Entity3d_SPnt.hxx>

#include <token.hxx>
#include <OFstream.hxx>
#include <Istream.hxx>

namespace tnbLib
{
	TnbGeo_EXPORT std::ostream& operator<<(std::ostream& os, const Entity3d_SPnt& p)
	{
		os << token::BEGIN_SQR << p.Coord() << token::END_SQR <<
			token::COMMA << token::SPACE <<
			token::BEGIN_SQR << p.Para() << token::END_SQR;
		return os;
	}

	TnbGeo_EXPORT std::istream& tnbLib::operator>>(std::istream& is, Entity3d_SPnt& p)
	{
		std::string comma, sqr;
		Pnt3d p3;
		Pnt2d p2;

		is >> sqr;
		if (!is.good())
		{
			FatalErrorIn(FunctionSIG)
				<< "Error in reading a SPnt parameter" << endl
				<< abort(FatalError);
		}

		is >> p3;
		if (!is.good())
		{
			FatalErrorIn(FunctionSIG)
				<< "Error in reading a SPnt parameter" << endl
				<< abort(FatalError);
		}

		is >> sqr;
		if (!is.good())
		{
			FatalErrorIn(FunctionSIG)
				<< "Error in reading a SPnt parameter" << endl
				<< abort(FatalError);
		}

		is >> comma;
		if (!is.good())
		{
			FatalErrorIn(FunctionSIG)
				<< "Error in reading a SPnt parameter" << endl
				<< abort(FatalError);
		}

		is >> sqr;
		if (!is.good())
		{
			FatalErrorIn(FunctionSIG)
				<< "Error in reading a SPnt parameter" << endl
				<< abort(FatalError);
		}

		is >> p2;
		if (!is.good())
		{
			FatalErrorIn(FunctionSIG)
				<< "Error in reading a SPnt parameter" << endl
				<< abort(FatalError);
		}

		is >> sqr;
		if (!is.good())
		{
			FatalErrorIn(FunctionSIG)
				<< "Error in reading a SPnt parameter" << endl
				<< abort(FatalError);
		}

		p.SetCoord(std::move(p3));
		p.SetPara(std::move(p2));
		return is;
	}

	TnbGeo_EXPORT Ostream& tnbLib::operator<<(Ostream& os, const Entity3d_SPnt& P)
	{
		os << token::BEGIN_LIST;
		os << P.Coord()
			<< token::COMMA
			<< token::SPACE
			<< P.Para();
		os << token::END_LIST;

		// Check state of Ostream
		os.check("Ostream & operator<<(Ostream & os, const Entity3d_SPnt & P)");
		return os;
	}

	TnbGeo_EXPORT Istream& tnbLib::operator>>(Istream& is, Entity3d_SPnt& P)
	{
		Pnt3d p3;
		Pnt2d p2;
		string comma;
		is.readBegin("Istream & tnbLib::operator>>(Istream & is, Entity3d_SPnt & P)");
		is >> p3 >> comma >> p2;
		is.readEnd("Istream & tnbLib::operator>>(Istream & is, Entity3d_SPnt & P)");

		P.SetCoord(std::move(p3));
		P.SetPara(std::move(p2));
		// Check state of Istream
		is.check("Istream & tnbLib::operator>>(Istream & is, Entity3d_SPnt & P)");
		return is;
	}
}