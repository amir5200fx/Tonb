#pragma once
#ifndef _Model_DisplNo1_Header
#define _Model_DisplNo1_Header

#include <Model_Displ.hxx>
#include <Model_DisplNo1Pars.hxx>
#include <Model_DisplNo1ParProfiles.hxx>
#include <Model_DisplNo1xPars.hxx>
#include <Model_VesselProfileXs.hxx>

namespace tnbLib
{

	// Forward Declarations [12/23/2022 Payvand]

	class Model_ParamProfile;
	class Model_SectionVessel;

	class Model_DisplNo1
		: public Model_Displ
	{

	public:

		struct SectionData 
		{
			Standard_Integer nbWidth;
			Standard_Integer nbHeight;

			Standard_Real x;
			Standard_Real z;
			Standard_Real sideSlope;
			Standard_Real deadrise;
			Standard_Real width;
			Standard_Real height;
		};

	private:

		/*Private Data*/

		Model_DisplNo1Pars theParameters_;
		Model_DisplNo1ParProfiles theProfiles_;


		// Memory object [12/23/2022 Payvand]

		Model_DisplNo1xPars theXPars_;

		// Private functions and operators [12/22/2022 Payvand]

		auto& ProfilesRef()
		{
			return theProfiles_;
		}

		const auto& XPars() const
		{
			return theXPars_;
		}

		auto& XParsRef()
		{
			return theXPars_;
		}

		Standard_Integer NbSections() const;
		Standard_Integer NbRows() const;

		std::shared_ptr<Model_ParamProfile> 
			CreateDeckProfile() const;

		std::shared_ptr<Model_ParamProfile> 
			CreateKeelProfile() const;

		std::vector<Standard_Real> DeckXs() const;
		std::vector<Standard_Real> KeelXs() const;
		
		void CreateFlares();

		TnbModel_EXPORT std::shared_ptr<modelLib::vesselLib::DeckProfileXs> CalcXSections() const;
		TnbModel_EXPORT std::shared_ptr<modelLib::vesselLib::KeelProfileXs> CalcYSections() const;
		TnbModel_EXPORT std::shared_ptr<modelLib::vesselLib::KeelProfileXs> CalcZSections() const;

		TnbModel_EXPORT std::shared_ptr<modelLib::vesselLib::KeelProfileXs> CalcxDepthSection() const;
		TnbModel_EXPORT std::shared_ptr<modelLib::vesselLib::KeelProfileXs> CalcxDeadrise() const;
		//std::shared_ptr<modelLib::vesselLib::KeelProfileXs> CalcxFlare() const;
		TnbModel_EXPORT std::shared_ptr<modelLib::vesselLib::KeelProfileXs> CalcxSideslope() const;
		TnbModel_EXPORT std::shared_ptr<modelLib::vesselLib::KeelProfileXs> CalcxTightness() const;
		//std::shared_ptr<modelLib::vesselLib::KeelProfileXs> CalcxRake() const;

		std::shared_ptr<Model_SectionVessel> CreateSection(const SectionData& theData) const;

		void CalcxParameters();

		void ApplyTightness(const std::shared_ptr<Model_SectionVessel>&, const Standard_Real theTightness) const;
		void ApplyFlare();
		void ApplyRake();
		void ApplyForeFootShape();
		void ApplyParameters();

		void CheckDeckProfile(const std::shared_ptr<Model_ParamProfile>&, const char* theFunName) const;
		void CheckKeelProfile(const std::shared_ptr<Model_ParamProfile>&, const char* theFunName) const;

		// Static functions [12/23/2022 Payvand]

		static std::shared_ptr<Model_ParamProfile>
			CreateFlareProfile
			(
				const std::shared_ptr<Model_SectionVessel>& theSection,
				const Standard_Real theFlare
			);

	public:

		static Standard_Real MIN_FLARE;
		static Standard_Real SMALL_TOL;
		static Standard_Real Zero;
		static Standard_Real Keel;

		static Standard_Real MAX_SIDESLOPE_COEFF;
		static Standard_Real MAX_DEADRISE_COEFF;

		// default constructor [12/21/2022 Payvand]

		Model_DisplNo1()
		{}

		// constructors [12/21/2022 Payvand]

		Model_DisplNo1(const Standard_Integer theIndex, const word& theName)
			: Model_Displ(theIndex, theName)
		{}


		// Public functions and operators [12/21/2022 Payvand]

		const auto& Parameters() const
		{
			return theParameters_;
		}

		auto& ParametersRef()
		{
			return theParameters_;
		}

		const auto& Profiles() const
		{
			return theProfiles_;
		}

	};
}


#endif // !_Model_DisplNo1_Header
