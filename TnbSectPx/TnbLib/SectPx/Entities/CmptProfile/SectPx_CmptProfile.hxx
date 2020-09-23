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


		auto& ChangeProfiles()
		{
			return theProfiles_;
		}

	public:

		static const char* typeName_;

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

		Standard_Boolean IsCmptProfile() const override;

		word RegObjTypeName() const override;

		sectPxLib::regObjType RegObjType() const override;

	};
}

#endif // !_SectPx_CmptProfile_Header
