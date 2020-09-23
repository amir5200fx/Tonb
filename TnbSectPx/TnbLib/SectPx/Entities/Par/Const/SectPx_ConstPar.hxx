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

#endif // !_SectPx_ConstPar_Header
