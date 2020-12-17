#pragma once
#ifndef _HydStatic_CrossCurves_Header
#define _HydStatic_CrossCurves_Header

#include <Global_Done.hxx>
#include <gp_Ax1.hxx>
#include <HydStatic_Module.hxx>
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
	class HydStatic_CrsCurve;
	class HydStatic_Spacing;

	class HydStatic_CrossCurves
		: public Global_Done
	{

		/*Private Data*/

		gp_Ax1 theAx_;

		Standard_Integer theNbWaters_;

		std::shared_ptr<Marine_Domain> theDomain_;
		std::shared_ptr<Marine_Body> theBody_;

		std::shared_ptr<HydStatic_Spacing> theHeels_;

		std::vector<std::shared_ptr<HydStatic_CrsCurve>> theCrossCurves_;

		std::shared_ptr<Marine_Graph> theGraph_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbHydStatic_EXPORT);


		auto& ChangeGraph()
		{
			return theGraph_;
		}

		auto& ChangeCrossCurves()
		{
			return theCrossCurves_;
		}

	public:

		static TnbHydStatic_EXPORT const gp_Ax1 null;
		static TnbHydStatic_EXPORT const Standard_Integer DEFAULT_NB_WATERS;

		TnbHydStatic_EXPORT HydStatic_CrossCurves();

		TnbHydStatic_EXPORT HydStatic_CrossCurves
		(
			const std::shared_ptr<Marine_Domain>& theDomain, 
			const std::shared_ptr<Marine_Body>& theBody, 
			const std::shared_ptr<HydStatic_Spacing>& theHeels,
			const Standard_Integer theNbWaters,
			const gp_Ax1& theAx
		);


		const auto& Domain() const
		{
			return theDomain_;
		}

		const auto& Body() const
		{
			return theBody_;
		}

		const auto& Heels() const
		{
			return theHeels_;
		}

		auto NbWaters() const
		{
			return theNbWaters_;
		}

		const auto& Graph() const
		{
			return theGraph_;
		}

		const auto& Ax() const
		{
			return theAx_;
		}

		const auto& CrossCurves() const
		{
			return theCrossCurves_;
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

		void LoadHeels(const std::shared_ptr<HydStatic_Spacing>& theHeels)
		{
			theHeels_ = theHeels;
		}

		void SetNbWaters(const Standard_Integer theNbWaters)
		{
			theNbWaters_ = theNbWaters;
		}

		void SetAx(const gp_Ax1& theAx)
		{
			theAx_ = theAx;
		}


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
