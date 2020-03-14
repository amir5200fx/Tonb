#pragma once
#ifndef _IOLongListInstances_Header
#define _IOLongListInstances_Header

#include <face.hxx>
#include <cell.hxx>
#include <point.hxx>
#include <IOLongList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	typedef IOLongList<point> pointIOFieldPMG;
	typedef IOLongList<face> faceIOListPMG;
	typedef IOLongList<cell> cellIOListPMG;
	typedef IOLongList<label> labelIOListPMG;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_IOLongListInstances_Header
