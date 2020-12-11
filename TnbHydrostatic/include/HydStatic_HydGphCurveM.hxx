#pragma once
#ifndef _HydStatic_HydGphCurveM_Header
#define _HydStatic_HydGphCurveM_Header

#include <HydStatic_HydGphCurve.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{
	namespace hydStcGphLib
	{
		struct xDraft;
	}
}

#define HYDSTATIC_HYDGRAPHCURVE(CLASS_NAME)																		\
	class CLASS_NAME																							\
		: public HydStatic_HydGphCurve																			\
	{																											\
																												\
	public:																										\
		CLASS_NAME(const Handle(Geom2d_Curve)& theCurve)														\
			: HydStatic_HydGphCurve(theCurve)																	\
		{}																										\
																												\
		CLASS_NAME(const Standard_Integer theIndex, const Handle(Geom2d_Curve)& theCurve)						\
			: HydStatic_HydGphCurve(theIndex, theCurve)															\
		{}																										\
																												\
		CLASS_NAME(const Standard_Integer theIndex, const word& theName, const Handle(Geom2d_Curve)& theCurve)	\
			: HydStatic_HydGphCurve(theIndex, theName, theCurve)												\
		{}																										\
																												\
		static std::shared_ptr<CLASS_NAME> Curve(const std::vector<xDraft>&);									\
	};


#endif // !_HydStatic_HydGphCurveM_Header
