#pragma once
#ifndef _HydStatic_HydCurves_Header
#define _HydStatic_HydCurves_Header

#include <Global_Done.hxx>
#include <Marine_BodiesFwd.hxx>
#include <Marine_VesselParams.hxx>
#include <HydStatic_Module.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class HydStatic_Spacing;
	class HydStatic_HydCurvesGraph;
	class Marine_Body;
	class Marine_Domain;
	class Marine_BaseLine;
	class Marine_MultLevWaterDomain;
	class Marine_Wave;
	class NumAlg_AdaptiveInteg_Info;

	class HydStatic_HydCurves
		: public Global_Done
	{


	public:

		struct colTable
		{
			word Name;

			std::vector<Standard_Real> Values;

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive &ar, const unsigned int /*file_version*/)
			{
				ar & Name;
				ar & Values;
			}
		};

		struct csvTable
		{
			std::vector<colTable> Columns;

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive &ar, const unsigned int /*file_version*/)
			{
				ar & Columns;
			}
		};

		struct steffenTessellInfo
		{

			static TnbHydStatic_EXPORT const Standard_Integer DEFAULT_NB_SAMPLES;

			// default constructor [7/9/2021 Amir]
			steffenTessellInfo();

			Standard_Boolean Apply;
			Standard_Integer NbSamples;


			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive &ar, const unsigned int /*file_version*/)
			{
				ar & Apply;
				ar & NbSamples;
			}
		};

		struct waterInfo
		{
			// default constructor [7/9/2021 Amir]
			waterInfo();


			Standard_Real RhoS;
			Standard_Real RhoF;


			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive &ar, const unsigned int /*file_version*/)
			{
				ar & RhoS;
				ar & RhoF;
			}
		};

		struct rudderInfo
		{
			// default constructor [7/9/2021 Amir]
			rudderInfo();

			Standard_Boolean RudderAxis;
			Standard_Real RudderAxisLoc;


			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive &ar, const unsigned int /*file_version*/)
			{
				ar & RudderAxis;
				ar & RudderAxisLoc;
			}
		};

		struct algInfo
		{

			static TnbHydStatic_EXPORT const Standard_Real DEFAULT_DISPL_FACTOR;

			// default constructor [7/9/2021 Amir]
			algInfo();

			Standard_Boolean Interpolate;
			Standard_Real DisplFactor;

			steffenTessellInfo SteffenInfo;


			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive &ar, const unsigned int /*file_version*/)
			{
				ar & Interpolate;
				ar & DisplFactor;
				ar & SteffenInfo;
			}
		};

	private:

		typedef NumAlg_AdaptiveInteg_Info info;

		/*Private Data*/

		waterInfo theWaterInfo_;
		rudderInfo theRudderInfo_;
		algInfo theAlgInfo_;

		std::shared_ptr<Marine_MultLevWaterDomain> theWaters_;

		std::shared_ptr<csvTable> theCSV_;
		std::shared_ptr<HydStatic_HydCurvesGraph> theGraph_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbHydStatic_EXPORT);


		static TnbHydStatic_EXPORT marineLib::TM 
			CalcTM
			(
				const std::shared_ptr<marineLib::Body_Wetted>& theBody, 
				const std::shared_ptr<Marine_Wave>& theWave,
				const marineLib::APP& theApp, 
				const marineLib::FPP& theFpp
			);

		static TnbHydStatic_EXPORT marineLib::APP
			CalcAPP
			(
				const Standard_Real theAxis
			);

		static TnbHydStatic_EXPORT marineLib::APP
			CalcAPP
			(
				const std::shared_ptr<marineLib::Body_Wetted>& theBody
			);

		TnbHydStatic_EXPORT std::tuple
			<
			marineLib::CB, 
			marineLib::CM,
			marineLib::CP,
			marineLib::CWL,
			marineLib::LCF,
			marineLib::LCB,
			marineLib::AW, 
			marineLib::MCT,
			marineLib::KML,
			marineLib::KM, 
			marineLib::KB,
			marineLib::DISPV
			>
			CalcParameters
			(
				const std::shared_ptr<marineLib::Body_Wetted>& theBody, 
				const Marine_BaseLine& theBase, 
				const std::shared_ptr<Marine_Wave>& theWave,
				const std::shared_ptr<info>& theInfo
			);

		auto & GraphRef()
		{
			return theGraph_;
		}


	public:

		static TnbHydStatic_EXPORT size_t clippNo;
		static TnbHydStatic_EXPORT size_t verbose;

		static TnbHydStatic_EXPORT const Standard_Real DEFAULT_RHOSW;
		static TnbHydStatic_EXPORT const Standard_Real DEFAULT_RHOFW;


		// default constructor [7/9/2021 Amir]

		TnbHydStatic_EXPORT HydStatic_HydCurves();


		//- public functions and operators

		const auto& WaterInfo() const
		{
			return theWaterInfo_;
		}

		const auto& RudderInfo() const
		{
			return theRudderInfo_;
		}

		const auto& AlgInfo() const
		{
			return theAlgInfo_;
		}

		const auto& Waters() const
		{
			return theWaters_;
		}

		const auto& Graph() const
		{
			return theGraph_;
		}

		const auto& CsvTable() const
		{
			return theCSV_;
		}

		TnbHydStatic_EXPORT void Perform();

		void LoadWaters
		(
			const std::shared_ptr<Marine_MultLevWaterDomain>& theWaters
		)
		{
			theWaters_ = theWaters;
		}

		TnbHydStatic_EXPORT void SetRudderLocation(const Standard_Real x);

		TnbHydStatic_EXPORT void SetRhoSW(const Standard_Real rho);
		TnbHydStatic_EXPORT void SetRhoFW(const Standard_Real rho);
		TnbHydStatic_EXPORT void SetSteffenTessellation(const Standard_Boolean useSteffen);
		TnbHydStatic_EXPORT void SetInterpolation(const Standard_Boolean doIt);
	};
}

#endif // !_HydStatic_HydCurves_Header
