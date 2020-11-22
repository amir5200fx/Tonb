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

		static TnbSectPx_EXPORT const char* typeName_;

		TnbSectPx_EXPORT explicit SectPx_FreePar
		(
			const std::shared_ptr<SectPx_FieldFun>& theFun
		);

		TnbSectPx_EXPORT explicit SectPx_FreePar
		(
			std::shared_ptr<SectPx_FieldFun>&& theFun
		);

		TnbSectPx_EXPORT SectPx_FreePar
		(
			const Standard_Integer theIndex, 
			const std::shared_ptr<SectPx_FieldFun>& theFun
		);

		TnbSectPx_EXPORT SectPx_FreePar
		(
			const Standard_Integer theIndex, 
			const word& theName, 
			const std::shared_ptr<SectPx_FieldFun>& theFun
		);


		const auto& FieldFun() const
		{
			return theFun_;
		}

		TnbSectPx_EXPORT Standard_Boolean HasFieldFun() const;

		TnbSectPx_EXPORT word RegObjTypeName() const override;

		TnbSectPx_EXPORT sectPxLib::parType ParType() const override;

		TnbSectPx_EXPORT Standard_Boolean IsFree() const override;

		TnbSectPx_EXPORT Standard_Boolean IsComplete() const override;

		TnbSectPx_EXPORT Standard_Boolean InCycle() const override;

		TnbSectPx_EXPORT Standard_Real Value() const override;

		void SetFieldFun(const std::shared_ptr<SectPx_FieldFun>& fun)
		{
			theFun_ = fun;
		}

		TnbSectPx_EXPORT void Print(Ostream& out) const override;
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::SectPx_FreePar);

#endif // !_SectPx_FreePar_Header
