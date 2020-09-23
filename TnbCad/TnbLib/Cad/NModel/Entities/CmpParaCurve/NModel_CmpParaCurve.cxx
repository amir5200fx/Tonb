#include <NModel_CmpParaCurve.hxx>

#include <Entity2d_Box.hxx>
#include <NModel_ParaCurve.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

tnbLib::Entity2d_Box
tnbLib::NModel_CmpParaCurve::CalcBoundingBox() const
{
	if (Curves().empty())
	{
		FatalErrorIn("Entity2d_Box CalcBoundingBox() const")
			<< "the curve list is empty" << endl
			<< abort(FatalError);
	}

	const auto& curves = Curves();
	auto iter = curves.begin();

	Debug_Null_Pointer((*iter));
	auto box = (*iter)->CalcBoundingBox();

	iter++;

	while (iter NOT_EQUAL curves.end())
	{
		Debug_Null_Pointer((*iter));
		box = Entity2d_Box::Union(box, (*iter)->CalcBoundingBox());

		iter++;
	}
	return std::move(box);
}