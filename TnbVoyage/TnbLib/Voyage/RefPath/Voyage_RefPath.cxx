#include <Voyage_RefPath.hxx>

#include <Voyage_Tools.hxx>
#include <Entity2d_Polygon.hxx>
#include <Pnt2d.hxx>
#include <token.hxx>

void tnbLib::Voyage_RefPath::LoadSingle(Istream& is)
{
	std::vector<Pnt2d> coords;
	is.readBegin("void tnbLib::Voyage_RefPath::LoadSingle(Istream& is)");
	bool flag = false;
	while (!is.eof())
	{
		Pnt2d pt;
		is >> pt;
		is.fatalCheck("Load(Istream): reading the ref. path");
		coords.emplace_back(Voyage_Tools::ConvertToUV(pt));
		token delimiter(is);
		if (delimiter == token::END_LIST)
		{
			flag = true;
			break; // end of the list
		}
	}
	if (NOT flag)
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "unsupported fule has been detected." << endl
			<< abort(FatalError);
	}
	auto poly = std::make_shared<Entity2d_Polygon>(std::move(coords), 0);
	thePath_.emplace_back(std::move(poly));
}

void tnbLib::Voyage_RefPath::Load(Istream& is)
{
	while (!is.eof())
	{
		LoadSingle(is);
		token delimiter(is);
	}
}
