#include <Geo_TableFunction.hxx>

#include <Geo_SamplingFunction.hxx>
#include <Global_Table.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Real 
tnbLib::Geo_TableFunction::Value
(
	const Standard_Real theRow, 
	const Standard_Real theCol, 
	const Global_Table & theTable
) const
{
	if (NOT RowFun())
	{
		FatalErrorIn(FunctionSIG)
			<< "no row function has been detected!" << endl
			<< abort(FatalError);
	}

	if (NOT ColFun())
	{
		FatalErrorIn(FunctionSIG)
			<< "no column function has been detected!" << endl
			<< abort(FatalError);
	}

	const auto& rows = theTable.Row();
	const auto& cols = theTable.Column();

	const auto rowIndices = RowFun()->Samples(theRow, rows.Values());
	const auto colIndices = ColFun()->Samples(theCol, cols.Values());

	std::vector<std::pair<Standard_Real, Standard_Real>> Qs;
	for (auto xRow : rows.Entities(rowIndices))
	{
		auto colQ = Global_Table::ColEntities(xRow, colIndices, theTable);
		auto v = ColFun()->Interpolate(xRow, colQ);

		auto paired = std::make_pair(xRow, v);
		Qs.push_back(std::move(paired));
	}

	return RowFun()->Interpolate(theRow, Qs);
}