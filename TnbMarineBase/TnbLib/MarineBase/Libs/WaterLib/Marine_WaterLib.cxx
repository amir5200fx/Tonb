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
#include <Marine_Water.hxx>
#include <Marine_WaterDomain.hxx>
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

std::shared_ptr<tnbLib::Marine_Domain>
tnbLib::Marine_WaterLib::Domain
(
	const marineLib::Body_Displacer & theBody
)
{
	auto domain = std::make_shared<Marine_Domain>();
	Debug_Null_Pointer(domain);

	domain->Perform(theBody.Sections());
	return std::move(domain);
}

std::shared_ptr<tnbLib::Marine_Domain> 
tnbLib::Marine_WaterLib::Domain
(
	const marineLib::Body_Tank & theBody
)
{
	auto domain = std::make_shared<Marine_Domain>();
	Debug_Null_Pointer(domain);

	domain->Perform(theBody.Sections());
	return std::move(domain);
}

//std::shared_ptr<tnbLib::Marine_Water> 
//tnbLib::Marine_WaterLib::StillWater
//(
//	const Marine_Body& theBody, 
//	const Marine_Domain& theDomain, 
//	const Standard_Real theZ
//)
//{
//	if (theBody.IsSail())
//	{
//		FatalErrorIn(FunctionSIG)
//			<< "the body must be hull or tank" << endl
//			<< abort(FatalError);
//	}
//
//#ifdef _DEBUG
//	Marine_BodyTools::CheckTypeConsistency(theBody);
//#endif // _DEBUG
//
//	Debug_Null_Pointer(theDomain.Dim());
//	auto water = 
//		Marine_WaterTools::StillWater
//		(
//			theBody.Sections(),
//			theZ, *theDomain.Dim()
//		);
//	Debug_Null_Pointer(water);
//	return std::move(water);
//}

std::shared_ptr<tnbLib::Marine_WaterDomain> 
tnbLib::Marine_WaterLib::StillWaterDomain
(
	const std::shared_ptr<Marine_Body>& theBody, 
	const std::shared_ptr<Marine_Domain>& theDomain, 
	const Standard_Real theZ
)
{
	if (theBody->IsHull())
	{
		auto body = std::dynamic_pointer_cast<marineLib::Body_Displacer>(theBody);
		if (NOT body)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< "the body type is not displacer" << endl
				<< abort(FatalError);
		}

		auto water = StillWaterDomain(*body, theDomain, theZ);
		return std::move(water);
	}
	else if (theBody->IsTank())
	{
		auto body = std::dynamic_pointer_cast<marineLib::Body_Tank>(theBody);
		Debug_Null_Pointer(body);

		auto water = StillWaterDomain(*body, theDomain, theZ);
		return std::move(water);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid body type has been detected: Sail" << endl
			<< abort(FatalError);
		return nullptr;
	}
}

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


	auto wave = Marine_WaterTools::FlatWave(theDomain, theZ);
	Debug_Null_Pointer(wave);

	wave->Perform();
	Debug_If_Condition_Message(NOT wave->IsDone(), "the wave is not created!");

	auto water = 
		Marine_WaterTools::StillWater(theBody.Sections(), theZ, *theDomain->Dim());

	auto wd = std::make_shared<Marine_WaterDomain>
		(
			std::move(water),
			std::move(wave)
			);
	wd->SetZ(theZ);
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

	auto wave = Marine_WaterTools::FlatWave(theDomain, theZ);
	Debug_Null_Pointer(wave);

	auto water =
		Marine_WaterTools::StillWater(theBody.Sections(), theZ, *theDomain->Dim());

	auto wd = 
		std::make_shared<Marine_WaterDomain>
		(
			std::move(water), 
			std::move(wave)
			);
	wd->SetZ(theZ);
	return std::move(wd);
}

std::shared_ptr<tnbLib::Marine_MultLevWaterDomain> 
tnbLib::Marine_WaterLib::MultiLevelsStillWaterDomain
(
	const std::shared_ptr<Marine_Body>& theBody,
	const std::shared_ptr<Marine_Domain>& theDomain,
	const Geo_xDistb & theZ
)
{
	if (theBody->IsHull())
	{
		auto body = std::dynamic_pointer_cast<marineLib::Body_Displacer>(theBody);
		if (NOT body)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< "the body type is not displacer" << endl
				<< abort(FatalError);
		}

		auto domain = MultiLevelsStillWaterDomain(*body, theDomain, theZ);
		return std::move(domain);
	}
	else if (theBody->IsTank())
	{
		auto body = std::dynamic_pointer_cast<marineLib::Body_Tank>(theBody);
		Debug_Null_Pointer(body);

		auto domain = MultiLevelsStillWaterDomain(*body, theDomain, theZ);
		return std::move(domain);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid body type has been detected: Sail" << endl
			<< abort(FatalError);
		return nullptr;
	}
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

	domain->SetWaters(std::move(domains));
	domain->SetDomain(theDomain);
	domain->SetBody(std::dynamic_pointer_cast<Marine_Body>(theBody.This()));
	return std::move(domain);
}

std::shared_ptr<tnbLib::Marine_MultLevWaterDomain> 
tnbLib::Marine_WaterLib::MultiLevelsStillWaterDomain
(
	const marineLib::Body_Tank & theBody,
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

	domain->SetWaters(std::move(domains));
	domain->SetDomain(theDomain);
	domain->SetBody(std::dynamic_pointer_cast<Marine_Body>(theBody.This()));
	return std::move(domain);
}

std::shared_ptr<tnbLib::Marine_WaterDomain> 
tnbLib::Marine_WaterLib::WaterDomain
(
	const std::shared_ptr<Marine_Body>& theBody, 
	const std::shared_ptr<Marine_Wave> & theWave,
	const std::shared_ptr<Marine_Domain>& theDomain, 
	const Standard_Real theMinTol, 
	const Standard_Real theMaxTol
)
{
	if (theBody->IsHull())
	{
		auto body = std::dynamic_pointer_cast<marineLib::Body_Displacer>(theBody);
		if (NOT body)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< "the body type is not displacer" << endl
				<< abort(FatalError);
		}

		auto domain = WaterDomain(*body, theWave, theDomain, theMinTol, theMaxTol);
		return std::move(domain);
	}
	else if (theBody->IsTank())
	{
		auto body = std::dynamic_pointer_cast<marineLib::Body_Tank>(theBody);
		Debug_Null_Pointer(body);

		auto domain = WaterDomain(*body, theWave, theDomain, theMinTol, theMaxTol);
		return std::move(domain);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid body type has been detected: Sail" << endl
			<< abort(FatalError);
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Marine_WaterDomain> 
tnbLib::Marine_WaterLib::WaterDomain
(
	const marineLib::Body_Displacer & theBody,
	const std::shared_ptr<Marine_Wave> & theWave,
	const std::shared_ptr<Marine_Domain>& theDomain,
	const Standard_Real theMinTol, 
	const Standard_Real theMaxTol
)
{
#ifdef _DEBUG
	Marine_BodyTools::CheckTypeConsistency(theBody);
#endif // _DEBUG

	auto water = 
		Marine_WaterTools::Water
		(
			theBody.Sections(), 
			theWave, *theDomain->Dim(), 
			theMinTol, theMaxTol
		);
	Debug_Null_Pointer(water);

	auto wave = theWave;
	auto wd =
		std::make_shared<Marine_WaterDomain>
		(
			std::move(water),
			std::move(wave)
			);
	wd->SetZ(theWave->Z());
	return std::move(wd);
}

std::shared_ptr<tnbLib::Marine_WaterDomain> 
tnbLib::Marine_WaterLib::WaterDomain
(
	const marineLib::Body_Tank & theBody, 
	const std::shared_ptr<Marine_Wave>& theWave, 
	const std::shared_ptr<Marine_Domain>& theDomain, 
	const Standard_Real theMinTol, 
	const Standard_Real theMaxTol
)
{
#ifdef _DEBUG
	Marine_BodyTools::CheckTypeConsistency(theBody);
#endif // _DEBUG

	auto water =
		Marine_WaterTools::Water
		(
			theBody.Sections(),
			theWave, *theDomain->Dim(),
			theMinTol, theMaxTol
		);
	Debug_Null_Pointer(water);

	auto wave = theWave;
	auto wd =
		std::make_shared<Marine_WaterDomain>
		(
			std::move(water),
			std::move(wave)
			);
	wd->SetZ(theWave->Z());
	return std::move(wd);
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