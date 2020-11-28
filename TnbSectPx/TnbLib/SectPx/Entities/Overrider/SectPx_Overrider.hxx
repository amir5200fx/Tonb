#pragma once
#ifndef _SectPx_Overrider_Header
#define _SectPx_Overrider_Header

#include <SectPx_RegObj.hxx>
#include <Pnt2d.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_MasterPnt;

	class SectPx_Overrider
		: public SectPx_RegObj
	{

		friend class SectPx_MasterPnt;

		/*Private Data*/

		std::weak_ptr<SectPx_MasterPnt> thePnt_;


		TNB_SERIALIZATION(TnbSectPx_EXPORT);

		void SetPnt
		(
			const std::weak_ptr<SectPx_MasterPnt>& thePnt
		)
		{
			thePnt_ = thePnt;
		}

	protected:

		template<class... _Types>
		SectPx_Overrider(_Types&&... _Args)
			: SectPx_RegObj(_Args...)
		{}

	public:

		virtual Pnt2d CalcCoord() const = 0;

		TnbSectPx_EXPORT Standard_Boolean IsOverrider() const override;

		TnbSectPx_EXPORT sectPxLib::regObjType RegObjType() const override;

		const auto& Pnt() const
		{
			return thePnt_;
		}
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::SectPx_Overrider);

#endif // !_SectPx_Overrider_Header
