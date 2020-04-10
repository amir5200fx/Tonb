#include <Marine_CG.hxx>

tnbLib::Marine_CG::Marine_CG
(
	const std::shared_ptr<Marine_LCG>& theLcg, 
	const std::shared_ptr<Marine_VCG>& theVcg,
	const std::shared_ptr<Marine_TCG>& theTcg
)
	: theLCG_(theLcg)
	, theTCG_(theTcg)
	, theVCG_(theVcg)
{
}

tnbLib::Marine_CG::Marine_CG
(
	const Standard_Integer theIndex, 
	const word & theName, 
	const std::shared_ptr<Marine_LCG>& theLcg,
	const std::shared_ptr<Marine_VCG>& theVcg,
	const std::shared_ptr<Marine_TCG>& theTcg
)
	: Marine_Entity(theIndex, theName)
	, theLCG_(theLcg)
	, theTCG_(theTcg)
	, theVCG_(theVcg)
{
}