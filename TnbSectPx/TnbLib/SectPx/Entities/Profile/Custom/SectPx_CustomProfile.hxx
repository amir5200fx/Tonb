#pragma once
#ifndef _SectPx_CustomProfile_Header
#define _SectPx_CustomProfile_Header

#include <SectPx_TopoProfile.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Pnt;
	class SectPx_FrameRegistry;

	class SectPx_CustomProfile
		: public SectPx_TopoProfile
	{

		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive &ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<SectPx_TopoProfile>(*this);
		}

	protected:


		//- default constructor

		SectPx_CustomProfile()
		{}

	public:

		static TnbSectPx_EXPORT const char* typeName_;


		//- constructors

		TnbSectPx_EXPORT SectPx_CustomProfile
		(
			const std::shared_ptr<SectPx_Node>& theNode0,
			const std::shared_ptr<SectPx_Node>& theNode1
		);

		TnbSectPx_EXPORT SectPx_CustomProfile
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<SectPx_Node>& theNode0,
			const std::shared_ptr<SectPx_Node>& theNode1
		);

		TnbSectPx_EXPORT SectPx_CustomProfile
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<SectPx_Node>& theNode0,
			const std::shared_ptr<SectPx_Node>& theNode1
		);


		//- public functions and operators

		TnbSectPx_EXPORT word RegObjTypeName() const override;

		static TnbSectPx_EXPORT std::shared_ptr<SectPx_CustomProfile>
			MakeProfile
			(
				const std::shared_ptr<SectPx_Pnt>& theP0,
				const std::shared_ptr<SectPx_Pnt>& theP1,
				const std::shared_ptr<SectPx_FrameRegistry>& theReg
			);
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::SectPx_CustomProfile);

#endif // !_SectPx_CustomProfile_Header
