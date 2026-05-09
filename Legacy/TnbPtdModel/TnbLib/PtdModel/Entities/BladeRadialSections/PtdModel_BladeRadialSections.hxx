#pragma once
#ifndef _PtdModel_BladeRadialSections_Header
#define _PtdModel_BladeRadialSections_Header

#include <PtdModel_Entity.hxx>
#include <PtdModel_Module.hxx>
#include <Pnt3d.hxx>

#include <vector>

#include <gp_Ax2.hxx>

namespace tnbLib
{

	//- Forward Declarations
	class PtdModel_RadialSection;

	class PtdModel_BladeRadialSections
		: public PtdModel_Entity
	{

		/*Private Data*/

		gp_Ax2 theOrigin_;

		std::vector<std::shared_ptr<PtdModel_RadialSection>> theSections_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbPtdModel_EXPORT);

	public:

		//- default constructor

		PtdModel_BladeRadialSections()
		{}


		//- constructors

		PtdModel_BladeRadialSections
		(
			const std::vector<std::shared_ptr<PtdModel_RadialSection>>& theSections,
			const gp_Ax2& theOrigin
		)
			: theSections_(theSections)
			, theOrigin_(theOrigin)
		{}

		PtdModel_BladeRadialSections
		(
			const Standard_Integer theIndex,
			const word& theName, 
			const std::vector<std::shared_ptr<PtdModel_RadialSection>>& theSections, 
			const gp_Ax2& theOrigin
		)
			: PtdModel_Entity(theIndex, theName)
			, theSections_(theSections)
			, theOrigin_(theOrigin)
		{}

		PtdModel_BladeRadialSections
		(
			std::vector<std::shared_ptr<PtdModel_RadialSection>>&& theSections,
			gp_Ax2&& theOrigin
		)
			: theSections_(std::move(theSections))
			, theOrigin_(std::move(theOrigin))
		{}

		PtdModel_BladeRadialSections
		(
			const Standard_Integer theIndex,
			const word& theName,
			std::vector<std::shared_ptr<PtdModel_RadialSection>>&& theSections,
			gp_Ax2&& theOrigin
		)
			: PtdModel_Entity(theIndex, theName)
			, theSections_(std::move(theSections))
			, theOrigin_(std::move(theOrigin))
		{}


		//- public functions and operators

		const auto& Sections() const
		{
			return theSections_;
		}

		const auto& Origin() const
		{
			return theOrigin_;
		}

		void SetSections(const std::vector<std::shared_ptr<PtdModel_RadialSection>>& theSections)
		{
			theSections_ = theSections;
		}

		void SetSections(std::vector<std::shared_ptr<PtdModel_RadialSection>>&& theSections)
		{
			theSections_ = std::move(theSections);
		}

		void SetOrigin(const gp_Ax2& theOrigin)
		{
			theOrigin_ = theOrigin;
		}

		void SetOrigin(gp_Ax2&& theOrigin)
		{
			theOrigin_ = std::move(theOrigin);
		}


	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::PtdModel_BladeRadialSections);

#endif // !_PtdModel_BladeRadialSections_Header
