#include <GeoMesh3d_Data.hxx>

#include <Entity3d_Tetrahedralization.hxx>
#include <TecPlot.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	template<>
	template<>
	void GeoMesh3d_Data::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int /*file_vertion*/
			)
	{
		ar & theElements_;
	}

	template<>
	template<>
	void GeoMesh3d_Data::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int /*file_vertion*/
			)
	{
		ar & theElements_;
	}
}

template<>
void tnbLib::GeoMesh3d_Data::ExportToPlt(OFstream& file) const
{
	auto tets = StaticData();
	Debug_Null_Pointer(tets);
	tets->ExportToPlt(file);
}