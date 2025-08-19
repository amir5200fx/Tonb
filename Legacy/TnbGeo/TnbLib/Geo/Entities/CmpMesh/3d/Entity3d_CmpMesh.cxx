// ReSharper disable CppClangTidyClangDiagnosticLanguageExtensionToken
#include <Entity3d_CmpMesh.hxx>

#include <Merge3d_Pnt.hxx>
#include <Geo_BoxTools.hxx>
#include <Entity3d_Hexahedralization.hxx>
#include <Entity3d_Tetrahedralization.hxx>
#include <Entity3d_CmpConnect_Brick.hxx>
#include <Entity3d_CmpConnect_Prism.hxx>
#include <Entity3d_CmpConnect_Pyramid.hxx>
#include <Entity3d_CmpConnect_Tetrahedron.hxx>
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

tnbLib::Entity3d_CmpMesh::Entity3d_CmpMesh(Entity3d_CmpMesh&& other) noexcept
	: theCoords_(std::move(other.theCoords_))
	, theIndices_(std::move(other.theIndices_))
{
	// empty body
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

tnbLib::Entity3d_CmpMesh& tnbLib::Entity3d_CmpMesh::operator=(Entity3d_CmpMesh&& other) noexcept
{
	if (this NOT_EQUAL &other)
	{
		theCoords_ = std::move(other.theCoords_);
		theIndices_ = std::move(other.theIndices_);
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
	return elm->RetrievePolygon(Coords());
}

std::shared_ptr<tnbLib::Entity3d_Box> tnbLib::Entity3d_CmpMesh::CalcBoundingBox() const
{
	return std::make_shared<Entity3d_Box>(Geo_BoxTools::GetBox(Coords(), 0));
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
	return std::make_shared<Entity3d_CmpMesh>(std::move(coords), std::move(ids));
}

std::shared_ptr<tnbLib::Entity3d_Tetrahedralization> tnbLib::Entity3d_CmpMesh::ExportAsTetrahedral() const
{
	std::vector<connectivity::quadruple> ids;
	for (const auto& t: Connectivity())
	{
		if (NOT t->IsTetrahedron())
		{
			FatalErrorIn(FunctionSIG) << "\n"
				<< "Couldn't export the mesh as tetrahedral elements.\n"
				<< " - Please make sure all the elements are tetrahedral.\n"
				<< abort(FatalError);
		}
		const auto cmpts = t->Components();
		ids.push_back({ {cmpts.at(0), cmpts.at(1), cmpts.at(2), cmpts.at(3)} });
	}
	auto coords = theCoords_;
	return std::make_shared<Entity3d_Tetrahedralization>(std::move(coords), std::move(ids));
}

std::shared_ptr<tnbLib::Entity3d_Hexahedralization> tnbLib::Entity3d_CmpMesh::ExportAsHexahedral() const
{
	std::vector<connectivity::octuple> ids;
	for (const auto& t: Connectivity())
	{
		if (t->IsTetrahedron())
		{
			const auto cmpts = t->Components();
			ids.emplace_back(raise(raise(connectivity::quadruple{ { cmpts.at(0), cmpts.at(1), cmpts.at(2), cmpts.at(3) } })));
		}
		else if (t->IsPrism())
		{
			const auto cmpts = t->Components();
			ids.emplace_back(raise(connectivity::sextuple{
				{cmpts.at(0), cmpts.at(1), cmpts.at(2), cmpts.at(3), cmpts.at(4), cmpts.at(5)}
			}));
		}
		else if (t->IsPyramid())
		{
			FatalErrorIn(FunctionSIG) << "\n"
				<< " Unsupported type of element has been detected: Pyramid.\n"
				<< abort(FatalError);
		}
		else if (t->IsBrick())
		{
			const auto cmpts = t->Components();
			ids.push_back({
				{cmpts.at(0), cmpts.at(1), cmpts.at(2), cmpts.at(3), cmpts.at(4), cmpts.at(5), cmpts.at(6), cmpts.at(7)}
			});
		}
		else
		{
			FatalErrorIn(FunctionSIG) << "\n"
				<< "Couldn't export the mesh as hexahedral mesh.\n"
				<< " - Please make sure all the elements are lower order than hexahedral elements.\n"
				<< abort(FatalError);
		}
	}
	auto coords = theCoords_;
	return std::make_shared<Entity3d_Hexahedralization>(std::move(coords), std::move(ids));
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
		return ids_tot;
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

void tnbLib::Entity3d_CmpMesh::Import(const Entity3d_CmpMesh& theMesh)
{
	theCoords_.clear();
	theIndices_.clear();
	Add(theMesh);
}

void tnbLib::Entity3d_CmpMesh::Import(const Entity3d_Tetrahedralization& theMesh)
{
	theCoords_.clear();
	theIndices_.clear();
	Add(theMesh);
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
	return std::make_shared<Entity3d_CmpMesh>(std::move(coords), std::move(indices));
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
