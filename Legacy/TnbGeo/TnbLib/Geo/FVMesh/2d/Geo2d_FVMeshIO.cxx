#include <Geo2d_FVMesh.hxx>

#include <Geo_ElemGeom.hxx>
#include <Entity2d_CmpConnect.hxx>
#include <TecPlot.hxx>

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

template <>
void tnbLib::Geo2d_FVMesh::ExportToPlt(OFstream& theFile) const
{
	std::vector<std::shared_ptr<Entity2d_CmpConnect>> tot_ids;
	tot_ids.reserve(theElements_.size());
	for (const auto& x:theElements_)
	{
		Debug_Null_Pointer(x);
		auto ids = Geo_ElemGeom::Convert2d(*x);
		tot_ids.emplace_back(std::move(ids));
	}
	Io::ExportMesh(Coordinates(), tot_ids, theFile);
}