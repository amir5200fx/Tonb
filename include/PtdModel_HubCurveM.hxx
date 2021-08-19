#pragma once
#ifndef _PtdModel_HubCurveM_Header
#define _PtdModel_HubCurveM_Header

#include <PtdModel_HubCurve.hxx>

#define HubCurveClass(Class_Name)														\
	class Class_Name																	\
		: public PtdModel_HubCurve														\
	{																					\
																						\
		/*Private Data*/																\
																						\
																						\
		friend class boost::serialization::access;										\
																						\
		template<class Archive>															\
		void serialize(Archive& ar, const unsigned int /*file_version*/)				\
		{																				\
			ar & boost::serialization::base_object<PtdModel_HubCurve>(*this);			\
		}																				\
																						\
		public:																			\
																						\
			/*default constructor*/														\
																						\
			Class_Name() {}																\
																						\
			Class_Name(const Handle(Geom_Curve)& theGeometry)							\
				: PtdModel_HubCurve(theGeometry)										\
			{}																			\
																						\
			Class_Name(Handle(Geom_Curve)&& theGeometry)								\
				: PtdModel_HubCurve(std::move(theGeometry))								\
			{}																			\
																						\
	}

#endif // !_PtdModel_HubCurveM_Header
