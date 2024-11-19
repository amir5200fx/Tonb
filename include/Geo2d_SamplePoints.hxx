#pragma once
#ifndef _Geo2d_SamplePoints_Header
#define _Geo2d_SamplePoints_Header

#include <Geo_Module.hxx>
#include <Entity2d_BoxFwd.hxx>
#include <Pnt2d.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations [12/26/2021 Amir]

	class Geo2d_SamplePoints
	{

	public:

		enum class Type
		{
			four_points,
			five_points,
			eight_points,
			nine_points,
			eight_points_2layer,
			nine_points_2layer,
			thirteen_points_2layer
		};

	private:

		/*Private Data*/


	protected:

		// default constructor [12/26/2021 Amir]

		Geo2d_SamplePoints()
		{}


		// constructors [12/26/2021 Amir]


	public:

		// public functions and operators [12/26/2021 Amir]

		virtual Standard_Integer NbPoints() const = 0;
		virtual Pnt2d CalcPoint(const Standard_Integer theIndex, const Entity2d_Box&) const = 0;

		virtual std::vector<Pnt2d> RetrieveSamples() const = 0;

		std::vector<Pnt2d> CalcPoints(const Entity2d_Box&) const;
	};
}

#endif // !_Geo2d_SamplePoints_Header
