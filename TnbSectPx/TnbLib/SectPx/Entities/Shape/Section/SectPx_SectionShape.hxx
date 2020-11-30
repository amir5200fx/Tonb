#pragma once
#ifndef _SectPx_SectionShape_Header
#define _SectPx_SectionShape_Header

#include <SectPx_Shape.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_ProfileShape;

	class SectPx_SectionShape
		: public SectPx_Shape
	{

		/*Private Data*/

		std::vector<std::shared_ptr<SectPx_ProfileShape>> theProfiles_;

	public:

		SectPx_SectionShape()
		{}

		SectPx_SectionShape
		(
			const std::vector<std::shared_ptr<SectPx_ProfileShape>>& theProfiles
		)
			: theProfiles_(theProfiles)
		{}

		SectPx_SectionShape
		(
			const Standard_Integer theIndex, 
			const word& theName, 
			const std::vector<std::shared_ptr<SectPx_ProfileShape>>& theProfiles
		)
			: SectPx_Shape(theIndex, theName)
			, theProfiles_(theProfiles)
		{}


		const auto& Profiles() const
		{
			return theProfiles_;
		}

		void SetProfiles
		(
			const std::vector<std::shared_ptr<SectPx_ProfileShape>>& theProfiles
		)
		{
			theProfiles_ = theProfiles;
		}


		Standard_Boolean IsSection() const override;
	};
}

#endif // !_SectPx_SectionShape_Header
