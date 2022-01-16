#include <Global_Tools.hxx>

#include <Global_Table.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

size_t 
tnbLib::Global_Tools::FindSpan
(
	const Standard_Real x,
	const std::vector<Standard_Real>& theSorted
)
{
#ifdef _DEBUG
	CheckSorted(theSorted, "size_t Global_Tools::FindSpan(Args...)");
#endif // _DEBUG

	auto high = theSorted.size() - 1;
	if (x IS_EQUAL theSorted[high])
	{
		return high;
	}

	size_t low = 0;
	auto mid = (low + high) / 2;
	while (x < theSorted[mid] OR x >= theSorted[mid + 1])
	{
		if (x < theSorted[mid]) high = mid;
		else low = mid;
		mid = (low + high) / 2;
	}
	return mid;
}

Standard_Real 
tnbLib::Global_Tools::Interpolate
(
	const Standard_Real theRow, 
	const Standard_Real theCol,
	const Global_Table & theTable
)
{
	Check(theRow, theCol, theTable);

	const auto& rows = theTable.Row();
	const auto& cols = theTable.Column();

	const auto rowSpan = FindSpan(theRow, rows.Values());
	const auto colSpan = FindSpan(theCol, cols.Values());

	const auto p0 = rows.SpanValues((Standard_Integer)rowSpan);
	const auto p1 = cols.SpanValues((Standard_Integer)colSpan);

	return LinearInterpolate(p0, p1, theRow);
}

void tnbLib::Global_Tools::Check
(
	const Standard_Real theRow,
	const Standard_Real theCol,
	const Global_Table & theTable
)
{
	const auto[x0, x1] = theTable.RowSpan();
	if (NOT INSIDE(theRow, x0, x1))
	{
		FatalErrorIn(FunctionSIG)
			<< "the value of the row exceeds the boundaries!" << endl
			<< " - rows: " << theRow << endl
			<< " - min: " << x0 << endl
			<< " - max: " << x1 << endl
			<< abort(FatalError);
	}
	const auto[y0, y1] = theTable.ColumnSpan();
	if (NOT INSIDE(theRow, y0, y1))
	{
		FatalErrorIn(FunctionSIG)
			<< "the value of the column exceeds the boundaries!" << endl
			<< " - rows: " << theCol << endl
			<< " - min: " << y0 << endl
			<< " - max: " << y1 << endl
			<< abort(FatalError);
	}
}

void tnbLib::Global_Tools::CheckSorted
(
	const std::vector<Standard_Real>& theSorted,
	const char* theName
)
{
	auto iter = theSorted.begin();
	auto x0 = *iter;

	iter++;
	while (iter NOT_EQUAL theSorted.end())
	{
		if (*iter < x0)
		{
			FatalErrorIn(theName)
				<< "the vector is not sorted!" << endl
				<< abort(FatalError);
		}
		x0 = *iter;
		iter++;
	}
}