#include <HydStatic_HeelSpacing_Arbt.hxx>

tnbLib::hydStcLib::HeelSpacing_Arbt::HeelSpacing_Arbt
(
	const std::shared_ptr<HydStatic_Spacing>& theSpacing
)
{
	SetSpacing(theSpacing);
	Change_IsDone() = Standard_True;
}

tnbLib::hydStcLib::HeelSpacing_Arbt::HeelSpacing_Arbt
(
	std::shared_ptr<HydStatic_Spacing>&& theSpacing
)
{
	SetSpacing(std::move(theSpacing));
	Change_IsDone() = Standard_True;
}

tnbLib::hydStcLib::HeelSpacing_Arbt::HeelSpacing_Arbt
(
	const Standard_Integer theIndex,
	const word & theName, 
	const std::shared_ptr<HydStatic_Spacing>& theSpacing
)
	: HydStatic_HeelSpacing(theIndex, theName)
{
	SetSpacing(theSpacing);
	Change_IsDone() = Standard_True;
}

tnbLib::hydStcLib::HeelSpacing_Arbt::HeelSpacing_Arbt
(
	const Standard_Integer theIndex,
	const word & theName, 
	std::shared_ptr<HydStatic_Spacing>&& theSpacing
)
	: HydStatic_HeelSpacing(theIndex, theName)
{
	SetSpacing(std::move(theSpacing));
	Change_IsDone() = Standard_True;
}

Standard_Boolean 
tnbLib::hydStcLib::HeelSpacing_Arbt::IsArbitrary() const
{
	return Standard_True;
}