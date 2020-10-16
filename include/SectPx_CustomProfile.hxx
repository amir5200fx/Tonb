#pragma once
#ifndef _SectPx_CustomProfile_Header
#define _SectPx_CustomProfile_Header

#include <SectPx_TopoProfile.hxx>

namespace tnbLib
{

	class SectPx_CustomProfile
		: public SectPx_TopoProfile
	{

		/*Private Data*/

	public:

		static const char* typeName_;

		SectPx_CustomProfile
		(
			const std::shared_ptr<SectPx_Node>& theNode0,
			const std::shared_ptr<SectPx_Node>& theNode1
		);

		SectPx_CustomProfile
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<SectPx_Node>& theNode0,
			const std::shared_ptr<SectPx_Node>& theNode1
		);

		SectPx_CustomProfile
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<SectPx_Node>& theNode0,
			const std::shared_ptr<SectPx_Node>& theNode1
		);

		word RegObjTypeName() const override;

		static std::shared_ptr<SectPx_CustomProfile>
			MakeProfile
			(
				const std::shared_ptr<SectPx_Node>& theNode0,
				const std::shared_ptr<SectPx_Node>& theNode1,
				const std::shared_ptr<SectPx_Registry>& theReg
			);
	};
}

#endif // !_SectPx_CustomProfile_Header
