#include <Geo2d_InscConxPoly.hxx>

#include <Geo_Tools.hxx>
#include <Entity2d_Polygon.hxx>
#include <Entity_Line.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const Standard_Real tnbLib::Geo2d_InscConxPoly::DEFAULT_TOLERANCE = 1.0E-6;

namespace tnbLib
{

	namespace inscConxPolyLib
	{

		class SubdivideFunc
		{

			/*Private Data*/

			const std::vector<Pnt2d>& thePts_;

			Standard_Real theTol_;

			// results [5/19/2022 Amir]

			std::vector<std::pair<Standard_Integer, Standard_Integer>> theIds_;

		protected:

			// default constructor [5/19/2022 Amir]


			// constructors [5/19/2022 Amir]

			explicit SubdivideFunc
			(
				const std::vector<Pnt2d>& thePnts
			)
				: thePts_(thePnts)
				, theTol_(0)
			{}


			// protected functions and operators [5/19/2022 Amir]

			

		public:

			// public functions and operators [5/19/2022 Amir]

			const auto& Points() const
			{
				return thePts_;
			}

			auto Tolerance() const
			{
				return theTol_;
			}

			auto& IdsRef()
			{
				return theIds_;
			}

			const auto& Ids() const
			{
				return theIds_;
			}

			virtual std::pair<Standard_Boolean, Standard_Integer> 
				Subdivide
				(
					const Entity2d_LineRef&,
					const Standard_Integer i0,
					const Standard_Integer i1
				) const = 0;

			void Subdivide(const Standard_Integer i0, const Standard_Integer i1);

			void SetTolerance(const Standard_Real theTol)
			{
				theTol_ = theTol;
			}


			// static functions and operators [5/19/2022 Amir]

			static std::pair<Standard_Boolean, Standard_Real> 
				IsRight(const Pnt2d& theCoord, const Entity2d_LineRef&, const Standard_Real theTol);

			static std::vector<Standard_Integer> 
				RetrieveIds(const std::vector<std::pair<Standard_Integer, Standard_Integer>>&);

			static void Check(const std::vector<std::pair<Standard_Integer, Standard_Integer>>&);
		};

		class SubdivideFunc_Projc
			: public SubdivideFunc
		{

			/*Private Data*/


		public:

			// default constructor [5/19/2022 Amir]


			// constructors [5/19/2022 Amir]

			explicit SubdivideFunc_Projc
			(
				const std::vector<Pnt2d>& thePts
			)
				: SubdivideFunc(thePts)
			{}


			// override functions and operators [5/19/2022 Amir]

			std::pair<Standard_Boolean, Standard_Integer> 
				Subdivide
				(
					const Entity2d_LineRef&,
					const Standard_Integer i0, 
					const Standard_Integer i1
				) const override;
		};
	}
}

void tnbLib::inscConxPolyLib::SubdivideFunc::Subdivide
(
	const Standard_Integer i0, 
	const Standard_Integer i1
)
{
	if (i1 <= i0)
	{
		return;
	}
	const auto& pts = Points();
	const auto& p0 = pts.at(i0);
	const auto& p1 = pts.at(i1);

	try
	{
		Entity2d_LineRef line(p0, Dir2d(p0, p1));
		auto[sub, im] = Subdivide(line, i0, i1);
		if (sub)
		{
			Subdivide(i0, im);
			Subdivide(im, i1);
		}
		else
		{
			auto paired = std::make_pair(i0, i1);
			IdsRef().push_back(std::move(paired));
		}
	}
	catch (const Standard_Failure& x)
	{
		FatalErrorIn(FunctionSIG)
			<< x.GetMessageString() << endl
			<< abort(FatalError);
	}
}

std::pair<Standard_Boolean, Standard_Real>
tnbLib::inscConxPolyLib::SubdivideFunc::IsRight
(
	const Pnt2d & theCoord, 
	const Entity2d_LineRef & theLine,
	const Standard_Real theTol
)
{
	auto pPt = Geo_Tools::ProjectToLine_cgal(theCoord, theLine);
	try
	{
		auto d = Dir2d(pPt, theCoord);
		auto t = std::make_pair(d.Crossed(theLine.Dir()) >= theTol, pPt.Distance(theCoord));
		return std::move(t);
	}
	catch (const Standard_Failure& x)
	{
		FatalErrorIn(FunctionSIG)
			<< x.GetMessageString() << endl
			<< abort(FatalError);
		return std::pair<Standard_Boolean, Standard_Real>();
	}
}

std::vector<Standard_Integer> 
tnbLib::inscConxPolyLib::SubdivideFunc::RetrieveIds
(
	const std::vector<std::pair<Standard_Integer, Standard_Integer>>& theIds
)
{
#ifdef _DEBUG
	Check(theIds);
#endif // _DEBUG
	std::vector<Standard_Integer> Ids;
	Ids.reserve(theIds.size());
	for (const auto& x : theIds)
	{
		auto x0 = x.first;
		Ids.push_back(x0);
	}
	const auto& xf = LastItem(theIds);
	Ids.push_back(xf.second);
	return std::move(Ids);
}

void tnbLib::inscConxPolyLib::SubdivideFunc::Check
(
	const std::vector<std::pair<Standard_Integer, Standard_Integer>>& theIds
)
{
	for (size_t i = 1; i < theIds.size(); i++)
	{
		const auto& p0 = theIds.at(i - 1);
		const auto& p1 = theIds.at(i);

		if (p0.second NOT_EQUAL p1.first)
		{
			FatalErrorIn(FunctionSIG)
				<< "the Ids vector is not continuous or sorted!" << endl
				<< abort(FatalError);
		}
	}
}

std::pair<Standard_Boolean, Standard_Integer>
tnbLib::inscConxPolyLib::SubdivideFunc_Projc::Subdivide
(
	const Entity2d_LineRef & theLine,
	const Standard_Integer i0,
	const Standard_Integer i1
) const
{
	Standard_Real dmax = 0;
	Standard_Integer imax = i0;
	for (Standard_Integer i = i0 + 1; i < i1; i++)
	{
		auto[isRight, d] = IsRight(Points().at(i), theLine, Tolerance());
		if (isRight)
		{
			if (d > dmax)
			{
				imax = i;
				dmax = d;
			}
		}
	}

	if (imax > i0)
	{
		auto t = std::make_pair(Standard_True, imax);
		return std::move(t);
	}
	else
	{
		auto t = std::make_pair(Standard_False, imax);
		return std::move(t);
	}
}

std::shared_ptr<tnbLib::Entity2d_Polygon> 
tnbLib::Geo2d_InscConxPoly::CreatePolygon
(
	const std::vector<Pnt2d> & thePoly,
	const std::vector<Standard_Integer>& theIds
)
{
	std::vector<Pnt2d> pts;
	pts.reserve(theIds.size());
	for (auto id : theIds)
	{
		auto pt = thePoly.at(id);
		pts.push_back(std::move(pt));
	}
	auto poly = std::make_shared<Entity2d_Polygon>(std::move(pts), 0);
	return std::move(poly);
}

void tnbLib::Geo2d_InscConxPoly::Perform()
{
	if (NOT Polygon())
	{
		FatalErrorIn(FunctionSIG)
			<< "no polygon has been found!" << endl
			<< abort(FatalError);
	}
	const auto& pts = Polygon()->Points();
	const auto& p0 = FirstItem(pts);
	const auto& pn = LastItem(pts);
	if (p0.Distance(pn) <= Tolerance())
	{
		FatalErrorIn(FunctionSIG)
			<< "the polygon is closed." << endl
			<< abort(FatalError);
	}
	else
	{
		std::shared_ptr<inscConxPolyLib::SubdivideFunc> 
			subFun = std::make_shared<inscConxPolyLib::SubdivideFunc_Projc>(pts);
		subFun->SetTolerance(Tolerance());

		try
		{
			subFun->Subdivide(0, pts.size() - 1);
		}
		catch (const Standard_Failure& x)
		{
			FatalErrorIn(FunctionSIG)
				<< x.GetMessageString() << endl
				<< abort(FatalError);
		}

		auto& Ids = subFun->IdsRef();
		if (Ids.empty())
		{
			std::vector<Standard_Integer> ids;
			ids.push_back(0);
			ids.push_back(pts.size() - 1);

			auto poly = CreatePolygon(pts, ids);

			HullRef() = std::move(poly);
		}
		else
		{
			std::sort
			(
				Ids.begin(), Ids.end(),
				([](
					const std::pair<Standard_Integer, Standard_Integer>& v0,
					const std::pair<Standard_Integer, Standard_Integer>& v1
					)->bool {return MEAN((float)v0.first, (float)v0.second) < MEAN((float)v1.first, (float)v1.second); })
			);

			auto ids = inscConxPolyLib::SubdivideFunc::RetrieveIds(Ids);

			auto poly = CreatePolygon(pts, ids);

			HullRef() = std::move(poly);
		}
	}
	
	Change_IsDone() = Standard_True;
}