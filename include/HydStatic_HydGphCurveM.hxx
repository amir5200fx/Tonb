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
																												\
		CLASS_NAME() {}																							\
																												\
																												\
		friend class boost::serialization::access;																\
																												\
		template<class Archive>																					\
		void serialize(Archive& ar, const unsigned int /*file_version*/)										\
		{																										\
			ar & boost::serialization::base_object<HydStatic_HydGphCurve>(*this);								\
		}																										\
																												\
																												\
																												\
	public:																										\
		CLASS_NAME(const Handle(Geom2d_Curve)& theCurve)														\
			: HydStatic_HydGphCurve(theCurve)																	\
		{}																										\
																												\
																												\
		CLASS_NAME(Handle(Geom2d_Curve)&& theCurve)																\
			: HydStatic_HydGphCurve(std::move(theCurve))														\
		{}																										\
																												\
		CLASS_NAME(const Standard_Integer theIndex, const word& theName, const Handle(Geom2d_Curve)& theCurve)	\
			: HydStatic_HydGphCurve(theIndex, theName, theCurve)												\
		{}																										\
																												\
		CLASS_NAME(const Standard_Integer theIndex, const word& theName, Handle(Geom2d_Curve)&& theCurve)		\
			: HydStatic_HydGphCurve(theIndex, theName, std::move(theCurve))										\
		{}																										\
																												\
		static std::shared_ptr<CLASS_NAME> Curve(const std::vector<xDraft>&);									\
	};


#endif // !_HydStatic_HydGphCurveM_Header
