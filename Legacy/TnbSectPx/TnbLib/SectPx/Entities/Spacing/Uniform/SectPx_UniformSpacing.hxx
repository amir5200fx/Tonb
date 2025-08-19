#pragma once
#ifndef _SectPx_UniformSpacing_Header
#define _SectPx_UniformSpacing_Header

#include <SectPx_Spacing.hxx>

namespace tnbLib
{

	class SectPx_UniformSpacing
		: public SectPx_Spacing
	{

		/*Private Data*/

		Standard_Integer theNbSections_;


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<SectPx_Spacing>(*this);
			ar & theNbSections_;
		}

	protected:


		//- default constructors

		SectPx_UniformSpacing()
		{}

	public:


		static TnbSectPx_EXPORT const char* typeName_;

		//- constructors

		TnbSectPx_EXPORT SectPx_UniformSpacing
		(
			const std::shared_ptr<SectPx_Limits>& theLimits,
			const Standard_Integer nbSections
		);

		TnbSectPx_EXPORT SectPx_UniformSpacing
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<SectPx_Limits>& theLimits,
			const Standard_Integer nbSections
		);


		//- public functions and operators

		TnbSectPx_EXPORT word RegObjTypeName() const override;

		Standard_Integer NbSections() const override
		{
			return theNbSections_;
		}

		TnbSectPx_EXPORT std::vector<Standard_Real> Sections() const override;
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::SectPx_UniformSpacing);

#endif // !_SectPx_UniformSpacing_Header
