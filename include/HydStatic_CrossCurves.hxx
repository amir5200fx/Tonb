#pragma once
#ifndef _HydStatic_CrossCurves_Header
#define _HydStatic_CrossCurves_Header

#include <Global_Done.hxx>
#include <gp_Ax1.hxx>
#include <HydStatic_Module.hxx>
#include <HydStatic_CurveMakerType.hxx>
#include <Global_Serialization.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Geo_xDistb;
	class Marine_Body;
	class Marine_Domain;
	class Marine_Graph;
	class Marine_MultLevWaterDomain;
	class HydStatic_CrsCurve;
	class HydStatic_CrsCurvesGraph;
	class HydStatic_HeelSpacing;

	class HydStatic_CrossCurves
		: public Global_Done
	{

		/*Private Data*/

		gp_Ax1 theAx_;

		Standard_Real theVolCoeff_;

		std::shared_ptr<Marine_MultLevWaterDomain> theWaters_;

		std::shared_ptr<HydStatic_HeelSpacing> theHeels_;

		std::shared_ptr<HydStatic_CrsCurvesGraph> theCrossCurves_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbHydStatic_EXPORT);


		auto& ChangeCrossCurves()
		{
			return theCrossCurves_;
		}

	public:

		static TnbHydStatic_EXPORT const gp_Ax1 null;
		static TnbHydStatic_EXPORT const Standard_Integer DEFAULT_NB_WATERS;

		static TnbHydStatic_EXPORT unsigned short verbose;

		TnbHydStatic_EXPORT HydStatic_CrossCurves();

		TnbHydStatic_EXPORT HydStatic_CrossCurves
		(
			const std::shared_ptr<Marine_MultLevWaterDomain>& theWaters,
			const std::shared_ptr<HydStatic_HeelSpacing>& theHeels,
			const gp_Ax1& theAx
		);


		const auto& Waters() const
		{
			return theWaters_;
		}

		const auto& Heels() const
		{
			return theHeels_;
		}

		const auto& Ax() const
		{
			return theAx_;
		}

		const auto& CrossCurves() const
		{
			return theCrossCurves_;
		}

		TnbHydStatic_EXPORT void Perform
		(
			const hydStcLib::CurveMakerType t = hydStcLib::CurveMakerType::starboard
		);

		void LoadWaters
		(
			const std::shared_ptr<Marine_MultLevWaterDomain>& theWaters
		)
		{
			theWaters_ = theWaters;
		}

		void LoadHeels
		(
			const std::shared_ptr<HydStatic_HeelSpacing>& theHeels
		)
		{
			theHeels_ = theHeels;
		}

		void SetAx(const gp_Ax1& theAx)
		{
			theAx_ = theAx;
		}

		void TnbHydStatic_EXPORT SetVolumeCoeff(const Standard_Real x);


		static TnbHydStatic_EXPORT std::shared_ptr<Geo_xDistb>
			Z
			(
				const Standard_Real theZ0,
				const Standard_Real theZ1,
				const Standard_Integer theN
			);
	};
}

#endif // !_HydStatic_CrossCurves_Header
