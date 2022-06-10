#pragma once
#ifndef _Cad_MetricRepair_Header
#define _Cad_MetricRepair_Header

#include <Cad_Module.hxx>
#include <Entity2d_BoxFwd.hxx>
#include <Entity2d_TriangulationFwd.hxx>
#include <Global_Done.hxx>

#include <gp_Trsf2d.hxx>
#include <Standard_TypeDef.hxx>

class Geom_Surface;

#include <memory>

namespace tnbLib
{

	// Forward Declarations [6/6/2022 Amir]
	class NumAlg_AdaptiveInteg_Info;

	template<class SurfType>
	class Cad_MetricRepair
		: public Global_Done
	{

		/*Private Data*/


		// inputs [6/6/2022 Amir]

		std::shared_ptr<SurfType> thePatch_;	

		std::shared_ptr<Entity2d_Box> theDomain_;

		Standard_Real theCharLenU_;
		Standard_Real theCharLenV_;


		// outputs [6/6/2022 Amir]

		std::shared_ptr<SurfType> theReparameterized_;

		gp_Trsf2d theTrsf_;

		// private functions and operators [6/6/2022 Amir]	

		auto& ReparameterizedRef()
		{
			return theReparameterized_;
		}

	public:

		// default constructor [6/6/2022 Amir]

		Cad_MetricRepair()
			: theCharLenU_(0)
			, theCharLenV_(0)
		{}


		// constructors [6/6/2022 Amir]

		Cad_MetricRepair
		(
			const std::shared_ptr<SurfType>& thePatch,
			const std::shared_ptr<Entity2d_Box>& theDomain,
			const Standard_Real theCharLenU,
			const Standard_Real theCharLenV
		)
			: thePatch_(thePatch)
			, theDomain_(theDomain)
			, theCharLenU_(theCharLenU)
			, theCharLenV_(theCharLenV)
		{}


		// public functions and operators [6/6/2022 Amir]

		const auto& Patch() const
		{
			return thePatch_;
		}

		const auto& Domain() const
		{
			return theDomain_;
		}

		auto CharLenU() const
		{
			return theCharLenU_;
		}

		auto CharLenV() const
		{
			return theCharLenV_;
		}

		const auto& Reparameterized() const
		{
			return theReparameterized_;
		}

		const auto& Trsf() const
		{
			return theTrsf_;
		}

		void Perform();

		void SetPatch(const std::shared_ptr<SurfType>& thePatch)
		{
			thePatch_ = thePatch;
		}

		void SetDomain(const std::shared_ptr<Entity2d_Box>& theDomain)
		{
			theDomain_ = theDomain;
		}

		void SetCharLenU(const Standard_Real Len)
		{
			theCharLenU_ = Len;
		}

		void SetCharLenV(const Standard_Real Len)
		{
			theCharLenV_ = Len;
		}
	};
}

#endif // !_Cad_MetricRepair_Header
