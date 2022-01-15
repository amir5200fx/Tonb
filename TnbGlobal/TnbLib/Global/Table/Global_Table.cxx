#include <Global_Table.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

tnbLib::Global_Table::EntitiesTable::EntitiesTable
(
	const Standard_Integer nbRows, 
	const Standard_Integer nbColumns
)
{
	theValues_.resize(nbRows);
	for (auto& x : theValues_)
	{
		x.resize(nbColumns, 0.0);
	}
}

Standard_Integer 
tnbLib::Global_Table::EntitiesTable::NbRows() const
{
	return (Standard_Integer)theValues_.size();
}

Standard_Integer 
tnbLib::Global_Table::EntitiesTable::NbColumns() const
{
	if (NOT NbRows()) return 0;
	return (Standard_Integer)theValues_[0].size();
}

Standard_Real 
tnbLib::Global_Table::EntitiesTable::Value
(
	const Standard_Integer theRow, 
	const Standard_Integer theCol
) const
{
	Debug_Bad_Index(theRow, 0, NbRows() - 1);
	try
	{
		const auto& row = theValues_.at(theRow);

		Debug_Bad_Index(theCol, 0, NbColumns() - 1);
		return row.at(theCol);
	}
	catch (const std::exception& x)
	{
		FatalErrorIn(FunctionSIG)
			<< x.what() << endl
			<< abort(FatalError);
		return 0;
	}
}

void tnbLib::Global_Table::EntitiesTable::Set
(
	const Standard_Integer theRow, 
	const Standard_Integer theCol, 
	const Standard_Real theValue
)
{
	Debug_Bad_Index(theRow, 0, NbRows() - 1);
	try
	{
		auto& row = theValues_.at(theRow);

		Debug_Bad_Index(theCol, 0, NbColumns() - 1);
		row.at(theCol) = theValue;
	}
	catch (const std::exception& x)
	{
		FatalErrorIn(FunctionSIG)
			<< x.what() << endl
			<< abort(FatalError);
	}
}

tnbLib::Global_Table::Global_Table
(
	const Global_RowTable & theRow,
	const Global_ColumnTable & theCol
)
	: theRow_(theRow)
	, theColumn_(theCol)
	, theEntities_(theRow.Size(), theCol.Size())
{
	// empty body [1/11/2022 Amir]
}

tnbLib::Global_Table::Global_Table
(
	Global_RowTable && theRow,
	Global_ColumnTable && theCol
)
	: theEntities_(theRow.Size(), theCol.Size())
	, theRow_(std::move(theRow))
	, theColumn_(std::move(theCol))
{
	// empty body [1/11/2022 Amir]
}

std::pair<Standard_Real, Standard_Real> 
tnbLib::Global_Table::RowSpan() const
{
	const auto& rows = theRow_.Values();
	auto t = std::make_pair(rows[0], rows[rows.size() - 1]);
	return std::move(t);
}

std::pair<Standard_Real, Standard_Real>
tnbLib::Global_Table::ColumnSpan() const
{
	const auto& cols = theColumn_.Values();
	auto t = std::make_pair(cols[0], cols[cols.size() - 1]);
	return std::move(t);
}

std::vector<Standard_Real> 
tnbLib::Global_Table::RowEntities
(
	const Standard_Real xCol,
	const std::vector<Standard_Integer>& theIndices
) const
{
	std::vector<Standard_Real> values;
	values.reserve(theIndices.size());

	const auto& rows = Row();
	const auto rowX = rows.Entities(theIndices);

	const auto& ets = Entities();
	for (auto x : rowX)
	{
		auto v = ets.Value(x, xCol);
		values.push_back(std::move(v));
	}
	return std::move(values);
}

std::vector<Standard_Real> 
tnbLib::Global_Table::ColEntities
(
	const Standard_Real xRow, 
	const std::vector<Standard_Integer>& theIndices
) const
{
	std::vector<Standard_Real> values;
	values.reserve(theIndices.size());

	const auto& cols = Column();
	const auto colX = cols.Entities(theIndices);

	const auto& ets = Entities();
	for (auto x : colX)
	{
		auto v = ets.Value(xRow, x);
		values.push_back(std::move(v));
	}
	return std::move(values);
}

std::vector<std::pair<Standard_Real, Standard_Real>> 
tnbLib::Global_Table::RowEntities
(
	const Standard_Real xCol,
	const std::vector<Standard_Integer>& theIndices,
	const Global_Table & theTable
)
{
	std::vector<std::pair<Standard_Real, Standard_Real>> values;
	values.reserve(theIndices.size());
	const auto& rows = theTable.Row();
	const auto rowX = rows.Entities(theIndices);
	const auto rowValues = theTable.RowEntities(xCol, theIndices);

	for (size_t i = 0; i < theIndices.size(); i++)
	{
		auto paired = std::make_pair(rowX[i], rowValues[i]);
		values.push_back(std::move(paired));
	}
	return std::move(values);
}

std::vector<std::pair<Standard_Real, Standard_Real>> 
tnbLib::Global_Table::ColEntities
(
	const Standard_Real xRow,
	const std::vector<Standard_Integer>& theIndices,
	const Global_Table & theTable
)
{
	std::vector<std::pair<Standard_Real, Standard_Real>> values;
	values.reserve(theIndices.size());
	const auto& cols = theTable.Column();
	const auto colX = cols.Entities(theIndices);
	const auto colValues = theTable.ColEntities(xRow, theIndices);

	for (size_t i = 0; i < theIndices.size(); i++)
	{
		auto paired = std::make_pair(colX[i], colValues[i]);
		values.push_back(std::move(paired));
	}
	return std::move(values);
}