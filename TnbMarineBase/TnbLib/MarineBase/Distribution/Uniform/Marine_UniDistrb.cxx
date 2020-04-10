#include <Marine_UniDistrb.hxx>

#include <Entity3d_Box.hxx>
#include <Geo_xDistb.hxx>
#include <error.hxx>
#include <OSstream.hxx>

tnbLib::Marine_UniDistrb::Marine_UniDistrb
(
	const Standard_Real x0, 
	const Standard_Real x1,
	const Standard_Integer n
)
	: Global_Bound<Standard_Real>(x0, x1)
	, theSize_(n)
{
}

void tnbLib::Marine_UniDistrb::Perform()
{
	if (Size() < 2)
	{
		FatalErrorIn("void tnbLib::Marine_UniDistrb::Perform()")
			<< "Invalid size to discretize uniformly! " << endl
			<< abort(FatalError);
	}

	if (Lower() <= Upper())
	{
		FatalErrorIn("void tnbLib::Marine_UniDistrb::Perform()")
			<< "Invalid bound size" << endl
			<< abort(FatalError);
	}

	auto dist = std::make_shared<Geo_xDistb>();
	Debug_Null_Pointer(dist);

	auto& X = dist->ChangeValues();
	X.reserve(Size());

	const auto dx = (Upper() - Lower()) / (Standard_Real)Size();
	const auto x0 = Lower();
	for (auto i = 0; i < Size(); i++)
	{
		auto x = x0 + i * dx + 0.5*dx;
		X.push_back(x);
	}

	ChangeX() = std::move(dist);
	Change_IsDone() = Standard_True;
}

std::shared_ptr<tnbLib::Marine_Distrb> 
tnbLib::Marine_UniDistrb::xDistb
(
	const Entity3d_Box & theDomain, 
	const Standard_Integer theSize
)
{
	const auto x0 = theDomain.P0().X();
	const auto x1 = theDomain.P1().X();

	auto dist = std::make_shared<Marine_UniDistrb>(x0, x1, theSize);
	Debug_Null_Pointer(dist);

	return std::move(dist);
}

std::shared_ptr<tnbLib::Marine_Distrb>
tnbLib::Marine_UniDistrb::zDistb
(
	const Entity3d_Box & theDomain,
	const Standard_Integer theSize
)
{
	const auto x0 = theDomain.P0().Z();
	const auto x1 = theDomain.P1().Z();

	auto dist = std::make_shared<Marine_UniDistrb>(x0, x1, theSize);
	Debug_Null_Pointer(dist);

	return std::move(dist);
}

std::shared_ptr<tnbLib::Marine_Distrb> 
tnbLib::Marine_UniDistrb::xOneStepForwardDistb
(
	const Entity3d_Box & theDomain, 
	const Standard_Integer theSize
)
{
	const auto x0 = theDomain.P0().X();
	const auto x1 = theDomain.P1().X();

	const auto dx = (x1 - x0) / (Standard_Real)theSize;
	
	auto dist = std::make_shared<Marine_UniDistrb>(x0, x1 + dx, theSize + 1);
	Debug_Null_Pointer(dist);

	return std::move(dist);
}

std::shared_ptr<tnbLib::Marine_Distrb> 
tnbLib::Marine_UniDistrb::zOneStepForwardDistb
(
	const Entity3d_Box & theDomain,
	const Standard_Integer theSize
)
{
	const auto x0 = theDomain.P0().Z();
	const auto x1 = theDomain.P1().Z();

	const auto dx = (x1 - x0) / (Standard_Real)theSize;

	auto dist = std::make_shared<Marine_UniDistrb>(x0, x1 + dx, theSize + 1);
	Debug_Null_Pointer(dist);

	return std::move(dist);
}