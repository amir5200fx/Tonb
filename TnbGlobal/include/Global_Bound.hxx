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

	template<>
	class Global_Bound<Standard_Integer>
	{
		/*Private Data*/
		Standard_Integer theLower_;
		Standard_Integer theUpper_;

		//- Private functions and operators
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar& theLower_;
			ar& theUpper_;
		}
	protected:
		// default constructor
		Global_Bound() = default;

		// constructors
		Global_Bound(Standard_Integer lower, Standard_Integer upper)
			: theLower_(lower)
			, theUpper_(upper)
		{}
	public:
		// Public functions and operators

		auto Lower() const { return theLower_; }
		auto Upper() const { return theUpper_; }
		auto& Lower() { return theLower_; }
		auto& Upper() { return theUpper_; }

		auto IsInside(Standard_Integer x) const
		{
			return INSIDE(x, Lower(), Upper());
		}

		void SetLower(Standard_Integer lower)
		{
			theLower_ = lower;
		}
		void SetUpper(Standard_Integer upper)
		{
			theUpper_ = upper;
		}
	};

	template<>
	class Global_Bound<Standard_Real>
	{
		/*Private Data*/
		Standard_Real theLower_;
		Standard_Real theUpper_;

		//- Private functions and operators
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar& theLower_;
			ar& theUpper_;
		}
	protected:
		// default constructor
		Global_Bound() = default;

		// constructors
		Global_Bound(Standard_Real lower, Standard_Real upper)
			: theLower_(lower)
			, theUpper_(upper)
		{
		}
	public:
		// Public functions and operators

		auto Lower() const { return theLower_; }
		auto Upper() const { return theUpper_; }
		auto& Lower() { return theLower_; }
		auto& Upper() { return theUpper_; }

		auto IsInside(Standard_Real x) const
		{
			return INSIDE(x, Lower(), Upper());
		}

		void SetLower(Standard_Real lower)
		{
			theLower_ = lower;
		}
		void SetUpper(Standard_Real upper)
		{
			theUpper_ = upper;
		}
	};

	typedef Global_Bound<Standard_Integer> intBound;
	typedef Global_Bound<Standard_Real> realBound;

}

#endif // !_Global_Bound_Header
