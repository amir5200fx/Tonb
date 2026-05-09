#include <SectPx_PairedInterface_Joint.hxx>

const char* tnbLib::sectPxLib::PairedInterface_Joint::typeName_("joint interface");

tnbLib::word
tnbLib::sectPxLib::PairedInterface_Joint::RegObjTypeName() const
{
	return typeName_;
}

tnbLib::sectPxLib::interfaceType 
tnbLib::sectPxLib::PairedInterface_Joint::InterfaceType() const
{
	return sectPxLib::interfaceType::joint;
}

//void tnbLib::sectPxLib::PairedInterface_Joint::disJoint()
//{
//
//}