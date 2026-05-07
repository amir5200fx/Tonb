#include "InitThick.hxx"

void tnbLib::createThickForm()
{
	auto form = std::make_shared<ptdModel::BladeFormNo1_Thickness>();
	ImportToForm(form, myRootThick);
	ImportToForm(form, myTipThick);
	ImportToForm(form, myRootSteepThick);
	ImportToForm(form, myTipSteepThick);
	myMakers->push_back(std::move(form));
}