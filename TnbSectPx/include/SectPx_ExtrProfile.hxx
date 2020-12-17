#pragma once
#ifndef _SectPx_ExtrProfile_Header
#define _SectPx_ExtrProfile_Header

#include <Pnt2d.hxx>
#include <SectPx_Parent.hxx>
#include <SectPx_ExtrProfileType.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Par;

	class SectPx_ExtrProfile
		: public SectPx_Parent
	{

		/*Private Data*/

		std::weak_ptr<SectPx_Par> theStart_;
		std::weak_ptr<SectPx_Par> theEnd_;

		/*private functions and operators*/

		TNB_SERIALIZATION(TnbSectPx_EXPORT);


	protected:


		template<class... _Types>
		SectPx_ExtrProfile(_Types&&... _Args)
			: SectPx_Parent(_Args...)
		{}

	public:

		const auto& Start() const
		{
			return theStart_;
		}

		const auto& End() const
		{
			return theEnd_;
		}

		TnbSectPx_EXPORT void SetStart
		(
			const std::shared_ptr<SectPx_Par>& thePar
		);

		TnbSectPx_EXPORT void SetEnd
		(
			const std::shared_ptr<SectPx_Par>& thePar
		);

		TnbSectPx_EXPORT Standard_Real Lower() const;

		TnbSectPx_EXPORT Standard_Real Upper() const;

		TnbSectPx_EXPORT Standard_Boolean IsExtrProfile() const override;

		virtual SectPx_ExtrProfileType ExtrProfileType() const = 0;

		virtual Standard_Real MinLower() const = 0;

		virtual Standard_Real MaxUpper() const = 0;

		virtual Standard_Integer NbPoints() const = 0;

		virtual Pnt2d Point(const Standard_Integer theIndex) const = 0;

		virtual std::vector<Standard_Real> X() const = 0;
	};
}


BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::SectPx_ExtrProfile);

#endif // !_SectPx_ExtrProfile_Header
