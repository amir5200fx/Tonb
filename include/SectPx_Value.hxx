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

		T theValue_;

		mutable Standard_Boolean IsChanged_;


		/*private functions and operators*/

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & theValue_;
			ar & IsChanged_;
		}

	public:

		SectPx_Value()
			: theValue_(0)
			, IsChanged_(Standard_False)
		{}

		SectPx_Value(const T theValue)
			: theValue_(theValue)
			, IsChanged_(Standard_False)
		{}

		auto IsChanged() const
		{
			return IsChanged_;
		}

		const T& Value() const
		{
			IsChanged_ = Standard_False;
			return theValue_;
		}

		T& ChangeValue()
		{
			IsChanged_ = Standard_True;
			return theValue_;
		}

		const auto& operator()() const
		{
			return Value();
		}

		auto& operator()()
		{
			return ChangeValue();
		}

		void SetValue(const Standard_Real x)
		{
			IsChanged_ = Standard_True;
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
