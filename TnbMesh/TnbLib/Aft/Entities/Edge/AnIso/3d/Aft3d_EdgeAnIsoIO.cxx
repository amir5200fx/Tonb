#include <Aft3d_EdgeAnIso.hxx>

#include <Aft3d_NodeAnIso.hxx>

namespace tnbLib
{

	template<>
	template<>
	void Mesh_Edge<Aft3d_EdgeAnIsoTraits>::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int file_version
			)
	{
		ar & boost::serialization::base_object<Mesh_Entity>(*this);
		ar & boost::serialization::base_object<edgeAdaptor>(*this);
		ar & theNodes_;
	}

	template<>
	template<>
	void Mesh_Edge<Aft3d_EdgeAnIsoTraits>::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int file_version
			)
	{
		ar & boost::serialization::base_object<Mesh_Entity>(*this);
		ar & boost::serialization::base_object<edgeAdaptor>(*this);
		ar & theNodes_;
	}
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Aft3d_EdgeAnIso);