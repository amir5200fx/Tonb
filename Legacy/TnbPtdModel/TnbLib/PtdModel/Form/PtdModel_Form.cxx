#include <PtdModel_Form.hxx>

#include <PtdModel_Par.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::map<tnbLib::word, std::shared_ptr<tnbLib::PtdModel_Par>> 
tnbLib::PtdModel_Form::RetrieveMap(std::shared_ptr<PtdModel_Par>* par, const Standard_Integer nbPars)
{
	std::map<word, std::shared_ptr<PtdModel_Par>> reg;
	for (size_t i = 0; i < nbPars; i++)
	{
		const auto& p = *par;
		auto paired = std::make_pair(p->Name(), p);
		auto insert = reg.insert(std::move(paired));
		if (NOT insert.second)
		{
			FatalErrorIn(FunctionSIG)
				<< "duplicate data!" << endl
				<< " - name: " << p->Name() << endl
				<< abort(FatalError);
		}
		par++;
	}
	return std::move(reg);
}

std::shared_ptr<tnbLib::PtdModel_Par>
tnbLib::PtdModel_Form::Parameter
(
	const word & name, 
	const std::map<word, std::shared_ptr<PtdModel_Par>>& parMap
)
{
	auto iter = parMap.find(name);
	if (iter IS_EQUAL parMap.end())
	{
		FatalErrorIn(FunctionSIG)
			<< "the parameter is not in the map!" << endl
			<< " - name: " << name << endl
			<< abort(FatalError);
	}
	return iter->second;
}