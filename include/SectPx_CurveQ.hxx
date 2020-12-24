#pragma once
#ifndef _SectPx_CurveQ_Header
#define _SectPx_CurveQ_Header

#include <SectPx_RegObj.hxx>
#include <SectPx_PolesFwd.hxx>
#include <SectPx_Module.hxx>

namespace tnbLib
{


	// Forward Declarations
	class SectPx_Pole;

	class SectPx_CurveQ
		: public SectPx_RegObj
	{

		/*Private Data*/

		std::shared_ptr<SectPx_Pole> thePole0_;
		std::shared_ptr<SectPx_Pole> thePole1_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbSectPx_EXPORT);


		static TnbSectPx_EXPORT void CheckPole(const std::shared_ptr<SectPx_Pole>& thePole, const char* name);

	public:

		static const char* typeName_;

		SectPx_CurveQ()
		{}

		TnbSectPx_EXPORT SectPx_CurveQ
		(
			const Standard_Integer theIndex, 
			const word& theName
		);

		TnbSectPx_EXPORT SectPx_CurveQ
		(
			const std::shared_ptr<SectPx_Pole>& thePole0,
			const std::shared_ptr<SectPx_Pole>& thePole1
		);

		TnbSectPx_EXPORT SectPx_CurveQ
		(
			const Standard_Integer theIndex, 
			const word& theName, 
			const std::shared_ptr<SectPx_Pole>& thePole0, 
			const std::shared_ptr<SectPx_Pole>& thePole1
		);


		TnbSectPx_EXPORT word RegObjTypeName() const override;

		TnbSectPx_EXPORT sectPxLib::regObjType RegObjType() const override;

		TnbSectPx_EXPORT Standard_Boolean IsCurveQ() const override;

		const auto& Pole0() const
		{
			return thePole0_;
		}

		const auto& Pole1() const
		{
			return thePole1_;
		}

		TnbSectPx_EXPORT void LoadPole0
		(
			const std::shared_ptr<SectPx_Pole>& thePole
		);

		TnbSectPx_EXPORT void LoadPole1
		(
			const std::shared_ptr<SectPx_Pole>& thePole
		);
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::SectPx_CurveQ);

#endif // !_SectPx_CurveQ_Header
