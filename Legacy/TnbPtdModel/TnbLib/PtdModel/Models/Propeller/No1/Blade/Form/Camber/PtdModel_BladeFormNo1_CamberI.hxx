#pragma once
inline tnbLib::word 
tnbLib::ptdModel::BladeFormNo1_Camber::Parameter(const Parameters p) const
{
	return theParameters_[(size_t)p];
}