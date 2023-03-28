#include <Aft2d_AltrOptNodeSurface_DE.hxx>

#include <Aft2d_AltrOptNodeSurface_DE_Info.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Aft2d_AltrOptNodeSurface_DE)
{
	ar& boost::serialization::base_object<Aft2d_AltrOptNodeSurface>(*this);
	ar& theUV0_;
	ar& theUV1_;
	ar& theInfo_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Aft2d_AltrOptNodeSurface_DE)
{
	ar& boost::serialization::base_object<Aft2d_AltrOptNodeSurface>(*this);
	ar& theUV0_;
	ar& theUV1_;
	ar& theInfo_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Aft2d_AltrOptNodeSurface_DE);