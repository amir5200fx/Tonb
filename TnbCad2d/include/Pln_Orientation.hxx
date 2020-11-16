#pragma once
#ifndef _Pln_Orientation_Header
#define _Pln_Orientation_Header

#include <Global_Serialization.hxx>

namespace tnbLib
{

	enum class Pln_Orientation
	{
		Pln_Orientation_Unknown = 0,
		Pln_Orientation_CCW,
		Pln_Orientation_CW
	};

	Pln_Orientation Reverse(const Pln_Orientation theOrient);

	template<class Archive>
	void serialize(Archive& ar, Pln_Orientation& x, const unsigned int file_version)
	{
		ar & x;
	}
}

#endif // !_Pln_Orientation_Header
