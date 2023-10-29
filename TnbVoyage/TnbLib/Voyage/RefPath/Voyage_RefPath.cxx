#include <Voyage_RefPath.hxx>

#include <Voyage_Tools.hxx>
#include <Entity2d_Polygon.hxx>
#include <Pnt2d.hxx>
#include <token.hxx>

void tnbLib::Voyage_RefPath::Load(Istream& is)
{
	std::string comma;
	std::vector<Pnt2d> coords;
	while (!is.eof())
	{
		Pnt2d pt;
		is >> pt;
		is.fatalCheck("Load(Istream): reading the ref. path");
		coords.emplace_back(Voyage_Tools::ConvertToUV(pt));
		token delimiter(is);
	}
	thePath_ = std::make_shared<Entity2d_Polygon>(std::move(coords), 0);
}
