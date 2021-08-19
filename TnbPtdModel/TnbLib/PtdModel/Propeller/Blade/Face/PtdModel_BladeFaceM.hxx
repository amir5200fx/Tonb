#pragma once
#ifndef _PtdModel_BladeFaceM_Header
#define _PtdModel_BladeFaceM_Header

#include <PtdModel_BladeFace.hxx>

#define BladeFaceClass(Class_Name)														\
	class Class_Name																	\
		: public PtdModel_BladeFace														\
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
			ar & boost::serialization::base_object<PtdModel_BladeFace>(*this);			\
		}																				\
																						\
		public:																			\
																						\
			/*default constructor*/														\
																						\
			Class_Name() {}																\
																						\
			Class_Name(const Handle(Geom_Surface)& theSurface)							\
				: PtdModel_BladeFace(theSurface)										\
			{}																			\
																						\
			Class_Name(Handle(Geom_Surface)&& theSurface)								\
				: PtdModel_BladeFace(std::move(theSurface))								\
			{}																			\
																						\
	}

#endif // !_PtdModel_BladeFaceM_Header
