#include "InitChord.hxx"

void tnbLib::createChordForm()
{
	auto form = std::make_shared<ptdModel::BladeFormNo1_Chord>();
	ImportToForm(form, myRootChord);
	ImportToForm(form, myTipChord);
	ImportToForm(form, myMaxChord);
	ImportToForm(form, myMaxChordLoc);
	ImportToForm(form, myRootChordWeight);
	ImportToForm(form, myTipChordWeight);
	myMakers->push_back(std::move(form));
}