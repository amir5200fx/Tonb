#pragma once
#include <TnbError.hxx>
#include <OSstream.hxx>
namespace tnbLib
{
	inline Geo_MxCifQuadtree_Base::Axis 
		Geo_MxCifQuadtree_Base::OTHERAXIS
		(
			const Axis theAx
		)
	{
		switch (theAx)
		{
		case Axis::X: return Axis::Y;
		case Axis::Y: return Axis::X;
		default:
			FatalErrorIn("Axis OTHERAXIS(const Axis)")
				<< "invalid data!" << endl
				<< abort(FatalError);
			return theAx;
		}
	}

	inline Geo_MxCifQuadtree_Base::QuadCompare 
		Geo_MxCifQuadtree_Base::CQUAD
		(
			const QuadCompare q
		)
	{
		switch (q)
		{
		case QuadCompare::SW: return QuadCompare::NW;
		case QuadCompare::SE: return QuadCompare::SW;
		case QuadCompare::NE: return QuadCompare::SE;
		case QuadCompare::NW: return QuadCompare::NE;
		default:
			FatalErrorIn("QuadCompare CQUAD(const QuadCompare)")
				<< "invalid data!" << endl
				<< abort(FatalError);
			return QuadCompare::SW;
		}
	}

	inline Geo_MxCifQuadtree_Base::QuadCompare
		Geo_MxCifQuadtree_Base::CCQUAD
		(
			const QuadCompare q
		)
	{
		switch (q)
		{
		case QuadCompare::SW: return QuadCompare::SE;
		case QuadCompare::SE: return QuadCompare::NE;
		case QuadCompare::NE: return QuadCompare::NW;
		case QuadCompare::NW: return QuadCompare::SW;
		default:
			FatalErrorIn("QuadCompare CCQUAD(const QuadCompare)")
				<< "invalid data!" << endl
				<< abort(FatalError);
			return QuadCompare::SW;
		}
	}

	inline Geo_MxCifQuadtree_Base::QuadCompare 
		Geo_MxCifQuadtree_Base::OPQUAD
		(
			const QuadCompare q
		)
	{
		switch (q)
		{
		case QuadCompare::SW: return QuadCompare::NE;
		case QuadCompare::SE: return QuadCompare::NW;
		case QuadCompare::NE: return QuadCompare::SW;
		case QuadCompare::NW: return QuadCompare::SE;
		default:
			FatalErrorIn("QuadCompare OPQUAD(const QuadCompare)")
				<< "invalid data!" << endl
				<< abort(FatalError);
			return QuadCompare::SW;
		}
	}

	inline Standard_Integer 
		tnbLib::Geo_MxCifQuadtree_Base::GetIndex
		(
			const Axis ax
		)
	{
		switch (ax)
		{
		case Axis::X: return 0;
		case Axis::Y: return 1;
		default:
			FatalErrorIn("QuadCompare OPQUAD(const QuadCompare)")
				<< "invalid data!" << endl
				<< abort(FatalError);
			return -1;
		}
	}

	inline Geo_MxCifQuadtree_Base::TreeCompare 
		Geo_MxCifQuadtree_Base::BinCompare
		(
			const Entity2d_Box & theBox,
			const Standard_Real theX, 
			const Axis theAxis
		)
	{
		Standard_Real x0, x1;
		theBox.GetBound(GetIndex(theAxis), x0, x1);

		const auto cx = MEAN(x0, x1);
		const auto lx = x1 - x0;

		if (cx - lx <= theX AND theX < cx + lx)
		{
			return TreeCompare::BOTH;
		}
		else if (theX < cx)
		{
			return TreeCompare::RIGHT;
		}
		else
		{
			return TreeCompare::LEFT;
		}
	}

	inline Geo_MxCifQuadtree_Base::TreeCompare 
		Geo_MxCifQuadtree_Base::OPDIRECTION
		(
			const TreeCompare d
		)
	{
		switch (d)
		{
		case TreeCompare::LEFT: return TreeCompare::RIGHT;
		case TreeCompare::RIGHT: return TreeCompare::LEFT;
		default:
			FatalErrorIn("TreeCompare OPDIRECTION(const TreeCompare d)")
				<< "Invalid data!" << endl
				<< abort(FatalError);
			return TreeCompare::BOTH;
		}
	}

	inline Geo_MxCifQuadtree_Base::QuadCompare 
		Geo_MxCifQuadtree_Base::CIFCompare
		(
			const Entity2d_Box & theBox,
			const Pnt2d & theCx
		)
	{
		const auto c = theBox.CalcCentre();
		if (c.X() < theCx.X())
		{
			if (c.Y() < theCx.Y()) return QuadCompare::SW;
			else return QuadCompare::NW;
		}
		else if (c.Y() < theCx.Y()) return QuadCompare::SE;
		else return QuadCompare::NE;
	}

	inline Standard_Real 
		Geo_MxCifQuadtree_Base::VF
		(
			const TreeCompare t
		)
	{
		switch (t)
		{
		case TreeCompare::LEFT: return -1.0;
		case TreeCompare::RIGHT: return +1.0;
		default:
			FatalErrorIn("Standard_Real VF(const TreeCompare t)")
				<< "Invalid data!" << endl
				<< abort(FatalError);
			return 0;
		}
	}

	inline Standard_Real 
		Geo_MxCifQuadtree_Base::XF
		(
			const QuadCompare t
		)
	{
		switch (t)
		{
		case QuadCompare::NW: return -1.0;
		case QuadCompare::NE: return +1.0;
		case QuadCompare::SW: return -1.0;
		case QuadCompare::SE: return +1.0;
		default:
			FatalErrorIn("Standard_Real XF(const TreeCompare t)")
				<< "Invalid data!" << endl
				<< abort(FatalError);
			return 0;
		}
	}

	inline Standard_Real 
		Geo_MxCifQuadtree_Base::YF
		(
			const QuadCompare t
		)
	{
		switch (t)
		{
		case QuadCompare::NW: return +1.0;
		case QuadCompare::NE: return +1.0;
		case QuadCompare::SW: return -1.0;
		case QuadCompare::SE: return -1.0;
		default:
			FatalErrorIn("Standard_Real YF(const TreeCompare t)")
				<< "Invalid data!" << endl
				<< abort(FatalError);
			return 0;
		}
	}

	template<class T>
	const std::shared_ptr<typename Geo_MxCifQuadtree<T>::node>&
		Geo_MxCifQuadtree<T>::BIN
		(
			const std::shared_ptr<quad>& t,
			const Axis ax
		)
	{
		switch (ax)
		{
		case Axis::X: return t->AxisX();
		case Axis::Y: return t->AxisY();
		default:
			FatalErrorIn("const std::shared_ptr<node>& BIN(const std::shared_ptr<quad>& t, const Axis)")
				<< "Invalid data!" << endl
				<< abort(FatalError);
			return quad::null;
		}
	}

	template<class T>
	std::shared_ptr<typename Geo_MxCifQuadtree<T>::node>& 
		Geo_MxCifQuadtree<T>::ChangeBIN
		(
			const std::shared_ptr<quad>& t,
			const Axis ax
		)
	{
		switch (ax)
		{
		case Axis::X: return t->AxisX();
		case Axis::Y: return t->AxisY();
		default:
			FatalErrorIn("const std::shared_ptr<node>& ChangeBIN(const std::shared_ptr<quad>& t, const Axis)")
				<< "Invalid data!" << endl
				<< abort(FatalError);
			return quad::null;
		}
	}

	template<class T>
	const std::shared_ptr<typename Geo_MxCifQuadtree<T>::node>&
		Geo_MxCifQuadtree<T>::SON
		(
			const std::shared_ptr<node>& t, 
			const TreeCompare c
		)
	{
		switch (c)
		{
		case TreeCompare::LEFT: return t->Left();
		case TreeCompare::RIGHT: return t->Right();
		default:
			return node::null;
		}
	}

	template<class T>
	std::shared_ptr<typename Geo_MxCifQuadtree<T>::node>&
		Geo_MxCifQuadtree<T>::ChangeSON
		(
			const std::shared_ptr<node>& t, 
			const TreeCompare c
		)
	{
		switch (c)
		{
		case TreeCompare::LEFT: return t->Left();
		case TreeCompare::RIGHT: return t->Right();
		default:
			return node::null;
		}
	}

	template<class T>
	const std::shared_ptr<typename Geo_MxCifQuadtree<T>::quad>&
		Geo_MxCifQuadtree<T>::SON
		(
			const std::shared_ptr<quad>& t,
			const QuadCompare q
		)
	{
		switch (q)
		{
		case QuadCompare::NW: return t->NW();
		case QuadCompare::NE: return t->NE();
		case QuadCompare::SW: return t->SW();
		case QuadCompare::SE: return t->SE();
		default:
			return quad::null;
		}
	}

	template<class T>
	std::shared_ptr<typename Geo_MxCifQuadtree<T>::quad>&
		Geo_MxCifQuadtree<T>::ChangeSON
		(
			const std::shared_ptr<quad>& t, 
			const QuadCompare q
		)
	{
		switch (q)
		{
		case QuadCompare::NW: return t->NW();
		case QuadCompare::NE: return t->NE();
		case QuadCompare::SW: return t->SW();
		case QuadCompare::SE: return t->SE();
		default:
			return quad::null;
		}
	}

	template<class T>
	Standard_Boolean 
		Geo_MxCifQuadtree<T>::Intersection
		(
			const Entity2d_Box & theB,
			const Pnt2d & theCx,
			const Pnt2d & theLx
		)
	{
		Entity2d_Box b(theCx - theLx, theCx + theLx);
		return b.IsIntersect(theB);
	}

	template<class T>
	Geo_MxCifQuadtree<T>::Geo_MxCifQuadtree()
	{
	}

	template<class T>
	void Geo_MxCifQuadtree<T>::InsertAxis
	(
		const std::shared_ptr<T>& theItem, 
		const std::shared_ptr<quad>& theCurrent, 
		const Standard_Real theCx, 
		const Standard_Real theLx,
		const Axis ax
	)
	{
		auto lx = theLx;
		auto cx = theCx;
		auto t = BIN(theCurrent, ax);
		if (NOT t)
		{

			t = ChangeBIN(theCurrent, ax);
			t = std::make_shared<node>();
		}

		const auto& b = GetBox_(theItem);
		auto d = BinCompare(b, theCx, ax);

		while (d NOT_EQUAL TreeCompare::BOTH)
		{
			auto father = t;

			t = SON(t, d);
			if (NOT t)
			{
				t = ChangeSON(father, d);
				t = std::make_shared<node>();
			}

			lx *= 0.5;
			cx += VF(d)*lx;

			d = BinCompare(b, cx, ax);
		}

		t->Insert(GetIndex_(theItem), theItem);
	}

	template<class T>
	void Geo_MxCifQuadtree<T>::Insert
	(
		const std::shared_ptr<T>& theItem,
		const std::shared_ptr<quad>& theRoot, 
		const Pnt2d & theCx,
		const Pnt2d & theLx
	)
	{
		auto t = theRoot;
		const auto& b = GetBox_(theItem);

		if (NOT t)
		{
			t = std::make_shared<quad>();
		}

		auto dx = BinCompare(b, theCx.Coord(GetIndex(Axis::X) + 1), Axis::X);
		auto dy = BinCompare(b, theCx.Coord(GetIndex(Axis::Y) + 1), Axis::Y);

		auto lx = theLx.X();
		auto ly = theLx.Y();

		auto cx = theCx.X();
		auto cy = theCx.Y();

		while
			(
				dx NOT_EQUAL TreeCompare::BOTH AND
				dy NOT_EQUAL TreeCompare::BOTH 
				)
		{
			auto q = CIFCompare(b, theCx);

			auto father = t;
			t = SON(t, q);

			if (NOT t)
			{
				t = ChangeSON(father, q);
				t = std::make_shared<quad>();
			}

			lx *= 0.5;
			ly *= 0.5;

			cx += XF(q)*lx;
			cy += YF(q)*ly;

			auto Cx = Pnt2d(cx, cy);

			dx = BinCompare(b, Cx.Coord(GetIndex(Axis::X) + 1), Axis::X);
			dy = BinCompare(b, Cx.Coord(GetIndex(Axis::Y) + 1), Axis::Y);
		}

		if (dx IS_EQUAL TreeCompare::BOTH)
		{
			InsertAxis(theItem, t, cy, ly, Axis::Y);
		}
		else
		{
			InsertAxis(theItem, t, cx, lx, Axis::X);
		}
	}

	template<class T>
	void Geo_MxCifQuadtree<T>::Remove
	(
		const std::shared_ptr<T>& theItem, 
		std::shared_ptr<quad>& theRoot,
		const Pnt2d & theCx,
		const Pnt2d & theLx
	)
	{
		if (NOT theRoot)
		{
			return; // the tree is empty
		}

		auto t = theRoot;
		std::shared_ptr<quad> ft;
		QuadCompare qf;

		auto lx = theLx.X();
		auto ly = theLx.Y();

		auto cx = theCx.X();
		auto cy = theCx.Y();

		const auto& box = GetBox_(theItem);
		while
			(
				BinCompare(box, theCx.Coord(GetIndex(Axis::X) + 1), Axis::X) NOT_EQUAL TreeCompare::BOTH AND
				BinCompare(box, theCx.Coord(GetIndex(Axis::Y) + 1), Axis::Y) NOT_EQUAL TreeCompare::BOTH 
				)
		{
			//- Locate the quadrant in which P belongs
			auto q = CIFCompare(box, theCx);
			if (NOT SON(t, q))
			{
				FatalErrorIn("void Remove(Args..)")
					<< "the item is not in the tree!" << endl
					<< abort(FatalError);
			}

			if (
				SON(t, CQUAD(q)) OR
				SON(t, CCQUAD(q)) OR
				SON(t, OPQUAD(q)) OR
				BIN(t, Axis::X) OR
				BIN(t, Axis::Y) 
				)
			{
				ft = t;
				qf = q;
			}

			t = SON(t, q);

			lx *= 0.5;
			ly *= 0.5;

			cx += XF(q)*lx;
			cy += YF(q)*ly;
		}

		Axis v;
		if (BinCompare(box, theCx.Coord(GetIndex(Axis::X) + 1), Axis::X) IS_EQUAL TreeCompare::BOTH)
		{
			v = Axis::X;
		}

		if (BinCompare(box, theCx.Coord(GetIndex(Axis::Y) + 1), Axis::Y) IS_EQUAL TreeCompare::BOTH)
		{
			v = Axis::Y;
		}

		v = OTHERAXIS(v);  // Reset the axis since v = cv passes through P

		auto rb = t;
		std::shared_ptr<node> fb;
		auto b = BIN(t, v);

		auto Cx = Pnt2d(cx, cy);
		auto Lx = Pnt2d(lx, ly);

		auto cv = Cx.Coord(GetIndex(v) + 1);
		auto lv = Lx.Coord(GetIndex(v) + 1);

		auto d = BinCompare(box, cv, v);
		TreeCompare df;

		while (b AND d NOT_EQUAL TreeCompare::BOTH)
		{
			if (SON(b, OPDIRECTION(d)) OR b->NbItems())
			{
				fb = b;
				df = d;
			}

			b = SON(b, d);
			lv *= 0.5;
			cv += VF(d)*lv;
			d = BinCompare(box, cv, v);
		}

		if (NOT b)
		{
			FatalErrorIn("void Remove(Args..)")
				<< "the item is not in the tree!" << endl
				<< abort(FatalError);
		}

		auto& items = b->Items();
		auto iter = items.find(GetIndex_(theItem));
		if (iter IS_EQUAL items.end())
		{
			FatalErrorIn("void Remove(Args..)")
				<< "the item is not in the tree!" << endl
				<< abort(FatalError);
		}

		items.erase(iter);

		if (SON(b, TreeCompare::LEFT) OR SON(b, TreeCompare::RIGHT))
		{
			//- no collapsing is possible		
		}
		else if (items.empty()) /*Attempt to perform collapsing*/
		{
			auto& tb = fb ? ChangeSON(fb, df) : ChangeBIN(rb, v);
			tb.reset();
		}

		if (fb)
		{
			/*the v axis is not empty*/
			ChangeSON(fb, df).reset();

		}
		else
		{
			ChangeBIN(rb, v).reset();

			if (
				BIN(rb, OTHERAXIS(v)) OR 
				SON(rb, QuadCompare::NW) OR 
				SON(rb, QuadCompare::NE) OR 
				SON(rb, QuadCompare::SW) OR 
				SON(rb, QuadCompare::SE)
				)
			{
				return;
			}

			t = ft ? ChangeSON(ft, qf) : theRoot;

			t.reset();
		}
	}

	template<class T>
	void Geo_MxCifQuadtree<T>::Search
	(
		const Entity2d_Box & theArea, 
		const std::shared_ptr<quad>& theRoot,
		const Pnt2d & theCx, 
		const Pnt2d & theLx,
		std::vector<std::shared_ptr<T>>& theList
	) const
	{
		if (NOT theRoot)
		{
			return;
		}
		
		if (NOT Intersection(theArea, theCx, theLx))
		{
			return;
		}

		CrossAxis(theArea, BIN(theRoot, Axis::X), theCx.X(), theLx.X(), Axis::X, theList);
		CrossAxis(theArea, BIN(theRoot, Axis::Y), theCx.Y(), theLx.Y(), Axis::Y, theList);

		auto lx = theLx.X()*0.5;
		auto ly = theLx.Y()*0.5;

		Search
		(
			theArea,
			SON(theRoot, QuadCompare::NE), 
			theCx + Pnt2d(XF(QuadCompare::NE)*lx, YF(QuadCompare::NE)*ly), 
			Pnt2d(lx, ly), theList
		);

		Search
		(
			theArea,
			SON(theRoot, QuadCompare::NW),
			theCx + Pnt2d(XF(QuadCompare::NW)*lx, YF(QuadCompare::NW)*ly),
			Pnt2d(lx, ly), theList
		);

		Search
		(
			theArea,
			SON(theRoot, QuadCompare::SW),
			theCx + Pnt2d(XF(QuadCompare::SW)*lx, YF(QuadCompare::SW)*ly),
			Pnt2d(lx, ly), theList
		);

		Search
		(
			theArea,
			SON(theRoot, QuadCompare::SE),
			theCx + Pnt2d(XF(QuadCompare::SE)*lx, YF(QuadCompare::SE)*ly),
			Pnt2d(lx, ly), theList
		);
	}

	template<class T>
	void Geo_MxCifQuadtree<T>::CrossAxis
	(
		const Entity2d_Box & theArea, 
		const std::shared_ptr<node>& theRoot, 
		const Standard_Real theCx, 
		const Standard_Real theLx,
		const Axis theAxis,
		std::vector<std::shared_ptr<T>>& theList
	) const
	{
		if (NOT theRoot)
		{
			return;
		}
		else if (theRoot->NbItems())
		{
			for (const auto& x : theRoot->Items())
			{
				Debug_Null_Pointer(x.second);
				const auto& item = x.second;

				if (theArea.IsIntersect(GetBox_(item)))
				{
					theList.push_back(item);
				}
			}
		}
		else
		{
			auto d = BinCompare(theArea, theCx, theAxis);
			auto lx = 0.5*theLx;

			if (d IS_EQUAL TreeCompare::BOTH)
			{
				CrossAxis(theArea, SON(theRoot, TreeCompare::LEFT), theCx - lx, lx, theAxis, theList);
				CrossAxis(theArea, SON(theRoot, TreeCompare::RIGHT), theCx + lx, lx, theAxis, theList);
			}
			else
			{
				CrossAxis(theArea, SON(theRoot, d), theCx + VF(d)*lx, lx, theAxis, theList);
			}
		}
	}

	
}