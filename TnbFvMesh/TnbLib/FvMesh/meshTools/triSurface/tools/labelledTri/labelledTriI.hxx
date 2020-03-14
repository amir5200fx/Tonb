#pragma once
#include <IOstreams.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	//- Construct null
	inline labelledTri::labelledTri()
		:
		region_(-1)
	{}


	//- Construct from components
	inline labelledTri::labelledTri
	(
		const label A,
		const label B,
		const label C,
		const label region
	)
		:
		triFace(A, B, C),
		region_(region)
	{}


	inline labelledTri::labelledTri(Istream& is)
	{
		operator>>(is, *this);
	}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	inline label labelledTri::region() const
	{
		return region_;
	}

	inline label& labelledTri::region()
	{
		return region_;
	}


	// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

	inline Istream& operator>>(Istream& is, labelledTri& t)
	{
		if (is.format() == IOstream::ASCII)
		{
			// Read beginning of labelledTri point pair
			is.readBegin("labelledTri");

			is >> static_cast<triFace&>(t) >> t.region_;

			// Read end of labelledTri point pair
			is.readEnd("labelledTri");
		}
		else
		{
			is.read(reinterpret_cast<char*>(&t), sizeof(labelledTri));
		}

		// Check state of Ostream
		is.check("Istream& operator>>(Istream&, labelledTri&)");

		return is;
	}


	inline Ostream& operator<<(Ostream& os, const labelledTri& t)
	{
		if (os.format() == IOstream::ASCII)
		{
			os << token::BEGIN_LIST
				<< static_cast<const triFace&>(t) << token::SPACE << t.region_
				<< token::END_LIST;
		}
		else
		{
			os.write
			(
				reinterpret_cast<const char*>(&t),
				sizeof(labelledTri)
			);
		}

		// Check state of Ostream
		os.check("Ostream& operator<<(Ostream&, const labelledTri&)");


		return os;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //