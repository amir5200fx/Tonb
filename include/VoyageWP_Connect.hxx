#pragma once
#ifndef _VoyageWP_Connect_Header
#define _VoyageWP_Connect_Header

#include <Global_Done.hxx>

#include <memory>

namespace tnbLib
{

	//- Forward Declarations
	class VoyageGeo_Earth;
	class VoyageWP_Net;
	class Mesh_Curve_Info;
	class Geo_MetricPrcsrAnIso_Info;

	class VoyageWP_Connect
		: public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<VoyageWP_Net> theNet_;
		std::shared_ptr<VoyageGeo_Earth> theEarth_;

		std::shared_ptr<Mesh_Curve_Info> theCurveInfo_;
		std::shared_ptr<Geo_MetricPrcsrAnIso_Info> theMetricInfo_;

		Standard_Real theAngle_;

		Standard_Integer theMaxSubLev_;

	public:

		//- the maximum allowable subdivision level
		static Standard_Integer DEFAULT_SUB_LEV;

		//- default constructor

		VoyageWP_Connect()
			: theAngle_(0)
			, theMaxSubLev_(DEFAULT_SUB_LEV)
		{}

		//- constructors

		//- Public functions and operators

		const auto& Net() const { return theNet_; }
		const auto& Earth() const { return theEarth_; }
		auto Angle() const { return theAngle_; }
		auto MaxSubLev() const { return theMaxSubLev_; }

		const auto& CurveInfo() const { return theCurveInfo_; }
		const auto& MetricInfo() const { return theMetricInfo_; }

		void Perform();

		void SetNet(const std::shared_ptr<VoyageWP_Net>& theNet) { theNet_ = theNet; }
		void SetAngle(const Standard_Real theAngle) { theAngle_ = theAngle; }
		void SetEarth(const std::shared_ptr<VoyageGeo_Earth>& theEarth) { theEarth_ = theEarth; }

		void SetCurveInfo(const std::shared_ptr<Mesh_Curve_Info>& theInfo) { theCurveInfo_ = theInfo; }
		void SetMetricInfo(const std::shared_ptr<Geo_MetricPrcsrAnIso_Info>& theInfo) { theMetricInfo_ = theInfo; }

		void SetMaxSubLev(const Standard_Integer theLev) { theMaxSubLev_ = theLev; }
	};

}

#endif // !_VoyageWP_Connect_Header
