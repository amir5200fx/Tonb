#include <Entity3d_CmpConnect_Brick.hxx>

#include <Pnt3d.hxx>

tnbLib::Entity3d_CmpConnect_Brick::Entity3d_CmpConnect_Brick(const connectivity::octuple& theOct)
	: theCmpts_
({ 
	theOct.Value(0),
	theOct.Value(1),
	theOct.Value(2),
	theOct.Value(3),
	theOct.Value(4),
	theOct.Value(5),
	theOct.Value(6),
	theOct.Value(7)
})
{}

Standard_Boolean tnbLib::Entity3d_CmpConnect_Brick::IsBrick() const
{
	return Standard_True;
}

Standard_Integer tnbLib::Entity3d_CmpConnect_Brick::NbCmpts() const { return nbCmpts; }
tnbLib::Entity3d_CmpConnect::ElmType tnbLib::Entity3d_CmpConnect_Brick::ElementType() const { return ElmType::brick; }
std::vector<Standard_Integer>
tnbLib::Entity3d_CmpConnect_Brick::Components() const
{
	std::vector<Standard_Integer> indices;
	std::copy(theCmpts_.begin(), theCmpts_.end(), std::back_inserter(indices));
	return indices;
}

std::vector<tnbLib::Pnt3d>
tnbLib::Entity3d_CmpConnect_Brick::RetrievePolygon(const std::vector<Pnt3d>& theCoords) const
{
	std::vector<Pnt3d> coords;
	coords.reserve(nbCmpts);
	for (const auto i : theCmpts_)
	{
		coords.emplace_back(theCoords.at(Index_Of(i)));
	}
	return coords;
}

std::vector<tnbLib::Entity3d_CmpConnect::Face> tnbLib::Entity3d_CmpConnect_Brick::CalcFaces() const
{
	std::vector<Face> faces;
	faces.emplace_back(Face{ {theCmpts_.at(0), theCmpts_.at(1), theCmpts_.at(5), theCmpts_.at(4)} });
	faces.emplace_back(Face{ {theCmpts_.at(1), theCmpts_.at(2), theCmpts_.at(6), theCmpts_.at(5)} });
	faces.emplace_back(Face{ {theCmpts_.at(2), theCmpts_.at(3), theCmpts_.at(7), theCmpts_.at(6)} });
	faces.emplace_back(Face{ {theCmpts_.at(3), theCmpts_.at(0), theCmpts_.at(4), theCmpts_.at(7)} });

	faces.emplace_back(Face{ {theCmpts_.at(0), theCmpts_.at(3), theCmpts_.at(2), theCmpts_.at(1)} });
	faces.emplace_back(Face{ {theCmpts_.at(4), theCmpts_.at(5), theCmpts_.at(6), theCmpts_.at(7)} });
	return faces;
}

std::shared_ptr<tnbLib::Entity3d_CmpConnect> tnbLib::Entity3d_CmpConnect_Brick::Copy() const
{
	return std::make_shared<Entity3d_CmpConnect_Brick>(this->Array());
}

void tnbLib::Entity3d_CmpConnect_Brick::Update(const std::vector<Standard_Integer>& indices)
{
	for (int i = 0; i < nbCmpts; i++)
	{
		theCmpts_.at(i) = indices.at(theCmpts_.at(i) - 1);
	}
}

void tnbLib::Entity3d_CmpConnect_Brick::Update(const std::map<Standard_Integer, Standard_Integer>& indices)
{
	for (auto& i: theCmpts_)
	{
		i = indices.at(i);
	}
}
