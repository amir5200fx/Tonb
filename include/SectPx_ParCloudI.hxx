#pragma once
namespace tnbLib
{

	inline Standard_Boolean SectPx_ParCloud::IsFixed() const
	{
		return Standard_False;
	}

	inline Standard_Boolean SectPx_ParCloud::IsFree() const
	{
		return Standard_False;
	}

	inline Standard_Boolean SectPx_ParCloud::IsConstant() const
	{
		return Standard_False;
	}

	inline typename SectPx_ParCloud::realValues
		SectPx_ParCloud::operator()() const
	{
		auto values = Values();
		return std::move(values);
	}
}