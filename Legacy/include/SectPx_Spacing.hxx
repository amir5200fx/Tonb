#pragma once
#ifndef _SectPx_Spacing_Header
#define _SectPx_Spacing_Header

#include <SectPx_Parent.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Limits;

	class SectPx_Spacing
		: public SectPx_Parent
	{

		/*Private Data*/

		std::shared_ptr<SectPx_Limits> theLimits_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbSectPx_EXPORT);

	protected:

		SectPx_Spacing()
		{}

		TnbSectPx_EXPORT SectPx_Spacing
		(
			const std::shared_ptr<SectPx_Limits>& theLimits
		);

		TnbSectPx_EXPORT SectPx_Spacing
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<SectPx_Limits>& theLimits
		);

	public:

		const auto& Limits() const
		{
			return theLimits_;
		}

		TnbSectPx_EXPORT Standard_Real Lower() const;

		TnbSectPx_EXPORT Standard_Real Upper() const;

		Standard_Real NormalizedParameter(const Standard_Real x) const
		{
			return (x - Lower()) / (Upper() - Lower());
		}

		virtual Standard_Integer NbSections() const = 0;

		virtual std::vector<Standard_Real> Sections() const = 0;


		//- override virtual functions from parent abstract class 

		TnbSectPx_EXPORT Standard_Boolean IsShapeRegObj() const override;

		TnbSectPx_EXPORT sectPxLib::regObjType RegObjType() const override;

		TnbSectPx_EXPORT Standard_Integer NbChildren() const override;

		TnbSectPx_EXPORT Standard_Boolean HasChildren() const override;

		TnbSectPx_EXPORT Standard_Boolean HasChild
		(
			const std::shared_ptr<SectPx_Child>& thePar
		) const override;

		TnbSectPx_EXPORT void RemoveThisFromChildren() const override;

		TnbSectPx_EXPORT void AddThisToChildren() const override;

		TnbSectPx_EXPORT void AddThisToChild
		(
			const std::shared_ptr<SectPx_Child>& thePar
		) const override;

		TnbSectPx_EXPORT void RemoveThisFromChild
		(
			const std::shared_ptr<SectPx_Child>& thePar
		) const override;

		TnbSectPx_EXPORT std::vector<std::shared_ptr<SectPx_Child>>
			RetrieveChildren() const override;
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::SectPx_Spacing);

#endif // !_SectPx_Spacing_Header
