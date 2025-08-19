#pragma once
#ifndef _Cad2d_Plane_Info_Header
#define _Cad2d_Plane_Info_Header

#include <Cad2d_Module.hxx>
#include <Global_AccessMethod.hxx>
#include <Global_TypeDef.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class Geo_ApprxCurve_Info;

	class Cad2d_Plane_Info
	{

		/*Private Data*/

		Standard_Real theTolerance_;

		std::shared_ptr<Geo_ApprxCurve_Info> theApprxInfo_;

	public:

		static TnbCad2d_EXPORT const Standard_Real DEFAULT_TOLERANCE;

		Cad2d_Plane_Info()
			: theTolerance_(DEFAULT_TOLERANCE)
		{}


		const auto& ApproxInfo() const
		{
			return theApprxInfo_;
		}

		void OverrideApproxInfo(const std::shared_ptr<Geo_ApprxCurve_Info>& theInfo)
		{
			theApprxInfo_ = theInfo;
		}

		//- Macros
		GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, Tolerance)
	};
}

#endif // !_Cad2d_Plane_Info_Header
