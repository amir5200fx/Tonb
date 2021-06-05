#pragma once
#ifndef _PtdModel_PropBlade_Header
#define _PtdModel_PropBlade_Header

#include <PtdModel_PropEntity.hxx>
#include <Pnt3d.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class PtdModel_BladeInfo;
	class PtdModel_xPars;
	class PtdModel_BladeProfiles;
	class PtdModel_BladeFace;
	class PtdModel_BladeView;
	class PtdModel_BladeExpandedView;
	class PtdModel_UnWrappedBladeSection;
	class PtdModel_WrappedBladeSection;

	class PtdModel_PropBlade
		: public PtdModel_Entity
	{

		/*Private Data*/

		std::shared_ptr<PtdModel_BladeInfo> theBladeInfo_;
		std::shared_ptr<PtdModel_xPars> theParameters_;
		std::shared_ptr<PtdModel_BladeProfiles> theProfiles_;
		std::shared_ptr<PtdModel_BladeView> theBladeView_;


		std::shared_ptr<PtdModel_BladeFace> theBack_;
		std::shared_ptr<PtdModel_BladeFace> theFace_;

		//- private functions and operators

		TNB_SERIALIZATION(TnbPtdModel_EXPORT);

		virtual std::shared_ptr<PtdModel_BladeExpandedView> CreateExpandView(const std::vector<Pnt3d>& theTf, const std::vector<Pnt3d>& theTb) const = 0;
		
		virtual void CreateUnWrappedView() const = 0;
		virtual void CreateWrappedView() const = 0;

		void CreateFaces();

		void CreateProfiles();
		

	protected:

		//- default constructor

		PtdModel_PropBlade()
		{}

		//- constructors


		//- protected functions and operators

		const auto& BladeInfo() const
		{
			return theBladeInfo_;
		}

		const auto& xParameters() const
		{
			return theParameters_;
		}

		const auto& BladeView() const
		{
			return theBladeView_;
		}

	public:

		//- public functions and operators

		const auto& BackPatch() const
		{
			return theBack_;
		}

		const auto& FacePatch() const
		{
			return theFace_;
		}

		virtual void Perform() = 0;
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::PtdModel_PropBlade);

#endif // !_PtdModel_PropBlade_Header
