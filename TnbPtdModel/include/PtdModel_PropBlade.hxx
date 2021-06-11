#pragma once
#ifndef _PtdModel_PropBlade_Header
#define _PtdModel_PropBlade_Header

#include <Global_Done.hxx>
#include <PtdModel_PropEntity.hxx>
#include <Pnt2d.hxx>
#include <Pnt3d.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Geo_xDistb;

	class PtdModel_xPars;
	class PtdModel_BladeInfo;
	class PtdModel_Profiles;
	class PtdModel_Face;
	class PtdModel_BladeView;
	class PtdModel_BladeSectionQ;
	class PtdModel_BladeExpandedView;
	class PtdModel_BladeGlobalPars;
	class PtdModel_UnWrappedBladeSection;
	class PtdModel_WrappedBladeSection;
	class PtdModel_FormMaker;
	class PtdModel_PropSection;

	class PtdModel_PropBlade
		: public PtdModel_Entity
		, public Global_Done
	{


		friend class PtdModel_PropSection;

		/*Private Data*/

		std::shared_ptr<Geo_xDistb> theDistb_;
		std::shared_ptr<PtdModel_PropSection> theSection_;

		std::shared_ptr<PtdModel_BladeInfo> theBladeInfo_;
		std::shared_ptr<PtdModel_Profiles> theProfiles_;

		std::shared_ptr<PtdModel_xPars> theParameters_;	
		std::shared_ptr<PtdModel_BladeView> theBladeView_;


		std::shared_ptr<PtdModel_Face> theBack_;
		std::shared_ptr<PtdModel_Face> theFace_;

		//- private functions and operators

		TNB_SERIALIZATION(TnbPtdModel_EXPORT);

		virtual std::shared_ptr<PtdModel_BladeExpandedView> CreateExpandView(const PtdModel_BladeSectionQ&) const = 0;
		
		virtual std::vector<std::shared_ptr<PtdModel_UnWrappedBladeSection>> CreateUnWrappedView() const = 0;
		virtual std::vector<std::shared_ptr<PtdModel_WrappedBladeSection>> CreateWrappedView() const = 0;

		TnbPtdModel_EXPORT void CalcXParameters();
		TnbPtdModel_EXPORT void CalcBladeView();
		
		TnbPtdModel_EXPORT void CreateFaces();

	protected:

		//- default constructor

		PtdModel_PropBlade()
		{}

		//- constructors

		TnbPtdModel_EXPORT PtdModel_PropBlade
		(
			const std::shared_ptr<PtdModel_BladeGlobalPars>&
		);

		//- protected functions and operators

		const auto& BladeInfo() const
		{
			return theBladeInfo_;
		}

		const auto& xParameters() const
		{
			return theParameters_;
		}

		

	public:

		//- public functions and operators

		TnbPtdModel_EXPORT Standard_Integer NbSections() const;

		const auto& xDistb() const
		{
			return theDistb_;
		}

		const auto& Section() const
		{
			return theSection_;
		}

		const auto& Profiles() const
		{
			return theProfiles_;
		}

		const auto& BladeView() const
		{
			return theBladeView_;
		}

		const auto& BackPatch() const
		{
			return theBack_;
		}

		const auto& FacePatch() const
		{
			return theFace_;
		}

		void Perform();

		TnbPtdModel_EXPORT void ImportMakers(const std::vector<std::shared_ptr<PtdModel_FormMaker>>&);
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::PtdModel_PropBlade);

#endif // !_PtdModel_PropBlade_Header
