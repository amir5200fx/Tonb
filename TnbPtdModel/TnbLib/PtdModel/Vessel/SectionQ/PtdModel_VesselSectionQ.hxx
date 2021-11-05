#pragma once
#ifndef _PtdModel_VesselSectionQ_Header
#define _PtdModel_VesselSectionQ_Header

#include <Pnt3d.hxx>

#include <vector>

namespace tnbLib
{

	class PtdModel_VesselSectionQ
	{

		/*Private Data*/

		std::vector<Pnt3d> thePoints_;

	public:

		//- default constructor

		PtdModel_VesselSectionQ()
		{}


		//- constructors

		PtdModel_VesselSectionQ(const std::vector<Pnt3d>& thePts)
			: thePoints_(thePts)
		{}

		PtdModel_VesselSectionQ(std::vector<Pnt3d>&& thePts)
			: thePoints_(std::move(thePts))
		{}


		//- public functions and operators

		const auto& Points() const
		{
			return thePoints_;
		}

		auto& PointsRef()
		{
			return thePoints_;
		}

		virtual Standard_Boolean HasCorner() const
		{
			return Standard_False;
		}

	};


	class PtdModel_CorneredVesselSectionQ
		: public PtdModel_VesselSectionQ
	{

		/*Private Data*/

		Standard_Integer theCorner_;

	public:

		//- default constructor

		PtdModel_CorneredVesselSectionQ()
			: theCorner_(0)
		{}

		//- constructors

		PtdModel_CorneredVesselSectionQ(const std::vector<Pnt3d>& thePts)
			: PtdModel_VesselSectionQ(thePts)
			, theCorner_(0)
		{}

		PtdModel_CorneredVesselSectionQ(std::vector<Pnt3d>&& thePts)
			: PtdModel_VesselSectionQ(std::move(thePts))
			, theCorner_(0)
		{}


		//- public functions and operators

		Standard_Boolean HasCorner() const override
		{
			return Standard_False;
		}

	};
}

#endif // !_PtdModel_VesselSectionQ_Header
