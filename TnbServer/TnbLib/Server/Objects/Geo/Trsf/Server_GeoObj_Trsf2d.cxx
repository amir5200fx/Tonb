#include <Server_GeoObj_Trsf2d.hxx>

#include <Geo_Serialization.hxx>
#include <Pnt2d.hxx>

#include <json.hpp>

implementTnbServerConstruction(Server_GeoObj_Trsf2d)
{
	gp_Trsf2d t;
	streamGoodTnbServerObject(t);
}

implementTnbServerParam(Server_GeoObj_Trsf2d_Mirror_By_Axis, trsf, "trsf");
implementTnbServerParam(Server_GeoObj_Trsf2d_Mirror_By_Axis, axis, "axis");

implementTnbServerConstruction(Server_GeoObj_Trsf2d_Mirror_By_Axis)
{
	gp_Trsf2d trsf;
	gp_Ax2d axis;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(trsf);
		}
		{
			loadTnbServerObject(axis);
		}
	}
	try
	{
		trsf.SetTransformation(axis);
		streamGoodTnbServerObject(trsf);
	}
	catchTnbServerErrors()
}

implementTnbServerParam(Server_GeoObj_Trsf2d_Mirror_By_Pnt, trsf, "trsf");
implementTnbServerParam(Server_GeoObj_Trsf2d_Mirror_By_Pnt, pnt, "pnt");

implementTnbServerConstruction(Server_GeoObj_Trsf2d_Mirror_By_Pnt)
{
	gp_Trsf2d trsf;
	Pnt2d pnt;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(trsf);
		}
		{
			loadTnbServerObject(pnt);
		}
	}
	try
	{
		trsf.SetMirror(pnt);
		streamGoodTnbServerObject(trsf);
	}
	catchTnbServerErrors()
}

implementTnbServerParam(Server_GeoObj_Trsf2d_Rotation, trsf, "trsf");
implementTnbServerParam(Server_GeoObj_Trsf2d_Rotation, pnt, "pnt");
implementTnbServerParam(Server_GeoObj_Trsf2d_Rotation, angle, "angle");

implementTnbServerConstruction(Server_GeoObj_Trsf2d_Rotation)
{
	gp_Trsf2d trsf;
	Pnt2d pnt;
	double angle;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(trsf);
		}
		{
			loadTnbServerObject(pnt);
		}
		{
			loadTnbServerObject(angle);
		}
	}
	try
	{
		trsf.SetRotation(pnt, angle);
		streamGoodTnbServerObject(trsf);
	}
	catchTnbServerErrors()
}

implementTnbServerParam(Server_GeoObj_Trsf2d_Scale, trsf, "trsf");
implementTnbServerParam(Server_GeoObj_Trsf2d_Scale, pnt, "pnt");
implementTnbServerParam(Server_GeoObj_Trsf2d_Scale, scale, "scale");

implementTnbServerConstruction(Server_GeoObj_Trsf2d_Scale)
{
	gp_Trsf2d trsf;
	Pnt2d pnt;
	double scale;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(trsf);
		}
		{
			loadTnbServerObject(pnt);
		}
		{
			loadTnbServerObject(scale);
		}
	}
	try
	{
		trsf.SetScale(pnt, scale);
		streamGoodTnbServerObject(trsf);
	}
	catchTnbServerErrors()
}

implementTnbServerParam(Server_GeoObj_Trsf2d_TrnsFromS1ToS2, trsf, "trsf");
implementTnbServerParam(Server_GeoObj_Trsf2d_TrnsFromS1ToS2, axis1, "axis1");
implementTnbServerParam(Server_GeoObj_Trsf2d_TrnsFromS1ToS2, axis2, "axis2");

implementTnbServerConstruction(Server_GeoObj_Trsf2d_TrnsFromS1ToS2)
{
	gp_Trsf2d trsf;
	gp_Ax2d axis1;
	gp_Ax2d axis2;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(trsf);
		}
		{
			loadTnbServerObject(axis1);
		}
		{
			loadTnbServerObject(axis2);
		}
	}
	try
	{
		trsf.SetTransformation(axis1, axis2);
		streamGoodTnbServerObject(trsf);
	}
	catchTnbServerErrors()
}

implementTnbServerParam(Server_GeoObj_Trsf2d_TransfTo, trsf, "trsf");
implementTnbServerParam(Server_GeoObj_Trsf2d_TransfTo, axis, "axis");

implementTnbServerConstruction(Server_GeoObj_Trsf2d_TransfTo)
{
	gp_Trsf2d trsf;
	gp_Ax2d axis;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(trsf);
		}
		{
			loadTnbServerObject(axis);
		}
	}
	try
	{
		trsf.SetTransformation(axis);
		streamGoodTnbServerObject(trsf);
	}
	catchTnbServerErrors()
}

implementTnbServerParam(Server_GeoObj_Trsf2d_Translation, trsf, "trsf");
implementTnbServerParam(Server_GeoObj_Trsf2d_Translation, pnt1, "pnt1");
implementTnbServerParam(Server_GeoObj_Trsf2d_Translation, pnt2, "pnt2");

implementTnbServerConstruction(Server_GeoObj_Trsf2d_Translation)
{
	gp_Trsf2d trsf;
	Pnt2d pnt1;
	Pnt2d pnt2;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(trsf);
		}
		{
			loadTnbServerObject(pnt1);
		}
		{
			loadTnbServerObject(pnt2);
		}
	}
	try
	{
		trsf.SetTranslation(pnt1, pnt2);
		streamGoodTnbServerObject(trsf);
	}
	catchTnbServerErrors()
}

implementTnbServerParam(Server_GeoObj_Trsf2d_Values, trsf, "trsf");
implementTnbServerParam(Server_GeoObj_Trsf2d_Values, a11, "a11");
implementTnbServerParam(Server_GeoObj_Trsf2d_Values, a12, "a12");
implementTnbServerParam(Server_GeoObj_Trsf2d_Values, a13, "a13");
implementTnbServerParam(Server_GeoObj_Trsf2d_Values, a21, "a21");
implementTnbServerParam(Server_GeoObj_Trsf2d_Values, a22, "a22");
implementTnbServerParam(Server_GeoObj_Trsf2d_Values, a23, "a23");

implementTnbServerConstruction(Server_GeoObj_Trsf2d_Values)
{
	gp_Trsf2d trsf;
	double a11, a12, a13, a21, a22, a23;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(trsf);
		}
		{
			loadTnbServerObject(a11);
		}
		{
			loadTnbServerObject(a12);
		}
		{
			loadTnbServerObject(a13);
		}
		{
			loadTnbServerObject(a21);
		}
		{
			loadTnbServerObject(a22);
		}
		{
			loadTnbServerObject(a23);
		}
	}
	try
	{
		trsf.SetValues(a11, a12, a13, a21, a22, a23);
		streamGoodTnbServerObject(trsf);
	}
	catchTnbServerErrors()
}