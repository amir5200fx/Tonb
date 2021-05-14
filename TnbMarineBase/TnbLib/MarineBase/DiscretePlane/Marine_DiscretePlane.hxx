#pragma once
#ifndef _Marine_DiscretePlane_Header
#define _Marine_DiscretePlane_Header

#include <Global_Done.hxx>
#include <Entity2d_ChainFwd.hxx>
#include <Marine_Module.hxx>

#include <memory>

namespace tnbLib
{

	//- Forward Declarations
	class Cad2d_Plane;
	class Geo_ApprxCurve_Info;

	class Marine_DiscretePlane
		: public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<Cad2d_Plane> thePlane_;
		std::shared_ptr<Geo_ApprxCurve_Info> theInfo_;

		std::shared_ptr<Entity2d_Chain> theChain_;

	public:

		static TnbMarine_EXPORT const std::shared_ptr<Geo_ApprxCurve_Info> gl_approx_curve_info;
		static TnbMarine_EXPORT void gl_approx_curve_info_init();

		//- default constructor

		Marine_DiscretePlane()
			: theInfo_(gl_approx_curve_info)
		{}



		//- public functions and operators

		const auto& Plane() const
		{
			return thePlane_;
		}

		const auto& ApproxCurveInfo() const
		{
			return theInfo_;
		}

		const auto& Chain() const
		{
			return theChain_;
		}

		TnbMarine_EXPORT void Perform();

		void LoadPlane(const std::shared_ptr<Cad2d_Plane>& thePlane)
		{
			thePlane_ = thePlane;
		}

		void LoadApproxCurveInfo(const std::shared_ptr<Geo_ApprxCurve_Info>& theInfo)
		{
			theInfo_ = theInfo;
		}

	};
}

#endif // !_Marine_DiscretePlane_Header
