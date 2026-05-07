#include <SectPx_CompOffset.hxx>

#include <SectPx_FieldFun.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

tnbLib::SectPx_CompOffset
<
	Standard_Real,
	tnbLib::SectPx_FieldFun
>::SectPx_CompOffset
(
	const Standard_Real x, 
	const std::shared_ptr<SectPx_FieldFun>& y
)
	: theX_(x)
	, theY_(y)
{
	// empty body
}

Standard_Real
tnbLib::SectPx_CompOffset<Standard_Real, tnbLib::SectPx_FieldFun>::yCoord() const
{
	auto x = theY_.lock();
	if (NOT x)
	{
		FatalErrorIn(FunctionSIG)
			<< "no field function is set for the y-coord" << endl
			<< abort(FatalError);
	}
	return x->Value();
}

tnbLib::SectPx_CompOffset
<
	tnbLib::SectPx_FieldFun,
	Standard_Real
>::SectPx_CompOffset
(
	const std::shared_ptr<SectPx_FieldFun>& x,
	const Standard_Real y
)
	: theX_(x)
	, theY_(y)
{
	// empty body
}

Standard_Real
tnbLib::SectPx_CompOffset<tnbLib::SectPx_FieldFun, Standard_Real>::xCoord() const
{
	auto x = theX_.lock();
	if (NOT x)
	{
		FatalErrorIn(FunctionSIG)
			<< "no field function is set for the x-coord" << endl
			<< abort(FatalError);
	}
	return x->Value();
}

tnbLib::SectPx_CompOffset
<
	tnbLib::SectPx_FieldFun, 
	tnbLib::SectPx_FieldFun
>::SectPx_CompOffset
(
	const std::shared_ptr<SectPx_FieldFun>& x,
	const std::shared_ptr<SectPx_FieldFun>& y
)
	: theX_(x)
	, theY_(y)
{
	// empty body
}

Standard_Real 
tnbLib::SectPx_CompOffset<tnbLib::SectPx_FieldFun, tnbLib::SectPx_FieldFun>::xCoord() const
{
	auto x = theX_.lock();
	if (NOT x)
	{
		FatalErrorIn(FunctionSIG)
			<< "no field function is set for the x-coord" << endl
			<< abort(FatalError);
	}
	return x->Value();
}

Standard_Real
tnbLib::SectPx_CompOffset<tnbLib::SectPx_FieldFun, tnbLib::SectPx_FieldFun>::yCoord() const
{
	auto x = theY_.lock();
	if (NOT x)
	{
		FatalErrorIn(FunctionSIG)
			<< "no field function is set for the y-coord" << endl
			<< abort(FatalError);
	}
	return x->Value();
}