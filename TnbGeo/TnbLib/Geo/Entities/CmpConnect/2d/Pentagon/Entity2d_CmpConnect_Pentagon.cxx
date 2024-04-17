#include <Entity2d_CmpConnect_Pentagon.hxx>

#include <Pnt3d.hxx>
#include <Pnt2d.hxx>

tnbLib::Entity2d_CmpConnect_Pentagon::Entity2d_CmpConnect_Pentagon(const connectivity::quintuple& theQ)
	: theCmpts_({theQ.Value(0), theQ.Value(1), theQ.Value(2), theQ.Value(3), theQ.Value(4)})
{
	// empty body
}

Standard_Boolean
tnbLib::Entity2d_CmpConnect_Pentagon::IsPentagon() const
{
	return Standard_True;
}

Standard_Integer
tnbLib::Entity2d_CmpConnect_Pentagon::NbCmpts() const
{
	return nbCmpts;
}

tnbLib::Entity2d_CmpConnect::ElmType
tnbLib::Entity2d_CmpConnect_Pentagon::ElementType() const
{
	return ElmType::pentagon;
}

std::vector<Standard_Integer>
tnbLib::Entity2d_CmpConnect_Pentagon::Components() const
{
	std::vector<Standard_Integer> indices;
	std::copy(theCmpts_.begin(), theCmpts_.end(), std::back_inserter(indices));
	return std::move(indices);
}

std::vector<tnbLib::Pnt3d>
tnbLib::Entity2d_CmpConnect_Pentagon::RetrievePolygon(const std::vector<Pnt3d>& theCoords) const
{
	std::vector<Pnt3d> coords;
	coords.reserve(nbCmpts);
	for (const auto i : theCmpts_)
	{
		coords.emplace_back(theCoords.at(Index_Of(i)));
	}
	return std::move(coords);
}

std::vector<tnbLib::Pnt2d>
tnbLib::Entity2d_CmpConnect_Pentagon::RetrievePolygon(const std::vector<Pnt2d>& theCoords) const
{
	std::vector<Pnt2d> coords;
	coords.reserve(nbCmpts);
	for (const auto i : theCmpts_)
	{
		coords.emplace_back(theCoords.at(Index_Of(i)));
	}
	return std::move(coords);
}

std::shared_ptr<tnbLib::Entity2d_CmpConnect>
tnbLib::Entity2d_CmpConnect_Pentagon::Copy() const
{
	auto t = std::make_shared<Entity2d_CmpConnect_Pentagon>(this->Array());
	return std::move(t);
}


