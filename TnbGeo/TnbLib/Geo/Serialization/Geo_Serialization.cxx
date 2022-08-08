#include <Geo_Serialization.hxx>

#include <Poly_Triangulation.hxx>
#include <gp_Pln.hxx>

template<>
void boost::serialization::save
(
	TNB_oARCH_TYPE & ar,
	const Poly_Triangle& sr,
	const unsigned int version
)
{
	ar << sr.Value(1);
	ar << sr.Value(2);
	ar << sr.Value(3);
}

template<>
void boost::serialization::load
(
	TNB_iARCH_TYPE & ar,
	Poly_Triangle& s,
	const unsigned int version
)
{
	ar >> s.ChangeValue(1);
	ar >> s.ChangeValue(2);
	ar >> s.ChangeValue(3);
}

template<>
void boost::serialization::save
(
	TNB_oARCH_TYPE & ar,
	const TShort_Array1OfShortReal& sr,
	const unsigned int version
)
{
	ar << sr.Size();
	forThose(id, 1, sr.Size())
	{
		ar << sr.Value(id);
	}
}

template<>
void boost::serialization::load
(
	TNB_iARCH_TYPE & ar,
	TShort_Array1OfShortReal& s,
	const unsigned int version
)
{
	Standard_Integer size;
	ar >> size;
	s.Resize(1, size, Standard_False);
	forThose(id, 1, s.Size())
	{
		ar >> s.ChangeValue(id);
	}
}

template<>
void boost::serialization::save
(
	TNB_oARCH_TYPE & ar,
	const Poly_Array1OfTriangle& sr,
	const unsigned int version
)
{
	ar << sr.Size();
	forThose(id, 1, sr.Size())
	{
		ar << sr.Value(id);
	}
}

template<>
void boost::serialization::load
(
	TNB_iARCH_TYPE & ar,
	Poly_Array1OfTriangle& s,
	const unsigned int version
)
{
	Standard_Integer size;
	ar >> size;
	s.Resize(1, size, Standard_False);
	forThose(id, 1, s.Size())
	{
		ar >> s.ChangeValue(id);
	}
}

//template<>
//void boost::serialization::save
//(
//	TNB_oARCH_TYPE & ar,
//	const Handle(Poly_Triangulation)& sr,
//	const unsigned int version
//)
//{
//	ar << sr->Deflection();
//	ar << sr->Nodes();
//	ar << sr->HasUVNodes();
//	if (sr->HasUVNodes())
//	{
//		ar << sr->UVNodes();
//	}
//	ar << sr->Triangles();
//	ar << sr->HasNormals();
//	if (sr->HasNormals())
//	{
//		ar << sr->Normals();
//	}
//}

//template<>
//void boost::serialization::load
//(
//	TNB_iARCH_TYPE & ar,
//	Handle(Poly_Triangulation)& s,
//	const unsigned int version
//)
//{
//	Standard_Real def;
//	ar >> def;
//
//	TColgp_Array1OfPnt nodes;
//	ar >> nodes;
//
//	Standard_Boolean hasUv;
//	ar >> hasUv;
//	TColgp_Array1OfPnt2d uvNodes;
//	if (hasUv)
//	{
//		ar >> uvNodes;
//	}
//
//	Poly_Array1OfTriangle triangles;
//	ar >> triangles;
//
//	Handle(TShort_HArray1OfShortReal) normals = new TShort_HArray1OfShortReal(1, 1);
//	Standard_Boolean hasNormals;
//	ar >> hasNormals;
//	if (hasNormals)
//	{
//		ar >> normals->ChangeArray1();
//	}
//
//	if (hasUv)
//	{
//		s = new Poly_Triangulation(nodes, uvNodes, triangles);
//	}
//	else
//	{
//		s = new Poly_Triangulation(nodes, triangles);
//	}
//
//	if (hasNormals)
//	{
//		s->SetNormals(normals);
//	}
//}

template<>
void boost::serialization::save
(
	TNB_oARCH_TYPE & ar,
	const TColgp_Array1OfPnt2d& sr,
	const unsigned int version
)
{
	ar << sr.Size();
	forThose(id, 1, sr.Size())
	{
		ar << sr.Value(id);
	}
}

template<>
void boost::serialization::load
(
	TNB_iARCH_TYPE & ar,
	TColgp_Array1OfPnt2d& s,
	const unsigned int version
)
{
	Standard_Integer size;
	ar >> size;
	s.Resize(1, size, Standard_False);
	forThose(id, 1, s.Size())
	{
		ar >> s.ChangeValue(id);
	}
}

template<>
void boost::serialization::save
(
	TNB_oARCH_TYPE & ar,
	const TColgp_Array1OfPnt& sr,
	const unsigned int version
)
{
	ar << sr.Size();
	forThose(id, 1, sr.Size())
	{
		ar << sr.Value(id);
	}
}

template<>
void boost::serialization::load
(
	TNB_iARCH_TYPE & ar,
	TColgp_Array1OfPnt& s,
	const unsigned int version
)
{
	Standard_Integer size;
	ar >> size;
	s.Resize(1, size, Standard_False);
	forThose(id, 1, s.Size())
	{
		ar >> s.ChangeValue(id);
	}
}

template<>
void boost::serialization::save
(
	TNB_oARCH_TYPE & ar,
	const gp_Pln& sr,
	const unsigned int version
)
{
	ar << sr.Location();
	ar << sr.Direct();
}

template<>
void boost::serialization::load
(
	TNB_iARCH_TYPE & ar,
	gp_Pln& s,
	const unsigned int version
)
{
	gp_Pnt p;
	gp_Dir d;
	ar >> p;
	ar >> d;
	s = gp_Pln(p, d);
}