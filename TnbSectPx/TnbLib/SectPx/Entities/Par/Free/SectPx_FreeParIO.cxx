#include <SectPx_FreePar.hxx>

#include <SectPx_FieldFun.hxx>

void tnbLib::SectPx_FreePar::Print(Ostream & out) const
{
	if (HasFieldFun())
	{
		const auto& fieldFun = FieldFun();
		out <<
			(
				fieldFun->IsComplete() ?
				std::to_string(Value()) :
				"NULL Parameter"
				)
			<< endl;
	}
	else
	{
		out << "NULL" << endl;
	}
}