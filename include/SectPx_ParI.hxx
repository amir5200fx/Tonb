#pragma once
namespace tnbLib
{

	inline Standard_Boolean 
		SectPx_Par::IsFixed() const
	{
		return Standard_False;
	}

	inline Standard_Boolean 
		SectPx_Par::IsFree() const
	{
		return Standard_False;
	}

	inline Standard_Boolean 
		SectPx_Par::IsConstant() const
	{
		return Standard_False;
	}

	inline Standard_Real 
		SectPx_Par::operator()() const
	{
		return Value();
	}
}