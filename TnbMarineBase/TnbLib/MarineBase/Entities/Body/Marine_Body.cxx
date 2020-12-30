#include <Marine_Body.hxx>

#include <Marine_BodyTools.hxx>

void tnbLib::Marine_Body::CheckSections()
{
	if (NbSections() < 3)
	{
		FatalErrorIn(FunctionSIG)
			<< "the minimum nb. of sections is 3" << endl
			<< abort(FatalError);
	}

	//- the sections of the body must be the same type
	Marine_BodyTools::CheckTypeConsistency(Sections());
}

tnbLib::Marine_Body::Marine_Body
(
	const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections
)
	: theSections_(theSections)
{
	CheckSections();
}

tnbLib::Marine_Body::Marine_Body
(
	std::vector<std::shared_ptr<Marine_CmpSection>>&& theSections
)
	: theSections_(std::move(theSections))
{
	CheckSections();
}

tnbLib::Marine_Body::Marine_Body
(
	const Standard_Integer theIndex,
	const word & theName,
	const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections
)
	: Marine_CoordinatedEntity(theIndex, theName)
	, theSections_(theSections)
{
	CheckSections();
}

tnbLib::Marine_Body::Marine_Body
(
	const Standard_Integer theIndex, 
	const word & theName, 
	std::vector<std::shared_ptr<Marine_CmpSection>>&& theSections
)
	: Marine_CoordinatedEntity(theIndex, theName)
	, theSections_(std::move(theSections))
{
	CheckSections();
}

Standard_Integer 
tnbLib::Marine_Body::NbSections() const
{
	return (Standard_Integer)theSections_.size();
}
