#pragma once
#ifndef _Cad2d_Modeler_Entity_Header
#define _Cad2d_Modeler_Entity_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>
#include <Geo_Serialization.hxx>

namespace tnbLib
{

	namespace cad2dLib
	{

		class Modeler_Entity
			: public Global_Indexed
			, public Global_Named
		{

			/*Private Data*/


			/*private functions and operators*/

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int version)
			{
				ar & Index();
				ar & Name();
			}

		protected:

			Modeler_Entity()
			{}

			Modeler_Entity
			(
				const Standard_Integer theIndex
			)
				: Global_Indexed(theIndex)
			{}

			Modeler_Entity
			(
				const Standard_Integer theIndex, 
				const word& theName
			)
				: Global_Indexed(theIndex)
				, Global_Named(theName)
			{}

		public:


		};
	}
}

#endif // !_Cad2d_Modeler_Entity_Header
