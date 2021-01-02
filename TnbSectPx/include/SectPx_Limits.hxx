#pragma once
#ifndef _SectPx_Limits_Header
#define _SectPx_Limits_Header

#include <SectPx_Parent.hxx>

namespace tnbLib
{

	class SectPx_Limits
		: public SectPx_Parent
	{

		/*Private Data*/

		std::weak_ptr<SectPx_Par> theStart_;
		std::weak_ptr<SectPx_Par> theEnd_;

	public:


		static const char* typeName_;

		SectPx_Limits()
		{}

		TnbSectPx_EXPORT SectPx_Limits(const Standard_Integer theIndex, const word& theName);

		const auto& Start() const
		{
			return theStart_;
		}

		const auto& End() const
		{
			return theEnd_;
		}

		TnbSectPx_EXPORT void SetStart(const std::shared_ptr<SectPx_Par>& thePar);

		TnbSectPx_EXPORT void SetEnd(const std::shared_ptr<SectPx_Par>& thePar);

		TnbSectPx_EXPORT Standard_Real Lower() const;

		TnbSectPx_EXPORT Standard_Real Upper() const;

		TnbSectPx_EXPORT word RegObjTypeName() const override;

		TnbSectPx_EXPORT sectPxLib::regObjType RegObjType() const override;

		//- override virtual functions from parent abstract class 

		TnbSectPx_EXPORT Standard_Integer NbChildren() const override;

		TnbSectPx_EXPORT Standard_Boolean HasChildren() const override;

		TnbSectPx_EXPORT Standard_Boolean
			HasChild
			(
				const std::shared_ptr<SectPx_Child>& thePar
			) const override;

		TnbSectPx_EXPORT std::vector<std::shared_ptr<SectPx_Child>>
			RetrieveChildren() const override;

		TnbSectPx_EXPORT void RemoveThisFromChildren() const override;

		TnbSectPx_EXPORT void AddThisToChildren() const override;

		TnbSectPx_EXPORT void RemoveThisFromChild
		(
			const std::shared_ptr<SectPx_Child>& thePar
		) const override;

		TnbSectPx_EXPORT void AddThisToChild
		(
			const std::shared_ptr<SectPx_Child>& thePar
		) const override;
	};
}

#endif // !_SectPx_Limits_Header
