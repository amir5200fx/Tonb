#include <SectPx_ConstPar.hxx>

void tnbLib::SectPx_ConstPar::Print(Ostream & out) const
{
	out << Value();
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::SectPx_ConstPar);