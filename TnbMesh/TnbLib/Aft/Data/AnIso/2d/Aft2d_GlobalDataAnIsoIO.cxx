#include <Aft2d_GlobalDataAnIso.hxx>

#include <Aft2d_NodeAnIso.hxx>
#include <Aft2d_ElementAnIso.hxx>
#include <Mesh_QualityMap.hxx>

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh_RegisterElement<tnbLib::Aft2d_ElementAnIso>)
{
	ar & theElements_;
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh_RegisterElement<tnbLib::Aft2d_ElementAnIso>)
{
	ar & theElements_;
}

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Aft2d_GlobalDataAnIso)
{
	ar & boost::serialization::base_object<Mesh_NamedEntity>(*this);
	ar & boost::serialization::base_object<Mesh_RegisterElement<Aft2d_ElementAnIso>>(*this);

	ar & theQuality_;
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Aft2d_GlobalDataAnIso)
{
	ar & boost::serialization::base_object<Mesh_NamedEntity>(*this);
	ar & boost::serialization::base_object<Mesh_RegisterElement<Aft2d_ElementAnIso>>(*this);

	ar & theQuality_;
}