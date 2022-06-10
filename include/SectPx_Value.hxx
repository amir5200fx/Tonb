#pragma once
#ifndef _SectPx_Value_Header
#define _SectPx_Value_Header

#include <Standard_TypeDef.hxx>
#include <Global_Serialization.hxx>
#include <SectPx_Module.hxx>

namespace tnbLib
{

	template<class T>
	class SectPx_Value
	{

		/*Private Data*/

		T theMin_;
		T theMax_;

		T theValue_;

		mutable Standard_Boolean IsChanged_;


		/*private functions and operators*/

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & theMin_;
			ar & theMax_;
			ar & theValue_;
			ar & IsChanged_;
		}

	public:

		SectPx_Value()
			: theMin_(0)
			, theMax_(0)
			, theValue_(0)
			, IsChanged_(Standard_False)
		{}

		SectPx_Value(const T theValue, const T theMin, const T theMax)
			: theMin_(theMin)
			, theMax_(theMax)
			, theValue_(theValue)
			, IsChanged_(Standard_False)
		{}

		auto IsChanged() const
		{
			return IsChanged_;
		}

		T Value() const
		{
			IsChanged_ = Standard_False;
			return theValue_;
		}

		T MinValue() const
		{
			return theMin_;
		}

		T MaxValue() const
		{
			return theMax_;
		}

		auto operator()() const
		{
			return Value();
		}

		void SetMinValue(const Standard_Real x)
		{
			theMin_ = x;
		}

		void SetMaxValue(const Standard_Real x)
		{
			theMax_ = x;
		}

		void SetValue(Standard_Real x)
		{
			IsChanged_ = Standard_True;
			if (x < MinValue())  x = MinValue();
			if (x > MaxValue()) x = MaxValue();
			theValue_ = x;
		}
	};

	namespace sectPxLib
	{

		typedef SectPx_Value<Standard_Real> real;
		typedef SectPx_Value<Standard_Integer> label;
	}
}

#endif // !_SectPx_Value_Header
