#include <Cad_PolesNetPrcssr.hxx>

#include <Pnt3d.hxx>
#include <Vec3d.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom_BSplineSurface.hxx>

Standard_Integer 
tnbLib::Cad_PolesNetPrcssr::NbRows() const
{
	Debug_Null_Pointer(Surface());
	return Surface()->NbUPoles();
}

Standard_Integer 
tnbLib::Cad_PolesNetPrcssr::NbColumns() const
{
	Debug_Null_Pointer(Surface());
	return Surface()->NbVPoles();
}

std::vector<std::pair<tnbLib::Pnt3d, Standard_Real>>
tnbLib::Cad_PolesNetPrcssr::FirstPoleRow() const
{
	auto poles = PoleRow(0);
	return std::move(poles);
}

std::vector<std::pair<tnbLib::Pnt3d, Standard_Real>>
tnbLib::Cad_PolesNetPrcssr::LastPoleRow() const
{
	auto poles = PoleRow(NbRows() - 1);
	return std::move(poles);
}

std::vector<std::pair<tnbLib::Pnt3d, Standard_Real>>
tnbLib::Cad_PolesNetPrcssr::FirstPoleColumn() const
{
	auto poles = PoleColumn(0);
	return std::move(poles);
}

std::vector<std::pair<tnbLib::Pnt3d, Standard_Real>>
tnbLib::Cad_PolesNetPrcssr::LastPoleColumn() const
{
	auto poles = PoleColumn(NbColumns() - 1);
	return std::move(poles);
}

//std::pair<tnbLib::Pnt3d, tnbLib::Pnt3d>
//tnbLib::Cad_PolesNetPrcssr::CalcVectorRow
//(
//	const Standard_Integer theIndex
//) const
//{
//	Debug_If_Condition(NOT INSIDE(theIndex, 0, NbVectorRows()));
//	auto poles = PoleRow(theIndex);
//	for (Standard_Integer i = 1; i < poles.size(); i++)
//	{
//		auto vect = Vec3d(poles[i], poles[i - 1]);
//		if (vect.Magnitude() <= Tolerance())
//		{
//			continue;
//		}
//		auto t = std::make_pair(std::move(poles[i - 1]), std::move(poles[i]));
//		return std::move(t);
//	}
//	return std::make_pair(std::move(poles[1]), std::move(poles[0]));
//}

//std::pair<tnbLib::Pnt3d, tnbLib::Pnt3d>
//tnbLib::Cad_PolesNetPrcssr::CalcVectorColumn
//(
//	const Standard_Integer theIndex
//) const
//{
//	Debug_If_Condition(NOT INSIDE(theIndex, 0, NbVectorColumns()));
//	auto poles = PoleColumn(theIndex);
//	for (Standard_Integer i = 1; i < poles.size(); i++)
//	{
//		auto vect = Vec3d(poles[i], poles[i - 1]);
//		if (vect.Magnitude() <= Tolerance())
//		{
//			continue;
//		}
//		auto t = std::make_pair(std::move(poles[i - 1]), std::move(poles[i]));
//		return std::move(t);
//	}
//	return std::make_pair(std::move(poles[1]), std::move(poles[0]));
//}

//std::pair<tnbLib::Pnt3d, tnbLib::Pnt3d>
//tnbLib::Cad_PolesNetPrcssr::CalcVectorRowRev
//(
//	const Standard_Integer theIndex
//) const
//{
//	Debug_If_Condition(NOT INSIDE(theIndex, 0, NbVectorRows()));
//	auto poles = PoleRow(theIndex);
//	for (Standard_Integer i = poles.size() - 1; i >= 1; i--)
//	{
//		auto vect = Vec3d(poles[i], poles[i - 1]);
//		if (vect.Magnitude() <= Tolerance())
//		{
//			continue;
//		}
//		auto t = std::make_pair(std::move(poles[i]), std::move(poles[i - 1]));
//		return std::move(t);
//	}
//	return std::make_pair(std::move(poles[poles.size() - 1]), std::move(poles[poles.size() - 2]));
//}

//std::pair<tnbLib::Pnt3d, tnbLib::Pnt3d>
//tnbLib::Cad_PolesNetPrcssr::CalcVectorColumnRev
//(
//	const Standard_Integer theIndex
//) const
//{
//	Debug_If_Condition(NOT INSIDE(theIndex, 0, NbVectorColumns()));
//	auto poles = PoleColumn(theIndex);
//	for (Standard_Integer i = poles.size() - 1; i >= 1; i--)
//	{
//		auto vect = Vec3d(poles[i], poles[i - 1]);
//		if (vect.Magnitude() <= Tolerance())
//		{
//			continue;
//		}
//		auto t = std::make_pair(std::move(poles[i]), std::move(poles[i - 1]));
//		return std::move(t);
//	}
//	return std::make_pair(std::move(poles[poles.size() - 1]), std::move(poles[poles.size() - 2]));
//}

std::vector<std::pair<tnbLib::Pnt3d, Standard_Real>>
tnbLib::Cad_PolesNetPrcssr::PoleRow(const Standard_Integer theIndex) const
{
	Debug_If_Condition(NOT INSIDE(theIndex, 0, NbRows() - 1));
	Debug_Null_Pointer(Surface());
	
	std::vector<std::pair<Pnt3d, Standard_Real>> poles;
	poles.reserve(NbColumns());
	for (Standard_Integer j = 1; j <= NbColumns(); j++)
	{
		auto pt = Pnt3d(Surface()->Pole(theIndex + 1, j));
		auto w = Surface()->Weight(theIndex + 1, j);

		auto pw = std::make_pair(std::move(pt), w);
		poles.push_back(std::move(pw));
	}
	return std::move(poles);
}

std::vector<std::pair<tnbLib::Pnt3d, Standard_Real>>
tnbLib::Cad_PolesNetPrcssr::PoleColumn(const Standard_Integer theIndex) const
{
	Debug_If_Condition(NOT INSIDE(theIndex, 0, NbColumns() - 1));
	Debug_Null_Pointer(Surface());

	std::vector<std::pair<Pnt3d, Standard_Real>> poles;
	poles.reserve(NbRows());
	for (Standard_Integer i = 1; i <= NbRows(); i++)
	{
		auto pt = Pnt3d(Surface()->Pole(i, theIndex + 1));
		auto w = Surface()->Weight(i, theIndex + 1);

		auto pw = std::make_pair(std::move(pt), w);
		poles.push_back(std::move(pw));
	}
	return std::move(poles);
}