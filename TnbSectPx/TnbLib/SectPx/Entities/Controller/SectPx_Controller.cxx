#include <SectPx_Controller.hxx>

Standard_Boolean 
tnbLib::SectPx_Controller::IsOnPole() const
{
	return Standard_False;
}

Standard_Boolean 
tnbLib::SectPx_Controller::IsOnSegment() const
{
	return Standard_False;
}

Standard_Boolean 
tnbLib::SectPx_Controller::IsController() const
{
	return Standard_True;
}

typename tnbLib::sectPxLib::regObjType 
tnbLib::SectPx_Controller::RegObjType() const
{
	return sectPxLib::regObjType::controller;
}