#pragma once
#ifndef _SectPx_CustomProfile_Header
#define _SectPx_CustomProfile_Header

#include <SectPx_TopoProfile.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Pnt;

	class SectPx_CustomProfile
		: public SectPx_TopoProfile
	{

		/*Private Data*/


		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive &ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<SectPx_TopoProfile>(*this);
		}

	protected:

		SectPx_CustomProfile()
		{}

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
				const std::shared_ptr<SectPx_Pnt>& theP0,
				const std::shared_ptr<SectPx_Pnt>& theP1,
				const std::shared_ptr<SectPx_Registry>& theReg
			);
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::SectPx_CustomProfile);

#endif // !_SectPx_CustomProfile_Header
