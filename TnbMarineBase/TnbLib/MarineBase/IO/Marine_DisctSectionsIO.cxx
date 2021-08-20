#include <Marine_DisctSectionsIO.hxx>

#include <Marine_SectionsIO.hxx>

tnbLib::marineLib::io::DisctSections::AlgInfo::AlgInfo()
	: Deflection(0)
	, Angle(0)
	, minSize(0)
	, maxNbSubdivision(0)
	, initNbSubdivision(0)
	, nbSmaples(0)
{
	// empty body [8/19/2021 Amir]
}

TNB_SAVE_IMPLEMENTATION(tnbLib::marineLib::io::DisctSections::AlgInfo)
{
	ar & Deflection;
	ar & Angle;
	ar & minSize;

	ar & maxNbSubdivision;
	ar & initNbSubdivision;
	ar & nbSmaples;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::marineLib::io::DisctSections::AlgInfo)
{
	ar & Deflection;
	ar & Angle;
	ar & minSize;

	ar & maxNbSubdivision;
	ar & initNbSubdivision;
	ar & nbSmaples;
}

TNB_SAVE_IMPLEMENTATION(tnbLib::marineLib::io::DisctSections)
{
	ar & theSections_;
	ar & theInfo_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::marineLib::io::DisctSections)
{
	ar & theSections_;
	ar & theInfo_;
}