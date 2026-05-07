#pragma once
#include <TnbError.hxx>
#include <OSstream.hxx>
inline Standard_Boolean tnbLib::TModel_Surface::IsLess
(
	const std::shared_ptr<TModel_Surface>& theS0,
	const std::shared_ptr<TModel_Surface>& theS1
)
{
	Debug_Null_Pointer(theS0);
	Debug_Null_Pointer(theS1);
	return theS0->Index() < theS1->Index();
}