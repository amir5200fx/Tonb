#include <TModel_Paired.hxx>

#include <Global_Macros.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

tnbLib::TModel_Paired::TModel_Paired
(
	const std::shared_ptr<TModel_Edge>& theEdge0,
	const std::shared_ptr<TModel_Edge>& theEdge1
)
	: theEdge0_(theEdge0)
	, theEdge1_(theEdge1)
{
}

tnbLib::TModel_Paired::TModel_Paired
(
	const Standard_Integer theIndex,
	const std::shared_ptr<TModel_Edge>& theEdge0,
	const std::shared_ptr<TModel_Edge>& theEdge1
)
	: TModel_Entity(theIndex)
	, theEdge0_(theEdge0)
	, theEdge1_(theEdge1)
{
}

tnbLib::TModel_Paired::TModel_Paired
(
	const Standard_Integer theIndex, 
	const word & theName, 
	const std::shared_ptr<TModel_Edge>& theEdge0, 
	const std::shared_ptr<TModel_Edge>& theEdge1
)
	: TModel_Entity(theIndex, theName)
	, theEdge0_(theEdge0)
	, theEdge1_(theEdge1)
{
}

Standard_Boolean 
tnbLib::TModel_Paired::IsFree() const
{
	return NOT Edge0() OR NOT Edge1();
}

const std::shared_ptr<tnbLib::TModel_Edge>& 
tnbLib::TModel_Paired::Other
(
	const std::shared_ptr<TModel_Edge>& theEdge
)
{
	if (theEdge == theEdge0_)
	{
		return theEdge1_;
	}

	if (theEdge == theEdge1_)
	{
		return theEdge0_;
	}

	FatalErrorIn("const std::shared_ptr<TModel_Edge>& Other(const std::shared_ptr<TModel_Edge>& theEdge) const")
		<< "Invalid Data" << endl
		<< abort(FatalError);

	return theEdge0_;
}