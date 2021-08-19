#include "InitCamber.hxx"

void tnbLib::createCamberForm()
{
	auto form = std::make_shared<ptdModel::BladeFormNo1_Camber>();
	ImportToForm(form, myRootCamber);
	ImportToForm(form, myTipCamber);
	ImportToForm(form, myMaxCamber);
	ImportToForm(form, myMaxCamberLoc);
	ImportToForm(form, myRootCamberWeight);
	ImportToForm(form, myTipCamberWeight);
	myMakers->push_back(std::move(form));
}