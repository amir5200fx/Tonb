#pragma once
#ifndef _SectPx_ExtrTopoSegment_Header
#define _SectPx_ExtrTopoSegment_Header

#include <SectPx_TopoSegment.hxx>

namespace tnbLib
{

	class SectPx_ExtrTopoSegment
		: public SectPx_TopoSegment
	{

		/*Private Data*/

	public:

		//- default constructor

		SectPx_ExtrTopoSegment()
		{}


		//- constructors

		TnbSectPx_EXPORT SectPx_ExtrTopoSegment
		(
			const Standard_Integer theIndex, 
			const word& theName
		);

		TnbSectPx_EXPORT SectPx_ExtrTopoSegment
		(
			const std::shared_ptr<SectPx_BndPole>& thePole0,
			const std::shared_ptr<SectPx_BndPole>& thePole1
		);

		TnbSectPx_EXPORT SectPx_ExtrTopoSegment
		(
			std::shared_ptr<SectPx_BndPole>&& thePole0,
			std::shared_ptr<SectPx_BndPole>&& thePole1
		);

		TnbSectPx_EXPORT SectPx_ExtrTopoSegment
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<SectPx_BndPole>& thePole0,
			const std::shared_ptr<SectPx_BndPole>& thePole1
		);

		TnbSectPx_EXPORT SectPx_ExtrTopoSegment
		(
			const Standard_Integer theIndex,
			const word& theName,
			std::shared_ptr<SectPx_BndPole>&& thePole0,
			std::shared_ptr<SectPx_BndPole>&& thePole1
		);


		//- public functions and operators

		Standard_Boolean IsExtruder() const override
		{
			return Standard_True;
		}
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::SectPx_ExtrTopoSegment);

#endif // !_SectPx_ExtrTopoSegment_Header
