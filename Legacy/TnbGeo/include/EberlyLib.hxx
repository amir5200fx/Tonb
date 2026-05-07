#pragma once
#ifndef _EberlyLib_Header
#define _EberlyLib_Header

#include <Pnt3d.hxx>

namespace tnbLib
{

	namespace EberlyLib
	{

		// David Eberly, Geometric Tools, Redmond WA 98052
		// Copyright (c) 1998-2016
		// Distributed under the Boost Software License, Version 1.0.
		// http://www.boost.org/LICENSE_1_0.txt
		// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
		// File Version: 3.0.0 (2016/06/19)
		// 
		// Modified and convert to C++ by Amir Amir-solaymani (2016/11/26)

		struct Segment
		{
			Pnt3d end0, end1;
		};

		struct Result
		{
			double sqrDistance;
			double parameter[2];

#if GET_CLOSEST
			Pnt3d closest[2];
#endif
		};

		inline double GetClampedRoot(double slope, double h0, double h1);

		TnbGeo_EXPORT void ComputeIntersection
		(
			double b,
			double f00,
			double f10, 
			double sValue[2],
			int classify[2],
			int edge[2], 
			double end[2][2]
		);

		TnbGeo_EXPORT void ComputeMinimumParameters
		(
			double b, 
			double c, 
			double e, 
			double g00, 
			double g10, 
			double g01, 
			double g11, 
			int edge[2],
			double end[2][2],
			double parameter[2]
		);

		TnbGeo_EXPORT void CSMain
		(
			const Segment& segment0, 
			const Segment& segment1,
			Result& result
		);
	}
}

#include <EberlyLibI.hxx>

#endif // !_EberlyLib_Header
