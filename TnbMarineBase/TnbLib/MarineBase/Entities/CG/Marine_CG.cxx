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
	// empty body
}

tnbLib::Marine_CG::Marine_CG
(
	std::shared_ptr<Marine_LCG>&& theLcg,
	std::shared_ptr<Marine_VCG>&& theVcg, 
	std::shared_ptr<Marine_TCG>&& theTcg
)
	: theLCG_(std::move(theLcg))
	, theTCG_(std::move(theTcg))
	, theVCG_(std::move(theVcg))
{
	// empty body
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
	// empty body
}

tnbLib::Marine_CG::Marine_CG
(
	const Standard_Integer theIndex,
	const word & theName,
	std::shared_ptr<Marine_LCG>&& theLcg, 
	std::shared_ptr<Marine_VCG>&& theVcg,
	std::shared_ptr<Marine_TCG>&& theTcg
)
	: Marine_Entity(theIndex, theName)
	, theLCG_(std::move(theLcg))
	, theTCG_(std::move(theTcg))
	, theVCG_(std::move(theVcg))
{
}