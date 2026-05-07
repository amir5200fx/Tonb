#include <SectPx_FixedPar.hxx>

void tnbLib::SectPx_FixedPar::Print(Ostream & out) const
{
	out << Value();
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::SectPx_FixedPar);