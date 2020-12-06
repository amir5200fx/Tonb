#pragma once
#ifndef _LegModel_DispNo1_Header
#define _LegModel_DispNo1_Header

#include <LegModel_Displacement.hxx>
#include <LegModel_CtrlNet.hxx>
#include <LegModel_DispNo1_Parameters.hxx>
#include <LegModel_DispNo1_Profiles.hxx>
#include <LegModel_Displacement.hxx>
#include <LegModel_Surface.hxx>
#include <LegModel_SectionCtrlPts.hxx>

namespace tnbLib
{


	class LegModel_DispNo1_Memory
		: public LegModel_DispNo1_Profile
		, public LegModel_DispNo1_Xparams
		, public LegModel_CtrlNet
	{

		/*Private Data*/

	protected:

		LegModel_DispNo1_Memory()
		{}

	public:


	};

	class LegModel_DispNo1_HullPatch
		: public LegModel_Displacement
		, public LegModel_DispNo1_Parameters
		, public LegModel_DispNo1_Memory
	{

		typedef LegModel_Displacement entity;
		typedef LegModel_DispNo1_Parameters params;
		typedef LegModel_DispNo1_Memory memory;

		/*Private Data*/

		legModel::geomSurface theHull_;

	protected:

		TnbCadModel_EXPORT void AllocateMemory();


		//- Create profiles

		TnbCadModel_EXPORT void CreateDeckProfile();

		TnbCadModel_EXPORT void CreateFlareProfile
		(
			const Standard_Integer theSection
		);

		TnbCadModel_EXPORT void CreateFlareProfile();


		//- Calculate parameters

		TnbCadModel_EXPORT void CalcxXSections();

		TnbCadModel_EXPORT void CalcxYSections();

		TnbCadModel_EXPORT void CalcxZSections();

		TnbCadModel_EXPORT void CalcxDepthSections();

		TnbCadModel_EXPORT void CalcxDeadRise();

		TnbCadModel_EXPORT void CalcxFlare();

		TnbCadModel_EXPORT void CalcxSideSlope();

		TnbCadModel_EXPORT void CalcxTightness();

		TnbCadModel_EXPORT void CalcxRake();

		TnbCadModel_EXPORT void CalcXSheer();

		TnbCadModel_EXPORT void CalcxParameters();


		//- Apply parameters

		TnbCadModel_EXPORT void ApplyTightness();

		TnbCadModel_EXPORT void ApplyFlare();

		TnbCadModel_EXPORT void ApplyRake();

		TnbCadModel_EXPORT void ApplyForeFootShape();

		TnbCadModel_EXPORT void ApplyBowSmoothness();

		TnbCadModel_EXPORT void ApplyParameters();

		TnbCadModel_EXPORT void ApplyTightness
		(
			LegModel_CorneredSectionCtrlPts& theSection,
			const Standard_Real theTightness
		);

		TnbCadModel_EXPORT void ApplyFlare
		(
			Standard_Integer theSection
		);

		TnbCadModel_EXPORT void ApplyRake
		(
			LegModel_CorneredSectionCtrlPts& theSection,
			const Standard_Real theRake
		);


		//- Section constructors

		TnbCadModel_EXPORT std::shared_ptr<LegModel_SectionCtrlPts> CreateRawSection
		(
			const Standard_Integer Section,
			const Standard_Integer nbWidth,
			const Standard_Integer nbHeight
		);

		TnbCadModel_EXPORT std::shared_ptr<LegModel_SectionCtrlPts> CreateRawStem() const;

		TnbCadModel_EXPORT std::shared_ptr<LegModel_SectionCtrlPts> CreateRawStemPaired();

		TnbCadModel_EXPORT void CreateRawSections();


		//- Setup hull

		TnbCadModel_EXPORT void SetupControlNet();

		TnbCadModel_EXPORT void SetupPatch();

		void SetSection
		(
			const Standard_Integer Index,
			const std::shared_ptr<LegModel_SectionCtrlPts>& Section
		)
		{
			xSection[Index] = Section;
		}

		void SetControlPoint
		(
			const Standard_Integer I,
			const Standard_Integer J,
			const Pnt3d& Coord
		)
		{
			CtrlNet->SetValue(I + 1, J + 1, Coord);
		}

	protected:

		TnbCadModel_EXPORT virtual void MakeFace();

	public:

		TnbCadModel_EXPORT void Perform();

		TnbCadModel_EXPORT void PerformToPreview() override;

		const legModel::geomSurface& Patch() const
		{
			return theHull_;
		}

		const params& Parameters() const
		{
			return *this;
		}

		params& Parameters()
		{
			return *this;
		}

		const LegModel_DispNo1_Dimensions& Dimensions() const
		{
			return *this;
		}

		LegModel_DispNo1_Dimensions& Dimensions()
		{
			return *this;
		}

		const LegModel_DispNo1_Xparams& Xparams() const
		{
			return *this;
		}
	};

	class LegModel_DispNo1
		: public LegModel_DispNo1_HullPatch
	{

		/*Private Data*/

	protected:

		TnbCadModel_EXPORT void MakeFace() override;

	public:

		LegModel_DispNo1()
		{}

		TnbCadModel_EXPORT void PerformToPreview() override;
	};
}

#endif // !_LegModel_DispNo1_Header
