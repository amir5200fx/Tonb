#pragma once
#include <SectPx_Parent.hxx>
namespace tnbLib
{

	template<class Archive>
	void SectPx_ParentAdaptor::Pair::serialize(Archive & ar, const unsigned int version)
	{
		ar & Parent;
		ar & K;
	}
}