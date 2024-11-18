#pragma once
#ifndef _Global_Bound_Header
#define _Global_Bound_Header

#include <Global_CascadeTypes.hxx>
#include <Global_Serialization.hxx>

namespace tnbLib
{

	template<class T>
	class Global_Bound
	{

		/*Private Data*/

		T theLower_;
		T theUpper_;


		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & theLower_;
			ar & theUpper_;
		}

	protected:

		Global_Bound()
		{}

		Global_Bound
		(
			const T& theLower,
			const T& theUpper
		)
			: theLower_(theLower)
			, theUpper_(theUpper)
		{}

	public:

		const T& Lower() const
		{
			return theLower_;
		}

		T& Lower()
		{
			return theLower_;
		}

		const T& Upper() const
		{
			return theUpper_;
		}

		T& Upper()
		{
			return theUpper_;
		}

		Standard_Boolean IsInside(const T& x) const
		{
			if (x < Lower()) return Standard_False;
			if (x > Upper()) return Standard_False;
			return Standard_True;
		}

		void SetLower(const T& theLower)
		{
			theLower_ = theLower;
		}

		void SetUpper(const T& theUpper)
		{
			theUpper_ = theUpper;
		}
	};


	typedef Global_Bound<Standard_Integer> intBound;

	template<>
	inline intBound::Global_Bound()
		: theLower_(IntegerFirst())
		, theUpper_(IntegerLast())
	{}

	typedef Global_Bound<Standard_Real> realBound;

	template<>
	inline realBound::Global_Bound()
		: theLower_(RealFirst())
		, theUpper_(RealLast())
	{}
}

#endif // !_Global_Bound_Header
