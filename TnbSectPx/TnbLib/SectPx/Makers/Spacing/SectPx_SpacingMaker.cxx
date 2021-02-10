#include <SectPx_SpacingMaker.hxx>

#include <SectPx_FrameRegistry.hxx>
#include <SectPx_Limits.hxx>
#include <SectPx_UniformSpacing.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::shared_ptr<tnbLib::SectPx_Spacing> 
tnbLib::maker::Spacing::SelectSpacing
(
	const Standard_Integer theIndex
) const
{
	Debug_Null_Pointer(Registry());

	auto item = Registry()->SelectObj(theIndex);
	Debug_Null_Pointer(item);

	auto spacing = std::dynamic_pointer_cast<SectPx_Spacing>(item);
	if (NOT spacing)
	{
		FatalErrorIn(FunctionSIG)
			<< "the item is not a spacing!" << endl
			<< abort(FatalError) << endl;
	}
	return std::move(spacing);
}

Standard_Integer 
tnbLib::maker::Spacing::CreateUniform
(
	const std::shared_ptr<SectPx_Limits>& theLimits, 
	const Standard_Integer n
) const
{
	auto spacing = std::make_shared<SectPx_UniformSpacing>(theLimits, n);
	Debug_Null_Pointer(spacing);

	Debug_Null_Pointer(Registry());
	const auto id = Registry()->Import(spacing);

	return id;
}

std::shared_ptr<tnbLib::SectPx_Spacing> 
tnbLib::maker::Spacing::RemoveSpacing
(
	const Standard_Integer theIndex
) const
{
	auto item = SelectSpacing(theIndex);
	Debug_Null_Pointer(item);

	Debug_Null_Pointer(Registry());
	Registry()->Remove(item);
	return std::move(item);
}