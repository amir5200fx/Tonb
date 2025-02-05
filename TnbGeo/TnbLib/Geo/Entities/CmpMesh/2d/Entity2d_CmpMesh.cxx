// ReSharper disable CppClangTidyClangDiagnosticLanguageExtensionToken
#include <Entity2d_CmpMesh.hxx>

#include <Geo_BoxTools.hxx>
#include <Entity2d_QuadMesh.hxx>
#include <Entity2d_Triangulation.hxx>
#include <Entity2d_CmpConnect_Quad.hxx>
#include <Entity2d_CmpConnect_Triangle.hxx>
#include <Merge_Pnt.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include "Entity2d_CmpMesh_Helper.lxx"

#include "Entity_StaticData.hxx"
#include "Geo_Tools.hxx"

const std::string tnbLib::Entity2d_CmpMesh::extension = ".gmesh2d";

tnbLib::Entity2d_CmpMesh::Entity2d_CmpMesh(const Entity2d_CmpMesh& theMesh)
	: theCoords_(theMesh.Coords())
{
	std::vector<std::shared_ptr<Entity2d_CmpConnect>> ids;
	ids.reserve(NbElements());
	for (const auto& x : this->Indices())
	{
		auto copy = x->Copy();
		ids.emplace_back(std::move(copy));
	}
	theIndices_ = std::move(ids);
}

tnbLib::Entity2d_CmpMesh::Entity2d_CmpMesh(Entity2d_CmpMesh&& other) noexcept
	: theCoords_(std::move(other.theCoords_))
	  , theIndices_(std::move(other.theIndices_))
{
	// empty body
}

tnbLib::Entity2d_CmpMesh& 
tnbLib::Entity2d_CmpMesh::operator=(const Entity2d_CmpMesh& theMesh)
{
	if (this NOT_EQUAL & theMesh)
	{
		theCoords_ = theMesh.Coords();
		std::vector<std::shared_ptr<Entity2d_CmpConnect>> ids;
		ids.reserve(NbElements());
		for (const auto& x : this->Indices())
		{
			auto copy = x->Copy();
			ids.emplace_back(std::move(copy));
		}
		theIndices_ = std::move(ids);
	}
	return *this;
}

tnbLib::Entity2d_CmpMesh& tnbLib::Entity2d_CmpMesh::operator=(Entity2d_CmpMesh&& other) noexcept
{
	if (this != &other)
	{
		theCoords_ = std::move(other.theCoords_);
		theIndices_ = std::move(other.theIndices_);
	}
	return *this;
}

Standard_Integer
tnbLib::Entity2d_CmpMesh::NbElements() const
{
	return static_cast<Standard_Integer>(theIndices_.size());
}

std::vector<tnbLib::Pnt2d>
tnbLib::Entity2d_CmpMesh::GetElement(const Standard_Integer theIndex) const
{
	const auto& elm = theIndices_.at(theIndex);
	return elm->RetrievePolygon(Coords());
}

std::shared_ptr<tnbLib::Entity2d_Box>
tnbLib::Entity2d_CmpMesh::CalcBoundingBox() const
{
	return std::make_shared<Entity2d_Box>(Geo_BoxTools::GetBox(Coords(), 0));
}

std::shared_ptr<tnbLib::Entity2d_CmpMesh>
tnbLib::Entity2d_CmpMesh::Copy() const
{
	auto coords = Coords();
	std::vector<std::shared_ptr<Entity2d_CmpConnect>> ids;
	ids.reserve(NbElements());
	for (const auto& x: this->Indices())
	{
		auto copy = x->Copy();
		ids.emplace_back(std::move(copy));
	}
	return std::make_shared<Entity2d_CmpMesh>(std::move(coords), std::move(ids));
}

std::shared_ptr<tnbLib::Entity2d_CmpMesh> tnbLib::Entity2d_CmpMesh::Reversed() const
{
	auto copy = Copy();
	copy->Reverse();
	return copy;
}

namespace tnbLib
{
	auto MaxID(const std::vector<std::shared_ptr<Entity2d_CmpConnect>>& theIds)
	{
		auto max_id = IntegerFirst();
		for (const auto& x:theIds)
		{
			auto ids = x->Components();
			for (const auto i:ids)
			{
				if (i > max_id)
				{
					max_id = i;
				}
			}
		}
		return std::max(max_id, 0);
	}

	auto CombineConnectivities
	(
		const std::vector<std::shared_ptr<Entity2d_CmpConnect>>& theIds0, 
		const std::vector<std::shared_ptr<Entity2d_CmpConnect>>& theIds1
	)
	{
		const auto max_id = MaxID(theIds0);
		std::vector<std::shared_ptr<Entity2d_CmpConnect>> ids_tot;
		ids_tot.reserve(theIds0.size() + theIds1.size());
		for (const auto& x: theIds0)
		{
			ids_tot.emplace_back(x);
		}
		for (const auto& x:theIds1)
		{
			auto copy = x->Copy();
			if (const auto tri = std::dynamic_pointer_cast<Entity2d_CmpConnect_Triangle>(copy))
			{
				tri->Value(0) += max_id;
				tri->Value(1) += max_id;
				tri->Value(2) += max_id;
			}
			else if (const auto quad = std::dynamic_pointer_cast<Entity2d_CmpConnect_Quad>(copy))
			{
				quad->Value(0) += max_id;
				quad->Value(1) += max_id;
				quad->Value(2) += max_id;
				quad->Value(3) += max_id;
			}
			else
			{
				FatalErrorIn(FunctionSIG) << "\n"
					<< "Unable to identify the type of the element.\n"
					<< abort(FatalError);
			}
			ids_tot.emplace_back(std::move(copy));
		}
		return ids_tot;
	}
}

void tnbLib::Entity2d_CmpMesh::Add(const Entity2d_CmpMesh& theMesh)
{
	for (const auto& x:theMesh.Coords())
	{
		theCoords_.emplace_back(x);
	}
	theIndices_ = 
		CombineConnectivities(this->Indices(), theMesh.Indices());
}

void tnbLib::Entity2d_CmpMesh::Add(const Entity2d_Triangulation& theMesh)
{
	const auto mesh = Convert(theMesh);
	Add(*mesh);
}

void tnbLib::Entity2d_CmpMesh::Add(const Entity2d_QuadMesh& theMesh)
{
	const auto mesh = Convert(theMesh);
	Add(*mesh);
}

void tnbLib::Entity2d_CmpMesh::Import(const Entity2d_Triangulation& theMesh)
{
	*this = *Convert(theMesh);
}

void tnbLib::Entity2d_CmpMesh::Import(const Entity2d_QuadMesh& theMesh)
{
	*this = *Convert(theMesh);
}

void tnbLib::Entity2d_CmpMesh::Reverse() const
{
	for (const auto& i: theIndices_)
	{
		i->Reverse();
	}
}

std::shared_ptr<tnbLib::Entity2d_CmpMesh>
tnbLib::Entity2d_CmpMesh::Convert(const Entity2d_Triangulation& theMesh)
{
	auto coords = theMesh.Points();
	std::vector<std::shared_ptr<Entity2d_CmpConnect>> indices;
	indices.reserve(theMesh.NbConnectivity());
	for (const auto& x : theMesh.Connectivity())
	{
		auto ids = std::make_shared<Entity2d_CmpConnect_Triangle>(x);
		indices.emplace_back(std::move(ids));
	}
	return std::make_shared<Entity2d_CmpMesh>(std::move(coords), std::move(indices));
}

std::shared_ptr<tnbLib::Entity2d_CmpMesh>
tnbLib::Entity2d_CmpMesh::Convert(const Entity2d_QuadMesh& theMesh)
{
	auto coords = theMesh.Points();
	std::vector<std::shared_ptr<Entity2d_CmpConnect>> indices;
	indices.reserve(theMesh.NbConnectivity());
	for (const auto& x:theMesh.Connectivity())
	{
		auto ids = std::make_shared<Entity2d_CmpConnect_Quad>(x);
		indices.emplace_back(std::move(ids));
	}
	return std::make_shared<Entity2d_CmpMesh>(std::move(coords), std::move(indices));
}

void tnbLib::Entity2d_CmpMesh::Merge
(
	Entity2d_CmpMesh& theMesh,
	const Standard_Real theTol
)
{
	auto b = Geo_BoxTools::GetBox(theMesh.Coords(), 0);
	const auto d = b.Diameter();
	Merge_Pnt<Pnt2d, std::vector> alg;
	alg.SetCoords(theMesh.Coords());
	alg.SetRadius(d * theTol);
	alg.SetResolution(d * 100.0 * theTol);
	alg.Perform();
	Debug_If_Condition_Message(NOT alg.IsDone(), "the application is not performed.");
	auto coords = alg.CompactPoints();
	const auto ids = alg.CompactIndices();
	for (const auto& x: theMesh.Indices())
	{
		if (auto quad = std::dynamic_pointer_cast<Entity2d_CmpConnect_Quad>(x))
		{
			UpdateIndices(*quad, ids);
		}
		else if (auto tri = std::dynamic_pointer_cast<Entity2d_CmpConnect_Triangle>(x))
		{
			UpdateIndices(*tri, ids);
		}
		else
		{
			FatalErrorIn(FunctionSIG) << endl
				<< " Unable to identify the element type." << endl
				<< abort(FatalError);
		}
	}
	theMesh.CoordsRef() = std::move(coords);
}

void tnbLib::Entity2d_CmpMesh::CheckInverseElements
(
	const Entity2d_CmpMesh& theMesh
)
{
	for (Standard_Integer i = 0; i < theMesh.NbElements(); i++)
	{
		if (auto poly = theMesh.GetElement(i); Geo_Tools::Area_cgal(poly) < 0)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< "The mes has atleast one inverse element." << endl
				<< abort(FatalError);
		}
	}
}
