
#define HYDSTATIC_HYDGRAPHCURVE_IMPL(CLASS_NAME)																\
std::shared_ptr<tnbLib::hydStcGphLib::CLASS_NAME>																\
tnbLib::hydStcGphLib::CLASS_NAME::Curve(const std::vector<xDraft>& theQ)										\
{																												\
	if (theQ.size() < 2)																						\
	{																											\
		FatalErrorIn(FunctionSIG)																				\
			<< "Not enough points"																				\
			<< abort(FatalError);																				\
	}																											\
	Handle(TColgp_HArray1OfPnt2d) PtsPtr = new TColgp_HArray1OfPnt2d(1, (Standard_Integer)theQ.size());			\
																												\
	auto& Pts = *PtsPtr;																						\
	Standard_Integer K = 0;																						\
	for (const auto& x : theQ)																					\
	{																											\
		Pts.SetValue(++K, gp_Pnt2d(x.value, x.T));																\
	}																											\
	Geom2dAPI_Interpolate Interpolation(PtsPtr, Standard_False, 1.0e-6);										\
	Interpolation.Perform();																					\
																												\
	if (!Interpolation.IsDone())																				\
	{																											\
		FatalErrorIn(FunctionSIG)																				\
		<< "Failed to interpolation!"																			\
		<< abort(FatalError);																					\
	}																											\
																												\
	try																											\
	{																											\
		auto c = std::make_shared<CLASS_NAME>(Interpolation.Curve());											\
		return std::move(c);																					\
	}																											\
	catch (StdFail_NotDone&)																					\
	{																											\
		return nullptr;																							\
	}																											\
}