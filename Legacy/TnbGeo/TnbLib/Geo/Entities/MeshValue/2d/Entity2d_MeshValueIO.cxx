#include <Entity2d_MeshValue.hxx>

#include <Entity2d_Box.hxx>
#include <Entity2d_Triangulation.hxx>
#include <Global_Tools.hxx>
#include <TecPlot.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	template<>
	template<>
	void Entity2d_MeshValue::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar, 
			const unsigned int /*file_version*/
			)
	{
		ar & theMesh_;
		ar & theValues_;
	}

	template<>
	template<>
	void Entity2d_MeshValue::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar, 
			const unsigned int /*file_version*/
			)
	{
		ar & theMesh_;
		ar & theValues_;
	}
}

void tnbLib::geoLib::ExportToPlt
(
	const Entity2d_MeshValue& theMesh,
	OFstream& theFile,
	const word& name
)
{
	if (NOT theMesh.Mesh())
	{
		FatalErrorIn(FunctionSIG)
			<< "no triangulation has been found." << endl
			<< abort(FatalError);
	}
	const auto& pts = theMesh.Mesh()->Points();
	const auto& ids = theMesh.Mesh()->Connectivity();
	const auto field = 
		Global_Tools::ConvertToArrayField<Standard_Real, Standard_Real, 1>
		(theMesh.Values());

	Io::ExportField(name, field, pts, ids, theFile);
}