#pragma once
#ifndef _SectPx_Profile_Header
#define _SectPx_Profile_Header

#include <SectPx_RegObj.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Node;
	class SectPx_Registry;

	class SectPx_TopoProfile
		: public SectPx_RegObj
	{

		/*Private Data*/

		std::shared_ptr<SectPx_Node> theNode0_;
		std::shared_ptr<SectPx_Node> theNode1_;

	protected:

		

	public:

		static const char* typeName_;

		SectPx_TopoProfile
		(
			const std::shared_ptr<SectPx_Node>& theNode0,
			const std::shared_ptr<SectPx_Node>& theNode1
		);

		SectPx_TopoProfile
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<SectPx_Node>& theNode0,
			const std::shared_ptr<SectPx_Node>& theNode1
		);

		SectPx_TopoProfile
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<SectPx_Node>& theNode0,
			const std::shared_ptr<SectPx_Node>& theNode1
		);

		const auto& Node0() const
		{
			return theNode0_;
		}

		const auto& Node1() const
		{
			return theNode1_;
		}

		word RegObjTypeName() const override;

		sectPxLib::regObjType RegObjType() const override;

		Standard_Boolean IsProfile() const override;


		static std::shared_ptr<SectPx_TopoProfile> 
			MakeProfile
			(
				const std::shared_ptr<SectPx_Node>& theNode0, 
				const std::shared_ptr<SectPx_Node>& theNode1,
				const std::shared_ptr<SectPx_Registry>& theReg
			);
	};
}

#endif // !_SectPx_Profile_Header
