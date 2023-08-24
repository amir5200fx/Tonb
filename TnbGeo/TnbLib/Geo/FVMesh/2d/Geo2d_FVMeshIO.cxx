#include <Geo2d_FVMesh.hxx>

#include <Geo_ElemGeom.hxx>

template<>
template<>
void tnbLib::Geo2d_FVMesh::Boundary::serialize<TNB_iARCH_TYPE>
(
	TNB_iARCH_TYPE& ar, 
	const unsigned int file_version
)
{
	ar& boost::serialization::base_object<Global_Named>(*this);
	ar& theType_;
	ar& theElements_;
}

template<>
template<>
void tnbLib::Geo2d_FVMesh::Boundary::serialize<TNB_oARCH_TYPE>
(
	TNB_oARCH_TYPE& ar,
	const unsigned int file_version
)
{
	ar& boost::serialization::base_object<Global_Named>(*this);
	ar& theType_;
	ar& theElements_;
}

template<>
template<>
void tnbLib::Geo2d_FVMesh::serialize<TNB_iARCH_TYPE>
(
	TNB_iARCH_TYPE& ar,
	const unsigned int file_version
)
{
	ar& boost::serialization::base_object<Global_Named>(*this);
	
	ar& theCoords_;
	ar& theElements_;
	ar& theBoundaries_;

	ar& theGroups_;
}

template<>
template<>
void tnbLib::Geo2d_FVMesh::serialize<TNB_oARCH_TYPE>
(
	TNB_oARCH_TYPE& ar,
	const unsigned int file_version
)
{
	ar& boost::serialization::base_object<Global_Named>(*this);

	ar& theCoords_;
	ar& theElements_;
	ar& theBoundaries_;

	ar& theGroups_;
}