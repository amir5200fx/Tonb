#include <Entity3d_CmpConnect_Prism.hxx>

#include <Pnt3d.hxx>

tnbLib::Entity3d_CmpConnect_Prism::Entity3d_CmpConnect_Prism(const connectivity::sextuple& theSext)
	: theCmpts_
	({
		theSext.Value(0),
		theSext.Value(1),
		theSext.Value(2),
		theSext.Value(3),
		theSext.Value(4),
		theSext.Value(5)
		})
{}

Standard_Boolean tnbLib::Entity3d_CmpConnect_Prism::IsPrism() const
{
	return Standard_True;
}

Standard_Integer tnbLib::Entity3d_CmpConnect_Prism::NbCmpts() const { return nbCmpts; }
tnbLib::Entity3d_CmpConnect::ElmType tnbLib::Entity3d_CmpConnect_Prism::ElementType() const { return ElmType::prism; }
std::vector<Standard_Integer>
tnbLib::Entity3d_CmpConnect_Prism::Components() const
{
	std::vector<Standard_Integer> indices;
	std::copy(theCmpts_.begin(), theCmpts_.end(), std::back_inserter(indices));
	return std::move(indices);
}

std::vector<tnbLib::Pnt3d>
tnbLib::Entity3d_CmpConnect_Prism::RetrievePolygon(const std::vector<Pnt3d>& theCoords) const
{
	std::vector<Pnt3d> coords;
	coords.reserve(nbCmpts);
	for (const auto i : theCmpts_)
	{
		coords.emplace_back(theCoords.at(Index_Of(i)));
	}
	return std::move(coords);
}

std::vector<tnbLib::Entity3d_CmpConnect::Face> tnbLib::Entity3d_CmpConnect_Prism::CalcFaces() const
{
	std::vector<Face> faces;
	faces.emplace_back(Face{ {theCmpts_.at(0), theCmpts_.at(1), theCmpts_.at(4), theCmpts_.at(3)} });
	faces.emplace_back(Face{ {theCmpts_.at(1), theCmpts_.at(2), theCmpts_.at(5), theCmpts_.at(4)} });
	faces.emplace_back(Face{ {theCmpts_.at(2), theCmpts_.at(0), theCmpts_.at(3), theCmpts_.at(5)} });

	faces.emplace_back(Face{ {theCmpts_.at(0), theCmpts_.at(2), theCmpts_.at(1)} });
	faces.emplace_back(Face{ {theCmpts_.at(3), theCmpts_.at(4), theCmpts_.at(5)} });
	return faces;
}

std::shared_ptr<tnbLib::Entity3d_CmpConnect>
tnbLib::Entity3d_CmpConnect_Prism::Copy() const
{
	auto t = std::make_shared<Entity3d_CmpConnect_Prism>(this->Array());
	return std::move(t);
}
