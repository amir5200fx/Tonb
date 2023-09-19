#include <Entity3d_CmpConnect_Tetrahedron.hxx>

#include <Pnt3d.hxx>

tnbLib::Entity3d_CmpConnect_Tetrahedron::Entity3d_CmpConnect_Tetrahedron(const connectivity::quadruple& theQuad)
	: theCmpts_
	({
		theQuad.Value(0),
		theQuad.Value(1),
		theQuad.Value(2),
		theQuad.Value(3)
		})
{}

Standard_Boolean
tnbLib::Entity3d_CmpConnect_Tetrahedron::IsTetrahedron() const
{
	return Standard_True;
}

Standard_Integer tnbLib::Entity3d_CmpConnect_Tetrahedron::NbCmpts() const { return nbCmpts; }
tnbLib::Entity3d_CmpConnect::ElmType tnbLib::Entity3d_CmpConnect_Tetrahedron::ElementType() const { return ElmType::tetrahedron; }
std::vector<Standard_Integer>
tnbLib::Entity3d_CmpConnect_Tetrahedron::Components() const
{
	std::vector<Standard_Integer> indices;
	std::copy(theCmpts_.begin(), theCmpts_.end(), std::back_inserter(indices));
	return std::move(indices);
}

std::vector<tnbLib::Pnt3d>
tnbLib::Entity3d_CmpConnect_Tetrahedron::RetrievePolygon(const std::vector<Pnt3d>& theCoords) const
{
	std::vector<Pnt3d> coords;
	coords.reserve(nbCmpts);
	for (const auto i : theCmpts_)
	{
		coords.emplace_back(theCoords.at(Index_Of(i)));
	}
	return std::move(coords);
}

std::shared_ptr<tnbLib::Entity3d_CmpConnect>
tnbLib::Entity3d_CmpConnect_Tetrahedron::Copy() const
{
	auto t = std::make_shared<Entity3d_CmpConnect_Tetrahedron>(this->Array());
	return std::move(t);
}
