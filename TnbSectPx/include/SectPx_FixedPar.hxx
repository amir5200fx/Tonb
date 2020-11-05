#pragma once
#ifndef _SectPx_FixedPar_Header
#define _SectPx_FixedPar_Header

#include <SectPx_Par.hxx>
#include <SectPx_Value.hxx>

namespace tnbLib
{

	class SectPx_FixedPar
		: public SectPx_Par
	{

		/*Private Data*/

		sectPxLib::real theValue_;


		/*private functions and operators*/

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<SectPx_Par>(*this);
			ar & theValue_;
		}

		auto& ChangeValue()
		{
			return theValue_;
		}

	public:

		static const char* typeName_;

		explicit SectPx_FixedPar
		(
			const Standard_Real theValue
		);

		SectPx_FixedPar
		(
			const Standard_Integer theIndex,
			const Standard_Real theValue
		);

		SectPx_FixedPar
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Standard_Real theValue
		);

		auto X() const
		{
			return theValue_();
		}

		auto& X()
		{
			return theValue_();
		}

		word RegObjTypeName() const override;

		sectPxLib::parType ParType() const override;

		Standard_Boolean IsFixed() const override;

		Standard_Boolean IsComplete() const override;

		Standard_Boolean InCycle() const override;

		Standard_Real Value() const override;

		void Print(Ostream& out) const override;

		Standard_Boolean IsChanged() const
		{
			return theValue_.IsChanged();
		}

		void SetValue(const Standard_Real x);

	};
}

#endif // !_SectPx_FixedPar_Header
