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

DECLARE_SAVE_IMP(tnbLib::SectPx_FreePar)
{
	ar & boost::serialization::base_object<SectPx_Par>(*this);
	ar & theFun_;
}

DECLARE_LOAD_IMP(tnbLib::SectPx_FreePar)
{
	ar & boost::serialization::base_object<SectPx_Par>(*this);
	ar & theFun_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::SectPx_FreePar);