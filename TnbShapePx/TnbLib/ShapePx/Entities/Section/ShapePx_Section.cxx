#include <ShapePx_Section.hxx>

#include <SectPx_Pars.hxx>
#include <SectPx_Tools.hxx>
#include <SectPx_FrameRegistry.hxx>
#include <SectPx_ScatterRegistry.hxx>
#include <ShapePx_ParValue.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

tnbLib::ShapePx_Section::ShapePx_Section
(
	const Standard_Integer theIndex
)
	: ShapePx_Entity(theIndex)
{
	// empty body
}

tnbLib::ShapePx_Section::ShapePx_Section
(
	const Standard_Integer theIndex,
	const word& theName
)
	: ShapePx_Entity(theIndex, theName)
{
	// empty body
}

tnbLib::ShapePx_Section::ShapePx_Section
(
	const std::shared_ptr<SectPx_FrameRegistry>& theReg
)
	: theRegistry_(theReg)
{
	// empty body
}

tnbLib::ShapePx_Section::ShapePx_Section
(
	const Standard_Integer theIndex,
	const word& theName,
	const std::shared_ptr<SectPx_FrameRegistry>& theReg
)
	: ShapePx_Entity(theIndex, theName)
	, theRegistry_(theReg)
{
	// empty body
}

Standard_Integer 
tnbLib::ShapePx_Section::NbProfiles() const
{
	Debug_Null_Pointer(Registry());
	return Registry()->NbTopoSegments();
}

Standard_Integer 
tnbLib::ShapePx_Section::NbCurveQs() const
{
	Debug_Null_Pointer(Registry());
	return Registry()->NbCurveQs();
}

std::vector<std::shared_ptr<tnbLib::SectPx_Par>> 
tnbLib::ShapePx_Section::RetrieveParameters() const
{
	Debug_Null_Pointer(Registry());
	auto segments = Registry()->RetrieveTopoSegments();
	if (segments.empty())
	{
		return std::vector<std::shared_ptr<SectPx_Par>>();
	}

	std::map<Standard_Integer, std::shared_ptr<SectPx_Par>> merge;
	for (const auto& x : segments)
	{
		auto parList = SectPx_Tools::RetrieveChildren(x);
		for (const auto& p : parList)
		{
			Debug_Null_Pointer(p);
			auto par = std::dynamic_pointer_cast<SectPx_Par>(p);
			Debug_Null_Pointer(par);
			
			auto paired = std::make_pair(par->Index(), std::move(par));
			auto insert = merge.insert(std::move(paired));
			if (NOT insert.second)
			{
				//- the parameter already exist in the map!
			}
		}
	}

	std::vector<std::shared_ptr<SectPx_Par>> parameters;
	parameters.reserve(merge.size());
	for (const auto& x : merge)
	{
		const auto& p = x.second;
		parameters.push_back(std::move(p));
	}
	return std::move(parameters);
}

std::vector<std::shared_ptr<tnbLib::SectPx_TopoSegment>> 
tnbLib::ShapePx_Section::RetrieveProfiles() const
{
	Debug_Null_Pointer(Registry());
	auto segments = Registry()->RetrieveTopoSegments();
	return std::move(segments);
}

std::vector<std::shared_ptr<tnbLib::SectPx_CurveQ>> 
tnbLib::ShapePx_Section::RetrieveCurveQs() const
{
	Debug_Null_Pointer(Registry());
	auto segments = Registry()->RetrieveCurveQs();
	return std::move(segments);
}

void tnbLib::ShapePx_Section::SetValues
(
	const std::shared_ptr<ShapePx_ParValue>& theValues
)
{
	const auto& pars = Registry()->Scatter()->ScatterMap(SectPx_RegObjType::parameter);
	for (const auto& x : theValues->Values())
	{
		const auto id = x.first;
		const auto val = x.second;

		auto iter = pars.find(id);
		if (iter IS_EQUAL pars.end())
		{
			FatalErrorIn(FunctionSIG)
				<< "there is no parameter with this id: " << id << endl
				<< abort(FatalError);
		}
		auto par = std::dynamic_pointer_cast<SectPx_Par>(iter->second.lock());
		Debug_Null_Pointer(par);

		if (par->IsFixed())
		{
			auto fixed = std::dynamic_pointer_cast<SectPx_FixedPar>(par);
			Debug_Null_Pointer(fixed);

			fixed->SetValue(val);
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "the parameter is not fixed!" << endl
				<< abort(FatalError);
		}
	}
}