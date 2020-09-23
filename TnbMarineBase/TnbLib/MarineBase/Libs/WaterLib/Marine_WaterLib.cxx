#include <Marine_WaterLib.hxx>

#include <Pnt3d.hxx>
#include <Geo_xDistb.hxx>
#include <Entity3d_Box.hxx>
#include <Pln_Curve.hxx>
#include <Pln_Tools.hxx>
#include <Cad_Tools.hxx>
#include <Cad2d_Plane.hxx>
#include <Marine_Wave.hxx>
#include <Marine_WaterCurve.hxx>
#include <Marine_xCmpSection.hxx>
#include <Marine_CmpSection.hxx>
#include <Marine_Section.hxx>
#include <Marine_WaterDomain_Still.hxx>
#include <Marine_Domain.hxx>
#include <Marine_MultLevWaterDomain.hxx>
#include <Marine_WaterTools.hxx>
#include <Marine_BodyTools.hxx>
#include <Marine_SectTools.hxx>
#include <Marine_Sections.hxx>
#include <Marine_Bodies.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#ifdef DebugInfo
#undef DebugInfo
#endif

#include <gp_Ax2.hxx>
#include <gp_Pln.hxx>
#include <GeomProjLib.hxx>
#include <Geom_Curve.hxx>
#include <Geom_Plane.hxx>
#include <Geom_Line.hxx>
#include <Geom_TrimmedCurve.hxx>
#include <GeomAPI_ProjectPointOnCurve.hxx>
#include <BRepAlgoAPI_Section.hxx>
#include <BRep_Tool.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Shape.hxx>

#include <vector>

std::shared_ptr<tnbLib::Marine_WaterDomain> 
tnbLib::Marine_WaterLib::StillWaterDomain
(
	const marineLib::Body_Displacer& theBody,
	const std::shared_ptr<Marine_Domain>& theDomain,
	const Standard_Real theZ	
)
{
#ifdef _DEBUG
	Marine_BodyTools::CheckTypeConsistency(theBody);
#endif // _DEBUG

	auto wd = std::make_shared<marineLib::WaterDomain_Still>(theDomain, theZ);
	Debug_Null_Pointer(wd);

	auto sections = 
		Marine_WaterTools::StillWaterSections(theBody.Sections(), theZ, theDomain->Dim());
	wd->ChangeWaters() = std::move(sections);
	return std::move(wd);
}

std::shared_ptr<tnbLib::Marine_WaterDomain> 
tnbLib::Marine_WaterLib::StillWaterDomain
(
	const marineLib::Body_Tank & theBody, 
	const std::shared_ptr<Marine_Domain>& theDomain,
	const Standard_Real theZ
)
{
#ifdef _DEBUG
	Marine_BodyTools::CheckTypeConsistency(theBody);
#endif // _DEBUG

	auto wd = std::make_shared<marineLib::WaterDomain_Still>(theDomain, theZ);
	Debug_Null_Pointer(wd);

	auto sections =
		Marine_WaterTools::StillWaterSections(theBody.Sections(), theZ, theDomain->Dim());
	wd->ChangeWaters() = std::move(sections);
	return std::move(wd);
}

std::shared_ptr<tnbLib::Marine_MultLevWaterDomain> 
tnbLib::Marine_WaterLib::MultiLevelsStillWaterDomain
(
	const marineLib::Body_Displacer & theBody,
	const std::shared_ptr<Marine_Domain>& theDomain,
	const Geo_xDistb & theZ
)
{
	auto domain = std::make_shared<Marine_MultLevWaterDomain>();
	Debug_Null_Pointer(domain);

	std::vector<std::shared_ptr<Marine_WaterDomain>> domains;
	domains.reserve(theZ.Size());
	for (auto z : theZ.Values())
	{
		auto water = StillWaterDomain(theBody, theDomain, z);
		Debug_Null_Pointer(water);

		domains.push_back(std::move(water));
	}

	domain->SetDomains(std::move(domains));
	return std::move(domain);
}

const std::shared_ptr<tnbLib::Marine_CmpSection> &
tnbLib::Marine_WaterLib::FUW
(
	const marineLib::Body_Wetted& theBody
)
{
	const auto& sections = theBody.Sections();
	if (sections.empty())
	{
		FatalErrorIn
		(
			"const std::shared_ptr<tnbLib::Marine_CmpSection> & FUW()"
		)
			<< "null list" << endl
			<< abort(FatalError);
	}
	return sections[sections.size() - 1];
}

const std::shared_ptr<tnbLib::Marine_CmpSection> &
tnbLib::Marine_WaterLib::AUW
(
	const marineLib::Body_Wetted& theBody
)
{
	const auto& sections = theBody.Sections();
	if (sections.empty())
	{
		FatalErrorIn
		(
			"const std::shared_ptr<tnbLib::Marine_CmpSection> & AUW()"
		)
			<< "null list" << endl
			<< abort(FatalError);
	}
	return sections[0];
}

const std::shared_ptr<tnbLib::Marine_CmpSection> &
tnbLib::Marine_WaterLib::FWL
(
	const marineLib::Body_Wetted& theBody
)
{
	const auto& sections = theBody.Sections();
	if (sections.size() < 3)
	{
		FatalErrorIn(FunctionSIG)
			<< "there must be more than 2 section for a valid body" << endl
			<< abort(FatalError);
	}
	for (size_t i = sections.size() - 1; i >= 0; i--)
	{
		const auto& x = sections[i];
		Debug_Null_Pointer(x);

		auto wls = Marine_WaterTools::RetrieveNonDeepWLs(*x);
		if (wls.size())
		{
			return x;
		}
	}
	return Marine_CmpSection::null;
}

const std::shared_ptr<tnbLib::Marine_CmpSection> &
tnbLib::Marine_WaterLib::AWL
(
	const marineLib::Body_Wetted& theBody
)
{
	const auto& sections = theBody.Sections();
	if (sections.size() < 3)
	{
		FatalErrorIn(FunctionSIG)
			<< "there must be more than 2 section for a valid body" << endl
			<< abort(FatalError);
	}
	for (const auto& x : sections)
	{
		Debug_Null_Pointer(x);

		auto wls = Marine_WaterTools::RetrieveNonDeepWLs(*x);
		if (wls.size())
		{
			return x;
		}
	}
	return Marine_CmpSection::null;
}