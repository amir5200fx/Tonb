#include <helperFunctionsStringConversion.hxx>

#include <error.hxx>

#include <sstream>

//#define DEBUG_pMesh

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *//

	namespace help
	{

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *//

		scalar textToScalar(const word& w)
		{
			std::stringstream ss;
			ss << w;

			double s;
			ss >> s;
			return s;
		}

		//- convert the text to label
		label textToLabel(const word& w)
		{
			return label(textToScalar(w));
		}

		word scalarToText(const scalar s)
		{
			std::ostringstream ss;
			ss << s;

			return ss.str();
		}

		word labelToText(const label l)
		{
			std::ostringstream ss;
			ss << l;

			return ss.str();
		}

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *//

	} // End namespace help

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *//

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //