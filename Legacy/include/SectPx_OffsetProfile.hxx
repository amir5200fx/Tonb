#pragma once
#ifndef _SectPx_OffsetProfile_Header
#define _SectPx_OffsetProfile_Header

#include <Pnt2d.hxx>
#include <SectPx_RegObj.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Offset;

	class SectPx_OffsetProfile
		: public SectPx_RegObj
	{

		/*Private Data*/

		std::vector<std::shared_ptr<SectPx_Offset>> theOffsets_;

	public:

		static TnbSectPx_EXPORT const char* typeName_;

		SectPx_OffsetProfile()
		{}

		TnbSectPx_EXPORT SectPx_OffsetProfile
		(
			const Standard_Integer theIndex
		);

		TnbSectPx_EXPORT SectPx_OffsetProfile
		(
			const Standard_Integer theIndex,
			const word& theName
		);


		auto NbOffsets() const
		{
			return (Standard_Integer)theOffsets_.size();
		}

		const auto& Offsets() const
		{
			return theOffsets_;
		}

		TnbSectPx_EXPORT Standard_Boolean IsOffsetProfile() const override;

		TnbSectPx_EXPORT Standard_Boolean IsFrameRegObj() const override;

		TnbSectPx_EXPORT sectPxLib::regObjType RegObjType() const override;

		TnbSectPx_EXPORT word RegObjTypeName() const override;

		TnbSectPx_EXPORT std::vector<Pnt2d> RetrievePoints() const;

		TnbSectPx_EXPORT void Import(const std::shared_ptr<SectPx_Offset>& theQ);

	};
}

#endif // !_SectPx_OffsetProfile_Header
