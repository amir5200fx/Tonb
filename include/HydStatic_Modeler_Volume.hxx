#pragma once
#ifndef _HydStatic_Modeler_Volume_Header
#define _HydStatic_Modeler_Volume_Header

#include <HydStatic_Modeler_Entity.hxx>

#include <TopoDS_Shape.hxx>

namespace tnbLib
{

	namespace hydStcLib
	{

		class Modeler_Volume
		{

			/*Private Data*/

			TopoDS_Shape theShape_;


			auto& ChangeShape()
			{
				return theShape_;
			}

		protected:

			Modeler_Volume();

			Modeler_Volume(const Standard_Integer theIndex);

			Modeler_Volume(const Standard_Integer theIndex, const word& theName);

		public:

			const auto& Shape() const
			{
				return theShape_;
			}


		};
	}
}

#endif // !_HydStatic_Modeler_Volume_Header
