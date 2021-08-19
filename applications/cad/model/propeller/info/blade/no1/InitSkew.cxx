#include "InitSkew.hxx"

void tnbLib::createSkewForm()
{
	auto form = std::make_shared<ptdModel::BladeFormNo1_Skew>();
	ImportToForm(form, myTipSkew);
	ImportToForm(form, myRootSteepSkew);
	ImportToForm(form, myTipSteepSkew);
	myMakers->push_back(std::move(form));
}