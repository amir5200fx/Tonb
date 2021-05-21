#pragma once
#ifndef _SectPx_ExtrCustomProfile_Header
#define _SectPx_ExtrCustomProfile_Header

#include <SectPx_CustomProfile.hxx>

namespace tnbLib
{

	class SectPx_ExtrCustomProfile
		: public SectPx_CustomProfile
	{

		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive &ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<SectPx_CustomProfile>(*this);
		}

	protected:


		//- default constructor

		SectPx_ExtrCustomProfile()
		{}

	public:

		//- constructors

		TnbSectPx_EXPORT SectPx_ExtrCustomProfile
		(
			const std::shared_ptr<SectPx_Node>& theNode0,
			const std::shared_ptr<SectPx_Node>& theNode1
		);

		TnbSectPx_EXPORT SectPx_ExtrCustomProfile
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<SectPx_Node>& theNode0,
			const std::shared_ptr<SectPx_Node>& theNode1
		);

		TnbSectPx_EXPORT SectPx_ExtrCustomProfile
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<SectPx_Node>& theNode0,
			const std::shared_ptr<SectPx_Node>& theNode1
		);


		//- public functions and operators

		Standard_Boolean IsExtruder() const override
		{
			return Standard_True;
		}

		static TnbSectPx_EXPORT std::shared_ptr<SectPx_ExtrCustomProfile>
			MakeProfile
			(
				const std::shared_ptr<SectPx_Pnt>& theP0,
				const std::shared_ptr<SectPx_Pnt>& theP1,
				const std::shared_ptr<SectPx_FrameRegistry>& theReg
			);

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::SectPx_ExtrCustomProfile);

#endif // !_SectPx_ExtrCustomProfile_Header
