#include <Geo2d_DelTri.hxx>

tnbLib::Geo2d_DelTri::Geo2d_DelTri
(
	const std::vector<Pnt2d>& thePts
)
{
	Import(thePts);
}

void tnbLib::Geo2d_DelTri::Import
(
	const std::vector<Pnt2d>& thePts
)
{
	theData_ = std::make_shared<staticData>();

	auto& Pts = Data()->Points();
	auto& Vtx = Data()->Connectivity();
	auto& Neighb = Data()->Neighbors();

	Pts.resize(thePts.size() + 3);
	Vtx.resize(2 * thePts.size() + 10);
	Neighb.resize(2 * thePts.size() + 10);

	ChangeNbPts() = (Standard_Integer)thePts.size();
	ChangeNbTriangles() = 0;

	Standard_Integer K = 0;
	for (const auto& x : thePts)
	{
		Pts[K++] = x;
	}
}

namespace tnbLib
{

	static inline Standard_Boolean Swap
	(
		const Pnt2d& Pt,
		const Pnt2d& P1,
		const Pnt2d& P2,
		const Pnt2d& P3
	)
	{
		auto x13 = P1.X() - P3.X();
		auto y13 = P1.Y() - P3.Y();
		auto x23 = P2.X() - P3.X();
		auto y23 = P2.Y() - P3.Y();
		auto x1p = P1.X() - Pt.X();
		auto y1p = P1.Y() - Pt.Y();
		auto x2p = P2.X() - Pt.X();
		auto y2p = P2.Y() - Pt.Y();

		auto cosa = x13 * x23 + y13 * y23;
		auto cosb = x2p * x1p + y1p * y2p;

		if ((cosa >= 0) && (cosb >= 0))
			return Standard_False;
		else if ((cosa < 0) && (cosb < 0))
			return Standard_True;
		else
		{
			auto sina = x13 * y23 - x23 * y13;
			auto sinb = x2p * y1p - x1p * y2p;

			if ((sina*cosb + sinb * cosa) < 0)
				return Standard_True;
			else
				return Standard_False;
		}
	}
}

void tnbLib::Geo2d_DelTri::Delaunay()
{
	auto v1 = NbPoints() + 1;
	auto v2 = NbPoints() + 2;
	auto v3 = NbPoints() + 3;

	auto& Vtx = Data()->Connectivity();
	auto& Neighb = Data()->Neighbors();

	Vtx[0].Value(0) = v1;
	Vtx[0].Value(1) = v2;
	Vtx[0].Value(2) = v3;

	Neighb[0].Value(0) = 0;
	Neighb[0].Value(1) = 0;
	Neighb[0].Value(2) = 0;

	auto& Pts = Data()->Points();

	// Set coords of Supertriangle
	Pts[Index_Of(v1)].X() = -100.0;
	Pts[Index_Of(v1)].Y() = -100.0;
	Pts[Index_Of(v2)].X() = +100.0;
	Pts[Index_Of(v2)].Y() = -100.0;
	Pts[Index_Of(v3)].X() = +000.0;
	Pts[Index_Of(v3)].Y() = +100.0;

	IncrementTri();

	std::list<Standard_Integer> STACK;

	Standard_Integer t, a, b, c, p;
	Standard_Integer r, erl, era, erb;

	for (Standard_Integer i = 0; i < NbPoints(); i++)
	{
		p = i + 1;
		const auto& pt = Pts[i];

		// Locate triangle in which point lies
		t = TriLoc(pt);

		// Create new vertex and adjacency lists for triangle t
		a = Neighb[t - 1].Value(0);
		b = Neighb[t - 1].Value(1);
		c = Neighb[t - 1].Value(2);

		v1 = Vtx[t - 1].Value(0);
		v2 = Vtx[t - 1].Value(1);
		v3 = Vtx[t - 1].Value(2);

		Vtx[t - 1].Value(0) = p;
		Vtx[t - 1].Value(1) = v1;
		Vtx[t - 1].Value(2) = v2;
		Neighb[t - 1].Value(0) = NbTriangles() + 2;
		Neighb[t - 1].Value(1) = a;
		Neighb[t - 1].Value(2) = NbTriangles() + 1;

		// Create new triangle
		IncrementTri();

		Vtx[NbTriangles() - 1].Value(0) = p;
		Vtx[NbTriangles() - 1].Value(1) = v2;
		Vtx[NbTriangles() - 1].Value(2) = v3;
		Neighb[NbTriangles() - 1].Value(0) = t;
		Neighb[NbTriangles() - 1].Value(1) = b;
		Neighb[NbTriangles() - 1].Value(2) = NbTriangles() + 1;

		IncrementTri();

		Vtx[NbTriangles() - 1].Value(0) = p;
		Vtx[NbTriangles() - 1].Value(1) = v3;
		Vtx[NbTriangles() - 1].Value(2) = v1;
		Neighb[NbTriangles() - 1].Value(0) = NbTriangles() - 1;
		Neighb[NbTriangles() - 1].Value(1) = c;
		Neighb[NbTriangles() - 1].Value(2) = t;

		if (a != 0) STACK.push_front(t);
		if (b != 0)
		{
			Neighb[b - 1].Value(Edge(b, t)) = NbTriangles() - 1;
			STACK.push_front(NbTriangles() - 1);
		}
		if (c != 0)
		{
			Neighb[c - 1].Value(Edge(c, t)) = NbTriangles();
			STACK.push_front(NbTriangles());
		}

		// Loop while stack is not empty
		while (!STACK.empty())
		{
			auto l = STACK.front();
			STACK.pop_front();

			r = Neighb[l - 1].Value(1);

			// Check if new point is in circumcircle for triangle R
			erl = Edge(r, l);
			era = (erl + 1) % 3;
			erb = (era + 1) % 3;
			v1 = Vtx[r - 1].Value(erl);
			v2 = Vtx[r - 1].Value(era);
			v3 = Vtx[r - 1].Value(erb);

			if (Swap(Pts[p - 1], Pts[v1 - 1], Pts[v2 - 1], Pts[v3 - 1]))
			{
				// New point is inside circumcircle for triangle R
				// Swap diagonal for convex quad formed by p-v2-v3-v1

				a = Neighb[r - 1].Value(era);
				b = Neighb[r - 1].Value(erb);
				c = Neighb[l - 1].Value(2);

				// Update vertex and adjacency list for triangle L

				Vtx[l - 1].Value(2) = v3;
				Neighb[l - 1].Value(1) = a;
				Neighb[l - 1].Value(2) = r;

				// Update vertex and adjacency list for triangle R

				Vtx[r - 1].Value(0) = p;
				Vtx[r - 1].Value(1) = v3;
				Vtx[r - 1].Value(2) = v1;
				Neighb[r - 1].Value(0) = l;
				Neighb[r - 1].Value(1) = b;
				Neighb[r - 1].Value(2) = c;

				// Put edges L-A and R-B on stack
				// Update adjacency lists for triangles A and C

				if (a != 0)
				{
					Neighb[a - 1].Value(Edge(a, r)) = l;
					STACK.push_front(l);
				}
				if (b != 0) STACK.push_front(r);
				if (c != 0) Neighb[c - 1].Value(Edge(c, l)) = r;
			}
		}
	}

	if (NbTriangles() != (2 * NbPoints() + 1))
	{
		FatalErrorIn("void tnbLib::Geo2d_DelTri::Delaunay()")
			<< "INCORRECT NUMBER OF TRIANGLES FORMED" << endl
			<< abort(FatalError);
	}

	// Remove all triangles containing supertriangle vertices
	// Find first triangle to be deleted (triangle T)
	// Update adjacency lists for triangle adjacent to T

	for (t = 1; t <= NbTriangles(); t++)
		if ((Vtx[t - 1].Value(0) > NbPoints()) || (Vtx[t - 1].Value(1) > NbPoints()) || (Vtx[t - 1].Value(2) > NbPoints()))
		{
			//cout << Vtx[t - 1][0] << "  " << Vtx[t - 1][1] << "  " << Vtx[t - 1][2] << endl;
			for (Standard_Integer i = 0; i < 3; i++)
			{
				a = Neighb[t - 1].Value(i);
				if (a != 0) Neighb[a - 1].Value(Edge(a, t)) = 0;
			}
			break;
		}

	Standard_Integer TSTRT = t + 1;
	Standard_Integer TSTOP = NbTriangles();
	ChangeNbTriangles() = t - 1;

	// Remove triangles
	for (Standard_Integer t = TSTRT; t <= TSTOP; t++)
	{
		if ((Vtx[t - 1].Value(0) > NbPoints()) || (Vtx[t - 1].Value(1) > NbPoints()) || (Vtx[t - 1].Value(2) > NbPoints()))
			for (Standard_Integer i = 0; i < 3; i++)
			{
				a = Neighb[t - 1].Value(i);
				if (a != 0) Neighb[a - 1].Value(Edge(a, t)) = 0;
			}
		else
		{
			// Triangle T is not to be deleted
			// Put triangle T in place of triangle NbTriangles()
			// Update adjacency lists for triangles adjacent to T

			IncrementTri();

			for (Standard_Integer i = 0; i < 3; i++)
			{
				a = Neighb[t - 1].Value(i);
				Neighb[NbTriangles() - 1].Value(i) = a;
				Vtx[NbTriangles() - 1].Value(i) = Vtx[t - 1].Value(i);

				if (a != 0) Neighb[a - 1].Value(Edge(a, t)) = NbTriangles();
			}
		}
	}

	Pts.resize(NbPoints());

	Vtx.resize(NbTriangles());
	Neighb.resize(NbTriangles());
}



void tnbLib::Geo2d_DelTri::Triangulate()
{
	auto& Pts = Data()->Points();

	auto xmin = Pts[0].X();
	auto xmax = xmin;
	auto ymin = Pts[0].Y();
	auto ymax = ymin;

	for (int i = 1; i < NbPoints(); i++)
	{
		xmin = MIN(xmin, Pts[i].X());
		xmax = MAX(xmax, Pts[i].X());
		ymin = MIN(ymin, Pts[i].Y());
		ymax = MAX(ymax, Pts[i].Y());
	}

	Standard_Real dmax = MAX(xmax - xmin, ymax - ymin);

	// Normalise X-Y coords of points
	Standard_Real fact = 1.0 / dmax;
	for (int i = 0; i < NbPoints(); i++)
	{
		Pts[i].X() = (Pts[i].X() - xmin)*fact;
		Pts[i].Y() = (Pts[i].Y() - ymin)*fact;
	}

	// Compute DELAUNAY TRIANGULATION
	Delaunay();

	// Reset X-Y coords to original values
	for (int i = 0; i < NbPoints(); i++)
	{
		Pts[i].X() = Pts[i].X()*dmax + xmin;
		Pts[i].Y() = Pts[i].Y()*dmax + ymin;
	}

	Change_IsDone() = Standard_True;
}