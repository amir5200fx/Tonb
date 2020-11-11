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


		DECLARE_SAVE_LOAD_HEADER(TnbSectPx_EXPORT);

		auto& ChangeFun()
		{
			return theFun_;
		}

	protected:

		SectPx_FreePar()
		{}

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

		void SetFieldFun(const std::shared_ptr<SectPx_FieldFun>& fun)
		{
			theFun_ = fun;
		}

		void Print(Ostream& out) const override;
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::SectPx_FreePar);

#endif // !_SectPx_FreePar_Header
