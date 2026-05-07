#include <HydStatic_SolutionData_GzEff.hxx>

#include <StbGMaker_Model.hxx>
#include <Marine_Shapes.hxx>
#include <HydStatic_Shapes.hxx>
#include <HydStatic_FormCoeff.hxx>
#include <HydStatic_FormDims.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Boolean 
tnbLib::hydStcLib::SolutionData_GzEff::IsUpdated
(
	const analysisCode code
)
{
	return (int)theCode_ >= (int)code;
}

typename tnbLib::hydStcLib::SolutionData_GzEff::tankMap::const_iterator
tnbLib::hydStcLib::SolutionData_GzEff::SelectTank
(
	const Standard_Integer theIndex
) const
{
	auto iter = theTanks_.find(theIndex);
	if (iter IS_EQUAL theTanks_.end())
	{
		FatalErrorIn(FunctionSIG)
			<< " the tank is not inside the solution data!" << endl
			<< " - id: " << theIndex << endl
			<< abort(FatalError);
	}
	return std::move(iter);
}

typename tnbLib::hydStcLib::SolutionData_GzEff::tankMap::iterator 
tnbLib::hydStcLib::SolutionData_GzEff::ImportTank
(
	const std::shared_ptr<HydStatic_TankShape>& theTank
)
{
	auto paired = std::make_pair(theTank->Index(), theTank);
	auto insert = theTanks_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< "unable to insert the tank into the list: duplicate data has been detected!" << endl
			<< abort(FatalError);
	}
	return std::move(insert.first);
}

void tnbLib::hydStcLib::SolutionData_GzEff::RemoveTank
(
	const Standard_Integer theIndex
)
{
	auto tank = SelectTank(theIndex);
	RemoveTank(tank);
}

void tnbLib::hydStcLib::SolutionData_GzEff::RemoveTank
(
	const tankMap::const_iterator & iter
)
{
	theTanks_.erase(iter);
}

void tnbLib::hydStcLib::SolutionData_GzEff::SetGzEff
(
	const std::shared_ptr<hydStcLib::rArmCurve_Eff>& theGz
)
{
	theGzEff_ = theGz;
}

void tnbLib::hydStcLib::SolutionData_GzEff::SetGzEff
(
	std::shared_ptr<hydStcLib::rArmCurve_Eff>&& theGz
)
{
	theGzEff_ = std::move(theGz);
}

void tnbLib::hydStcLib::SolutionData_GzEff::Import
(
	const std::shared_ptr<StbGMaker_Model>& theModel
)
{
	if (NOT theModel)
	{
		FatalErrorIn(FunctionSIG)
			<< " the imported model is null" << endl
			<< abort(FatalError);
	}

	theModel_ = theModel;

	theHull_ = std::make_shared<HydStatic_HullShape>();
	theHull_->SetHull(theModel->Hull());
	
	for (const auto& x : theModel_->Tanks())
	{
		Debug_Null_Pointer(x);

		auto tank = std::make_shared<HydStatic_TankShape>();
		Debug_Null_Pointer(tank);

		tank->SetModel(x);
		ImportTank(tank);
	}
}