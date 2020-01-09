#include <cellShape.hxx>

#include <token.hxx>
#include <cellModeller.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	Istream& operator>>(Istream& is, cellShape& s)
	{
		bool readEndBracket = false;

		// Read the 'name' token for the symbol
		token t(is);

		if (t.isPunctuation())
		{
			if (t.pToken() == token::BEGIN_LIST)
			{
				readEndBracket = true;

				is >> t;
			}
			else
			{
				FatalIOErrorIn("operator>>(Istream&, cellShape& s)", is)
					<< "incorrect first token, expected '(', found "
					<< t.info()
					<< exit(FatalIOError);
			}
		}

		// it is allowed to have either a word or a number describing the model
		if (t.isLabel())
		{
			s.m = cellModeller::lookup(int(t.labelToken()));
		}
		else if (t.isWord())
		{
			s.m = cellModeller::lookup(t.wordToken());
		}
		else
		{
			FatalIOErrorIn("operator>>(Istream& is, cellShape& s)", is)
				<< "Bad type of token for cellShape symbol " << t.info()
				<< exit(FatalIOError);
			return is;
		}

		// Check that a model was found
		if (!s.m)
		{
			FatalIOErrorIn("operator>>(Istream& is, cellShape& s)", is)
				<< "CellShape has unknown model " << t.info()
				<< exit(FatalIOError);
			return is;
		}

		// Read the geometry labels
		is >> static_cast<labelList&>(s);

		if (readEndBracket)
		{
			// Read end)
			is.readEnd("cellShape");
		}

		return is;
	}


	Ostream& operator<<(Ostream& os, const cellShape & s)
	{
		// Write beginning of record
		os << token::BEGIN_LIST;

		// Write the list label for the symbol (ONE OR THE OTHER !!!)
		os << (s.m)->index() << token::SPACE;

		// Write the model name instead of the label (ONE OR THE OTHER !!!)
		// os << (s.m)->name() << token::SPACE;

		// Write the geometry
		os << static_cast<const labelList&>(s);

		// End of record
		os << token::END_LIST;

		return os;
	}


#if defined (__GNUC__)
	template<>
#endif
	Ostream& operator<<(Ostream& os, const InfoProxy<cellShape>& ip)
	{
		const cellShape& cs = ip.t_;

		if (!(&cs.model()))
		{
			os << "    cellShape has no model!\n";
		}
		else
		{
			os << cs.model().info() << endl;
		}

		os << "\tGeom:\tpoint\tlabel\txyz\n";

		forAll(cs, i)
		{
			os << "\t\t" << i << "\t" << cs[i] << endl;
		}

		return os;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //