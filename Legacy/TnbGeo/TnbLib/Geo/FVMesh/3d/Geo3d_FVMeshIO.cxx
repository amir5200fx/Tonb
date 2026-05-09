#include <Geo3d_FVMesh.hxx>

#include <Geo_ElemGeom.hxx>
#include <Geo_BoxTools.hxx>
#include <Entity3d_CmpConnect.hxx>
#include <TecPlot.hxx>

template<>
template<>
void tnbLib::Geo3d_FVMesh::Boundary::serialize<TNB_iARCH_TYPE>
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
void tnbLib::Geo3d_FVMesh::Boundary::serialize<TNB_oARCH_TYPE>
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
void tnbLib::Geo3d_FVMesh::serialize<TNB_iARCH_TYPE>
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
void tnbLib::Geo3d_FVMesh::serialize<TNB_oARCH_TYPE>
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
void tnbLib::Geo3d_FVMesh::ExportToPlt(OFstream& theFile) const
{
	std::vector<std::shared_ptr<Entity3d_CmpConnect>> tot_ids;
	tot_ids.reserve(theElements_.size());
	for (const auto& x : theElements_)
	{
		Debug_Null_Pointer(x);
		auto ids = Geo_ElemGeom::Convert3d(*x);
		tot_ids.emplace_back(std::move(ids));
	}
	auto b = Geo_BoxTools::GetBox(Coordinates(), 0);
	auto coords = Coordinates();
	const auto [lx, ly, lz] = b.Length();
	const auto max_l = std::max(lx, std::max(ly, lz));
	auto p0 = b.P0();//Corner(Box3d_PickAlgorithm_Aft_SW);
	p0.X() *= (max_l / lx);
	p0.Y() *= (max_l / ly);
	p0.Z() *= (max_l / lz);
	auto p1 = b.P1(); //Corner(Box3d_PickAlgorithm_Aft_SE);
	p1.X() *= (max_l / lx);
	p1.Y() *= (max_l / ly);
	p1.Z() *= (max_l / lz);
	/*auto p2 = b.Corner(Box3d_PickAlgorithm_Aft_NE);
	p2.X() *= (lx / max_l);
	p2.Y() *= (ly / max_l);
	p2.Z() *= (lz / max_l);
	auto p3 = b.Corner(Box3d_PickAlgorithm_Aft_NW);
	p3.X() *= (lx / max_l);
	p3.Y() *= (ly / max_l);
	p3.Z() *= (lz / max_l);

	auto p4 = b.Corner(Box3d_PickAlgorithm_Fwd_SW);
	p4.X() *= (lx / max_l);
	p4.Y() *= (ly / max_l);
	p4.Z() *= (lz / max_l);
	auto p5 = b.Corner(Box3d_PickAlgorithm_Fwd_SE);
	p5.X() *= (lx / max_l);
	p5.Y() *= (ly / max_l);
	p5.Z() *= (lz / max_l);
	auto p6 = b.Corner(Box3d_PickAlgorithm_Fwd_NE);
	p6.X() *= (lx / max_l);
	p6.Y() *= (ly / max_l);
	p6.Z() *= (lz / max_l);
	auto p7 = b.Corner(Box3d_PickAlgorithm_Fwd_NW);
	p7.X() *= (lx / max_l);
	p7.Y() *= (ly / max_l);
	p7.Z() *= (lz / max_l);*/
	coords.emplace_back(std::move(p0));
	coords.emplace_back(std::move(p1));
	/*coords.emplace_back(std::move(p2));
	coords.emplace_back(std::move(p3));
	coords.emplace_back(std::move(p4));
	coords.emplace_back(std::move(p5));
	coords.emplace_back(std::move(p6));
	coords.emplace_back(std::move(p7));*/
	Io::ExportMesh(coords, tot_ids, theFile);
}