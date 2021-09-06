#pragma once
#ifndef _HydStatic_Bonjean2_Header
#define _HydStatic_Bonjean2_Header

#include <Global_Done.hxx>
#include <HydStatic_Module.hxx>
#include <Global_Serialization.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Geo_xDistb;
	class Marine_CmpSection;
	class Marine_Domain;
	class Marine_Body;
	class HydStatic_HydOffsetCurve;
	class NumAlg_AdaptiveInteg_Info;

	class HydStatic_Bonjean2
		: public Global_Done
	{

	public:

		enum class levDistb
		{
			uniform,
			cosine
		};

		struct bonjeanEntity
		{

			std::shared_ptr<Marine_CmpSection> Section;
			std::shared_ptr<HydStatic_HydOffsetCurve> Curve;


			//- default constructor

			bonjeanEntity()
			{}


			//- constructors

			bonjeanEntity
			(
				const std::shared_ptr<Marine_CmpSection>& theSection,
				const std::shared_ptr<HydStatic_HydOffsetCurve>& theCurve
			)
				: Section(theSection)
				, Curve(theCurve)
			{}

			bonjeanEntity
			(
				std::shared_ptr<Marine_CmpSection>&& theSection,
				std::shared_ptr<HydStatic_HydOffsetCurve>&& theCurve
			)
				: Section(std::move(theSection))
				, Curve(std::move(theCurve))
			{}


			//- public functions and operators

			TNB_SERIALIZATION(TnbHydStatic_EXPORT);

		};

	private:

		/*Private Data*/

		std::shared_ptr<Marine_Domain> theDomain_;
		std::shared_ptr<Marine_Body> theBody_;

		Standard_Integer theNbLevels_;
		levDistb theLevDistb_;


		std::vector<std::shared_ptr<bonjeanEntity>> theSections_;

		//- private functions and operators

		TNB_SERIALIZATION(TnbHydStatic_EXPORT);

		TnbHydStatic_EXPORT std::shared_ptr<Geo_xDistb> 
			CreateDistribution(const std::shared_ptr<Marine_CmpSection>&) const;

	public:

		static TnbHydStatic_EXPORT const unsigned int DEFAULT_NB_LEVELS;
		static TnbHydStatic_EXPORT const unsigned int MIN_NB_LEVELS;
		static TnbHydStatic_EXPORT unsigned short verbose;

		static TnbHydStatic_EXPORT std::shared_ptr<NumAlg_AdaptiveInteg_Info> integInfo;

		//- default constructor

		HydStatic_Bonjean2()
			: theNbLevels_(DEFAULT_NB_LEVELS)
		{}


		//- constructors


		//- public functions and operators

		const auto& Domain() const
		{
			return theDomain_;
		}

		const auto& Body() const
		{
			return theBody_;
		}

		auto NbLevels() const
		{
			return theNbLevels_;
		}

		auto LevDistb() const
		{
			return theLevDistb_;
		}

		const auto& Sections() const
		{
			return theSections_;
		}

		TnbHydStatic_EXPORT void Perform();

		void LoadDomain(const std::shared_ptr<Marine_Domain>& theDomain)
		{
			theDomain_ = theDomain;
		}

		void LoadBody(const std::shared_ptr<Marine_Body>& theBody)
		{
			theBody_ = theBody;
		}

		void SetNbLevels(const Standard_Integer n)
		{
			theNbLevels_ = n;
		}

		void SetLevDistb(const levDistb l)
		{
			theLevDistb_ = l;
		}



	};
}

#endif // !_HydStatic_Bonjean2_Header
