#include <Cad2d_BruteForceSearchCrv.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Integer 
tnbLib::Cad2d_BruteForceSearchCrv::NbCurves() const
{
	return (Standard_Integer)theCurves_.size();
}

std::vector<std::shared_ptr<tnbLib::Pln_Edge>> 
tnbLib::Cad2d_BruteForceSearchCrv::Find
(
	const std::shared_ptr<Pln_Edge>& theCurve
) const
{
	std::vector<std::shared_ptr<Pln_Edge>> curves;
	curves.reserve(NbCurves() - 1);
	for (const auto& x : Curves())
	{
		if (x NOT_EQUAL theCurve)
		{
			curves.push_back(x);
		}
	}
	return std::move(curves);
}

std::vector<std::shared_ptr<tnbLib::Pln_Edge>> 
tnbLib::Cad2d_BruteForceSearchCrv::AllCurves() const
{
	return theCurves_;
}

void tnbLib::Cad2d_BruteForceSearchCrv::Insert(const std::shared_ptr<Pln_Edge>& theCurve)
{
	theCurves_.push_back(theCurve);
}

void tnbLib::Cad2d_BruteForceSearchCrv::Insert(std::shared_ptr<Pln_Edge>&& theCurve)
{
	theCurves_.push_back(std::move(theCurve));
}