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


		DECLARE_SAVE_LOAD_HEADER(TnbSectPx_EXPORT);

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

		Standard_Boolean IsOverrider() const override;

		sectPxLib::regObjType RegObjType() const override;

		const auto& Pnt() const
		{
			return thePnt_;
		}
	};
}

#endif // !_SectPx_Overrider_Header
