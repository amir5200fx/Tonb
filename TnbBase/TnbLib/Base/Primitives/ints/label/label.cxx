#include <label.hxx>

#include <error.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	const char* const pTraits<label>::typeName = "label";
	const label pTraits<label>::zero = 0;
	const label pTraits<label>::one = 1;
	const label pTraits<label>::min = labelMin;
	const label pTraits<label>::max = labelMax;

	const char* pTraits<label>::componentNames[] = { "x" };

	pTraits<label>::pTraits(Istream& is)
	{
		is >> p_;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	// Raise one label to the power of another (overloaded function call)
	label pow(label a, label b)
	{
		register label ans = 1;
		for (register label i = 0; i < b; i++)
		{
			ans *= a;
		}

#   ifdef FULLDEBUG
		if (b < 0)
		{
			FatalErrorIn("pow(label a, label b)")
				<< "negative value for b is not supported"
				<< abort(FatalError);
		}
#   endif

		return ans;
	}


	//- Return factorial(n) : 0 <= n <= 12
	label factorial(label n)
	{
		static label factTable[13] =
		{
			1, 1, 2, 6, 24, 120, 720, 5040, 40320,
			362880, 3628800, 39916800, 479001600
		};

#   ifdef FULLDEBUG
		if (n > 12 || n < 0)
		{
			FatalErrorIn("factorial(label n)")
				<< "n value out of range"
				<< abort(FatalError);
		}
#   endif

		return factTable[n];
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //