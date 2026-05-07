#pragma once
#ifndef _Discret3d_Surface_Function_Header
#define _Discret3d_Surface_Function_Header

#include <Discret_Module.hxx>
#include <Global_Serialization.hxx>
#include <Global_TypeDef.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations [11/7/2022 Amir]

	class Cad_GeomSurface;

	class Discret3d_Surface_Function
	{

		/*Private Data*/


		// Private functions and operators [11/7/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			// empty body [11/7/2022 Amir]
		}

	protected:

		// default constructor [11/7/2022 Amir]

		Discret3d_Surface_Function()
		{}


		// constructors [11/7/2022 Amir]

	public:

		// public functions and operators [11/7/2022 Amir]

		virtual Standard_Boolean 
			Subdivide
			(
				const std::shared_ptr<Cad_GeomSurface>& theSurface, 
				const Standard_Real theU0, 
				const Standard_Real theU1,
				const Standard_Real theV0,
				const Standard_Real theV1
			) const = 0;
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Discret3d_Surface_Function);

#endif // !_Discret3d_Surface_Function_Header
