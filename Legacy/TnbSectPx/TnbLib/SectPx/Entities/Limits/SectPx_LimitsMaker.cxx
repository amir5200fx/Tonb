#include <SectPx_LimitsMaker.hxx>

#include <SectPx_FrameRegistry.hxx>
#include <SectPx_Limits.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::shared_ptr<tnbLib::SectPx_Limits> 
tnbLib::maker::Limits::SelectLimits
(
	const Standard_Integer theIndex
) const
{
	Debug_Null_Pointer(Registry());

	auto item = Registry()->SelectObj(theIndex);
	Debug_Null_Pointer(item);

	auto limits = std::dynamic_pointer_cast<SectPx_Limits>(item);
	if (NOT limits)
	{
		FatalErrorIn(FunctionSIG)
			<< "the item is not a limits!" << endl
			<< abort(FatalError) << endl;
	}
	return std::move(limits);
}

Standard_Integer 
tnbLib::maker::Limits::CreateLimits
(
	const std::shared_ptr<SectPx_Par>& theP0,
	const std::shared_ptr<SectPx_Par>& theP1
) const
{
	auto limits = std::make_shared<SectPx_Limits>();
	Debug_Null_Pointer(limits);

	Debug_Null_Pointer(Registry());
	const auto id = Registry()->Import(limits);

	limits->SetStart(theP0);
	limits->SetEnd(theP1);

	return id;
}

std::shared_ptr<tnbLib::SectPx_Limits> 
tnbLib::maker::Limits::RemoveLimits
(
	const Standard_Integer theIndex
) const
{
	auto item = SelectLimits(theIndex);
	Debug_Null_Pointer(item);

	Debug_Null_Pointer(Registry());
	Registry()->Remove(item);
	return std::move(item);
}