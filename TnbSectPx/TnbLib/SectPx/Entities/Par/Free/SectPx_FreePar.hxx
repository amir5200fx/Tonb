#pragma once
#ifndef _SectPx_FreePar_Header
#define _SectPx_FreePar_Header

#include <SectPx_Par.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_FieldFun;

	class SectPx_FreePar
		: public SectPx_Par
	{

		/*Private Data*/

		std::shared_ptr<SectPx_FieldFun> theFun_;


		auto& ChangeFun()
		{
			return theFun_;
		}

	public:

		static const char* typeName_;

		explicit SectPx_FreePar
		(
			const std::shared_ptr<SectPx_FieldFun>& theFun
		);

		explicit SectPx_FreePar
		(
			std::shared_ptr<SectPx_FieldFun>&& theFun
		);

		SectPx_FreePar
		(
			const Standard_Integer theIndex, 
			const std::shared_ptr<SectPx_FieldFun>& theFun
		);

		SectPx_FreePar
		(
			const Standard_Integer theIndex, 
			const word& theName, 
			const std::shared_ptr<SectPx_FieldFun>& theFun
		);


		const auto& FieldFun() const
		{
			return theFun_;
		}

		Standard_Boolean HasFieldFun() const;

		word RegObjTypeName() const override;

		sectPxLib::parType ParType() const override;

		Standard_Boolean IsFree() const override;

		Standard_Boolean IsComplete() const override;

		Standard_Boolean InCycle() const override;

		Standard_Real Value() const override;

		void Print(Ostream& out) const override;
	};
}

#endif // !_SectPx_FreePar_Header
