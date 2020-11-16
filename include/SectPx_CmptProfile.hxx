#pragma once
#ifndef _SectPx_CmptProfile_Header
#define _SectPx_CmptProfile_Header

#include <SectPx_RegObj.hxx>

#include <map>
#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_TopoProfile;

	class SectPx_CmptProfile
		: public SectPx_RegObj
	{

		/*Private Data*/

		std::vector<std::shared_ptr<SectPx_TopoProfile>> theProfiles_;


		DECLARE_SAVE_LOAD_HEADER(TnbSectPx_EXPORT);


		auto& ChangeProfiles()
		{
			return theProfiles_;
		}

	public:

		static TnbSectPx_EXPORT const char* typeName_;

		SectPx_CmptProfile()
		{}

		Standard_Integer NbProfiles() const
		{
			return (Standard_Integer)theProfiles_.size();
		}

		const auto& Profiles() const
		{
			return theProfiles_;
		}

		TnbSectPx_EXPORT Standard_Boolean IsCmptProfile() const override;

		TnbSectPx_EXPORT word RegObjTypeName() const override;

		TnbSectPx_EXPORT sectPxLib::regObjType RegObjType() const override;

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::SectPx_CmptProfile);

#endif // !_SectPx_CmptProfile_Header
