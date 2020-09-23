#pragma once
#include <SectPx_Registry.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	template<class FieldFun>
	std::shared_ptr<FieldFun> 
		SectPx_oneParFieldFun::Maker
		(
			const std::shared_ptr<SectPx_Registry>& theReg,
			const Standard_Integer theParId
		)
	{
		auto field = std::make_shared<FieldFun>();
		Debug_Null_Pointer(field);

		theReg->Import(field);

		Debug_Null_Pointer(SELECT_PAR_FROM_REGISTRY(theReg, theParId));
		field->SetPar(SELECT_PAR_FROM_REGISTRY(theReg, theParId));
		return std::move(field);
	}
}