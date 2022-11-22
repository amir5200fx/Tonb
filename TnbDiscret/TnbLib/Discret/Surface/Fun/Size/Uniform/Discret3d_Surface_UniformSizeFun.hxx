#pragma once
#ifndef _Discret3d_Surface_UniformSizeFun_Header
#define _Discret3d_Surface_UniformSizeFun_Header

#include <Discret3d_Surface_SizeFunction.hxx>

namespace tnbLib
{

	class Discret3d_Surface_UniformSizeFun
		: public Discret3d_Surface_SizeFunction
	{

		/*Private Data*/

		Standard_Real theSize_;


		// Private functions and operators [11/16/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<Discret3d_Surface_SizeFunction>(*this);
			ar & theSize_;
		}

	public:

		// default constructor [11/7/2022 Amir]

		Discret3d_Surface_UniformSizeFun()
			: theSize_(0)
		{}


		// constructors [11/7/2022 Amir]


		// Public functions and operators [11/7/2022 Amir]

		auto Size() const
		{
			return theSize_;
		}

		TnbDiscret_EXPORT Standard_Boolean 
			Subdivide
			(
				const std::shared_ptr<Cad_GeomSurface>& theSurface, 
				const Standard_Real theU0, 
				const Standard_Real theU1, 
				const Standard_Real theV0,
				const Standard_Real theV1
			) const override;

		void SetSize(const Standard_Real theSize)
		{
			theSize_ = theSize;
		}
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Discret3d_Surface_UniformSizeFun);

#endif // !_Discret3d_Surface_UniformSizeFun_Header
