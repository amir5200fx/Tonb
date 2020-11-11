#pragma once
#ifndef _SectPx_ConstPar_Header
#define _SectPx_ConstPar_Header

#include <SectPx_Par.hxx>
#include <SectPx_Value.hxx>

namespace tnbLib
{

	class SectPx_ConstPar
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

	protected:

		SectPx_ConstPar()
		{}

	public:


		static const char* typeName_;

		explicit SectPx_ConstPar
		(
			const Standard_Real theValue
		);

		SectPx_ConstPar
		(
			const Standard_Integer theIndex,
			const Standard_Real theValue
		);

		SectPx_ConstPar
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Standard_Real theValue
		);

		const auto& X() const
		{
			return theValue_();
		}

		word RegObjTypeName() const override;

		sectPxLib::parType ParType() const override;

		Standard_Boolean IsConstant() const override;

		Standard_Boolean IsComplete() const override;

		Standard_Boolean InCycle() const override;

		Standard_Real Value() const override;

		void SetValue(const Standard_Real x);

		void Print(Ostream& out) const override;
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::SectPx_ConstPar);

#endif // !_SectPx_ConstPar_Header
