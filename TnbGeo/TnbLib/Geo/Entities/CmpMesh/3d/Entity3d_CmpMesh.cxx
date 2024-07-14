#include <Entity3d_CmpMesh.hxx>

#include <Merge3d_Pnt.hxx>
#include <Geo_BoxTools.hxx>
#include <Entity3d_Tetrahedralization.hxx>
#include <Entity3d_CmpConnect_Brick.hxx>
#include <Entity3d_CmpConnect_Prism.hxx>
#include <Entity3d_CmpConnect_Pyramid.hxx>
#include <Entity3d_CmpConnect_Tetrahedron.hxx>
#include <Entity3d_Box.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Entity2d_CmpMesh_Helper.lxx>

const std::string tnbLib::Entity3d_CmpMesh::extension = ".gmesh3d";

tnbLib::Entity3d_CmpMesh::Entity3d_CmpMesh() = default;
tnbLib::Entity3d_CmpMesh::Entity3d_CmpMesh(const Entity3d_CmpMesh& theMesh)
	: theCoords_(theMesh.Coords())
{
	std::vector<std::shared_ptr<Entity3d_CmpConnect>> ids;
	ids.reserve(NbElements());
	for (const auto& x: this->Indices())
	{
		auto copy = x->Copy();
		ids.emplace_back(std::move(copy));
	}
	theIndices_ = std::move(ids);
}

tnbLib::Entity3d_CmpMesh& 
tnbLib::Entity3d_CmpMesh::operator=(const Entity3d_CmpMesh& theMesh)
{
	if (this NOT_EQUAL &theMesh)
	{
		theCoords_ = theMesh.Coords();
		std::vector<std::shared_ptr<Entity3d_CmpConnect>> ids;
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

Standard_Integer
tnbLib::Entity3d_CmpMesh::NbElements() const
{
	return static_cast<Standard_Integer>(theIndices_.size());
}

std::vector<tnbLib::Pnt3d>
tnbLib::Entity3d_CmpMesh::GetElement(const Standard_Integer theIndex) const
{
	const auto& elm = theIndices_.at(theIndex);
	auto poly = elm->RetrievePolygon(Coords());
	return std::move(poly);
}

std::shared_ptr<tnbLib::Entity3d_Box> tnbLib::Entity3d_CmpMesh::CalcBoundingBox() const
{
	auto b = Geo_BoxTools::GetBox(Coords(), 0);
	auto t = std::make_shared<Entity3d_Box>(std::move(b));
	return std::move(t);
}

std::shared_ptr<tnbLib::Entity3d_CmpMesh>
tnbLib::Entity3d_CmpMesh::Copy() const
{
	auto coords = Coords();
	std::vector<std::shared_ptr<Entity3d_CmpConnect>> ids;
	ids.reserve(NbElements());
	for (const auto& x: this->Indices())
	{
		auto copy = x->Copy();
		ids.emplace_back(std::move(copy));
	}
	auto mesh = std::make_shared<Entity3d_CmpMesh>(std::move(coords), std::move(ids));
	return std::move(mesh);
}

namespace tnbLib
{
	auto MaxID(const std::vector<std::shared_ptr<Entity3d_CmpConnect>>& theIds)
	{
		auto max_id = IntegerFirst();
		for (const auto& x: theIds)
		{
			auto ids = x->Components();
			for (const auto i: ids)
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
		const std::vector<std::shared_ptr<Entity3d_CmpConnect>>& theIds0,
		const std::vector<std::shared_ptr<Entity3d_CmpConnect>>& theIds1
	)
	{
		const auto max_id = MaxID(theIds0);
		std::vector<std::shared_ptr<Entity3d_CmpConnect>> ids_tot;
		ids_tot.reserve(theIds0.size() + theIds1.size());
		for (const auto& x: theIds0)
		{
			ids_tot.emplace_back(x);
		}
		for (const auto& x: theIds1)
		{
			auto copy = x->Copy();
			if (const auto e=std::dynamic_pointer_cast<Entity3d_CmpConnect_Brick>(copy))
			{
				e->Value(0) += max_id;
				e->Value(1) += max_id;
				e->Value(2) += max_id;
				e->Value(3) += max_id;
				e->Value(4) += max_id;
				e->Value(5) += max_id;
				e->Value(6) += max_id;
				e->Value(7) += max_id;
			}
			else if (const auto e = std::dynamic_pointer_cast<Entity3d_CmpConnect_Prism>(copy))
			{
				e->Value(0) += max_id;
				e->Value(1) += max_id;
				e->Value(2) += max_id;
				e->Value(3) += max_id;
				e->Value(4) += max_id;
				e->Value(5) += max_id;
			}
			else if (const auto e = std::dynamic_pointer_cast<Entity3d_CmpConnect_Pyramid>(copy))
			{
				e->Value(0) += max_id;
				e->Value(1) += max_id;
				e->Value(2) += max_id;
				e->Value(3) += max_id;
				e->Value(4) += max_id;
			}
			else if (const auto e = std::dynamic_pointer_cast<Entity3d_CmpConnect_Tetrahedron>(copy))
			{
				e->Value(0) += max_id;
				e->Value(1) += max_id;
				e->Value(2) += max_id;
				e->Value(3) += max_id;
				e->Value(4) += max_id;
			}
			else
			{
				FatalErrorIn(FunctionSIG) << endl
					<< "Unspecified type of element has been detected." << endl
					<< abort(FatalError);
			}
			ids_tot.emplace_back(std::move(copy));
		}
		return std::move(ids_tot);
	}
}

void tnbLib::Entity3d_CmpMesh::Add(const Entity3d_CmpMesh& theMesh)
{
	for (const auto& x: theMesh.Coords())
	{
		theCoords_.emplace_back(x);
	}
	theIndices_ =
		CombineConnectivities(this->Indices(), theMesh.Indices());
}

void tnbLib::Entity3d_CmpMesh::Add(const Entity3d_Tetrahedralization& theMesh)
{
	const auto mesh = Convert(theMesh);
	Add(*mesh);
}

std::shared_ptr<tnbLib::Entity3d_CmpMesh>
tnbLib::Entity3d_CmpMesh::Convert(const Entity3d_Tetrahedralization& theMesh)
{
	auto coords = theMesh.Points();
	std::vector<std::shared_ptr<Entity3d_CmpConnect>> indices;
	indices.reserve(theMesh.NbConnectivity());
	for (const auto& x: theMesh.Connectivity())
	{
		auto ids = std::make_shared<Entity3d_CmpConnect_Tetrahedron>(x);
		indices.emplace_back(std::move(ids));
	}
	auto mesh = std::make_shared<Entity3d_CmpMesh>(std::move(coords), std::move(indices));
	return std::move(mesh);
}



void tnbLib::Entity3d_CmpMesh::Merge
(
	Entity3d_CmpMesh& theMesh,
	const Standard_Real theTol
)
{
	const auto b = Geo_BoxTools::GetBox(theMesh.Coords(), 0);
	const auto d = b.Diameter();
	Merge_Pnt<Pnt3d, std::vector> alg;
	alg.SetCoords(theMesh.Coords());
	alg.SetRadius(d * theTol);
	alg.SetResolution(d * 100.0 * theTol);
	alg.Perform();
	Debug_If_Condition_Message(NOT alg.IsDone(), "the application is not performed.");
	auto coords = alg.CompactPoints();
	const auto ids = alg.CompactIndices();
	for (const auto& x: theMesh.Indices())
	{
		if (const auto e = std::dynamic_pointer_cast<Entity3d_CmpConnect_Brick>(x))
		{
			UpdateIndices(*e, ids);
		}
		else if (const auto e = std::dynamic_pointer_cast<Entity3d_CmpConnect_Prism>(x))
		{
			UpdateIndices(*e, ids);
		}
		else if (const auto e = std::dynamic_pointer_cast<Entity3d_CmpConnect_Pyramid>(x))
		{
			UpdateIndices(*e, ids);
		}
		else if (const auto e = std::dynamic_pointer_cast<Entity3d_CmpConnect_Tetrahedron>(x))
		{
			UpdateIndices(*e, ids);
		}
		else
		{
			FatalErrorIn(FunctionSIG) << endl
				<< "Unspecified type of element has been detected." << endl
				<< abort(FatalError);
		}
	}
	theMesh.CoordsRef() = std::move(coords);
}
