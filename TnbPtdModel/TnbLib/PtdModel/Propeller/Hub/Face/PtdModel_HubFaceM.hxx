#pragma once
#ifndef _PtdModel_HubFaceM_Header
#define _PtdModel_HubFaceM_Header

#include <PtdModel_HubFace.hxx>

#define HubFaceClass(Class_Name)														\
	class Class_Name																	\
		: public PtdModel_HubFace														\
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
			ar & boost::serialization::base_object<PtdModel_HubFace>(*this);			\
		}																				\
																						\
		public:																			\
																						\
			/*default constructor*/														\
																						\
			Class_Name() {}																\
																						\
			Class_Name(const Handle(Geom_Surface)& theSurface)							\
				: PtdModel_HubFace(theSurface)											\
			{}																			\
																						\
			Class_Name(Handle(Geom_Surface)&& theSurface)								\
				: PtdModel_HubFace(std::move(theSurface))								\
			{}																			\
																						\
	}

#endif // !_PtdModel_HubFaceM_Header
