#pragma once
#ifndef _PtdModel_Wing_Header
#define _PtdModel_Wing_Header

#include <Global_Done.hxx>
#include <PtdModel_Entity.hxx>
#include <Pnt2d.hxx>
#include <Pnt3d.hxx>

#include <vector>

namespace tnbLib
{

	//- Forward Declarations
	class Geo_xDistb;

	class PtdModel_WingSection;
	class PtdModel_WingInfo;
	class PtdModel_WingView;
	class PtdModel_Profiles;
	class PtdModel_xPars;
	class PtdModel_Face;
	class PtdModel_Par;
	class PtdModel_WingExpandedView;
	class PtdModel_WrappedWingSection;
	class PtdModel_WingSectionQ;
	class PtdModel_FormMaker;
	class PtdModel_WingGlobalPars;

	class PtdModel_Wing
		: public Global_Done
	{

		friend class PtdModel_WingSection;

		/*Private Data*/

		std::shared_ptr<Geo_xDistb> theDistb_;
		std::shared_ptr<PtdModel_WingSection> theSection_;

		std::shared_ptr<PtdModel_WingInfo> theWingInfo_;
		std::shared_ptr<PtdModel_Profiles> theProfiles_;

		std::shared_ptr<PtdModel_xPars> theParameters_;
		std::shared_ptr<PtdModel_WingView> theWingView_;

		std::shared_ptr<PtdModel_Face> theUpper_;
		std::shared_ptr<PtdModel_Face> theLower_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbPtdModel_EXPORT);


		virtual std::shared_ptr<PtdModel_WingExpandedView> 
			CreateExpandView(const Standard_Integer, const PtdModel_WingSectionQ&) const = 0;

		virtual std::vector<std::shared_ptr<PtdModel_WrappedWingSection>> 
			CreateWrappedView() const = 0;

		TnbPtdModel_EXPORT void CalcXParameters();
		TnbPtdModel_EXPORT void CalcWingView();

		TnbPtdModel_EXPORT void CreateFaces();

	protected:

		//- default constructor

		PtdModel_Wing()
		{}

		//- constructors

		TnbPtdModel_EXPORT PtdModel_Wing
		(
			const std::shared_ptr<PtdModel_WingGlobalPars>&
		);


		//- protected functions and operators

		const auto& WingInfo() const
		{
			return theWingInfo_;
		}

		const auto& xParameters() const
		{
			return theParameters_;
		}

	public:

		static TnbPtdModel_EXPORT const Standard_Integer DEFAULT_NB_SECTIONS;
		static TnbPtdModel_EXPORT const Standard_Integer DEFAULT_NB_SPANS;

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

		const auto& WingView() const
		{
			return theWingView_;
		}

		const auto& UpperPatch() const
		{
			return theUpper_;
		}

		const auto& LowerPatch() const
		{
			return theLower_;
		}

		TnbPtdModel_EXPORT void Perform();

		TnbPtdModel_EXPORT void SetxDistb(const std::shared_ptr<Geo_xDistb>&);
		TnbPtdModel_EXPORT void SetxDistb(std::shared_ptr<Geo_xDistb>&&);
		TnbPtdModel_EXPORT void SetSection(const std::shared_ptr<PtdModel_WingSection>&);
		TnbPtdModel_EXPORT void SetSection(std::shared_ptr<PtdModel_WingSection>&&);

		TnbPtdModel_EXPORT void ImportMakers(const std::vector<std::shared_ptr<PtdModel_FormMaker>>&);
	};
}

#endif // !_PtdModel_Wing_Header
