#include <Cad_GeomCurve.hxx>
#include <Pnt3d.hxx>
#include <OSstream.hxx>
#include <TnbError.hxx>

#include <vector>

#include <Standard_Handle.hxx>
#include <Geom_BSplineCurve.hxx>

namespace tnbLib
{

	static unsigned short verbose(0);

	std::vector<std::shared_ptr<Cad_GeomCurve>> myCurves;

	auto getIndex()
	{
		return (int)myCurves.size() + 1;
	}

	auto createPointList()
	{
		return std::vector<Pnt3d>();
	}

	auto createRealList()
	{
		return std::vector<double>();
	}

	auto createIntegerList()
	{
		return std::vector<int>();
	}

	auto getPoles(const std::vector<Pnt3d>& pnts)
	{
		TColgp_Array1OfPnt poles(1, pnts.size());
		int k = 0;
		for (const auto& x : pnts)
		{
			poles.SetValue(++k, x);
		}
		return std::move(poles);
	}

	auto getReals(const std::vector<double>& xs)
	{
		TColStd_Array1OfReal X(1, xs.size());
		int k = 0;
		for (auto x : xs)
		{
			X.SetValue(++k, x);
		}
		return std::move(X);
	}

	auto getIntegers(const std::vector<int>& xs)
	{
		TColStd_Array1OfInteger X(1, xs.size());
		int k = 0;
		for (auto x : xs)
		{
			X.SetValue(++k, x);
		}
		return std::move(X);
	}

	void makeCurve
	(
		const std::vector<Pnt3d>& pnts,
		const std::vector<double>& ws,
		const std::vector<double>& knots,
		const std::vector<int>& mults, 
		int deg
	)
	{
		try
		{
			Handle(Geom_BSplineCurve) geom =
				new Geom_BSplineCurve
				(
					getPoles(pnts),
					getReals(ws),
					getReals(knots),
					getIntegers(mults),
					deg
				);
			auto curve = std::make_shared<Cad_GeomCurve>(getIndex(), "curve", std::move(geom));

			myCurves.push_back(std::move(curve));
		}
		catch (const Standard_Failure& x)
		{
			FatalErrorIn(FunctionSIG)
				<< x.GetMessageString() << endl
				<< abort(FatalError);
		}
	}

	void makeCurve
	(
		const std::vector<Pnt3d>& pnts,
		const std::vector<double>& ws,
		const std::vector<double>& knots,
		const std::vector<int>& mults,
		int deg,
		const std::string& name
	)
	{
		try
		{
			Handle(Geom_BSplineCurve) geom =
				new Geom_BSplineCurve
				(
					getPoles(pnts),
					getReals(ws),
					getReals(knots),
					getIntegers(mults),
					deg
				);
			auto curve = std::make_shared<Cad_GeomCurve>(getIndex(), name, std::move(geom));

			myCurves.push_back(std::move(curve));
		}
		catch (Standard_Failure& x)
		{
			FatalErrorIn(FunctionSIG)
				<< x.GetMessageString() << endl
				<< abort(FatalError);
		}
	}


}