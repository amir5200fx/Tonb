#pragma once
#ifndef _VoyageSim_Variables_Header
#define _VoyageSim_Variables_Header

#include <Standard_TypeDef.hxx>
#include <Pnt2d.hxx>

namespace tnbLib
{
	namespace voyageLib
	{
		namespace variable
		{

			struct Cost
			{
				Standard_Real value;
			};

			struct Time
			{
				Standard_Real value;
			};

			struct Velocity
			{
				Standard_Real value;
			};

			struct Distance
			{
				Standard_Real value;
			};

			struct RPM
			{
				Standard_Real value;
			};

			struct Power
			{
				Standard_Real value;
			};

			struct NbSamples
			{
				Standard_Integer value;
			};

			struct Resistance
			{
				Standard_Real value;
			};

			struct SOG
			{
				Standard_Real value;
			};

			struct State
			{
				Pnt2d coord;
				Time time;
			};

			struct Path
			{
				State start;
				State end;
			};

			struct Location
			{
				Pnt2d value;
			};
		}
	}
}

#endif
