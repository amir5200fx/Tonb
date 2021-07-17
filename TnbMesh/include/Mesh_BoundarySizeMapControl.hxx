#pragma once
#ifndef _Mesh_BoundarySizeMapControl_Header
#define _Mesh_BoundarySizeMapControl_Header

#include <Mesh_SizeMapControl.hxx>

namespace tnbLib
{

	template<class GeomType>
	class Mesh_BoundarySizeMapControl
		: public Mesh_SizeMapControl<GeomType>
	{

	public:

		typedef Mesh_SizeMapControl<GeomType> base;
		using base::sizeMapTool;

	private:

		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<Mesh_SizeMapControl<GeomType>>(*this);
		}

	protected:


	public:


		//- default constructor
		Mesh_BoundarySizeMapControl()
		{}


		//- constructors

		Mesh_BoundarySizeMapControl
		(
			const std::shared_ptr<GeomType>& theGeometry,
			const std::shared_ptr<Mesh_ReferenceValues>& theRef
		)
			: base(theGeometry, theRef)
		{}


		//- public functions and operators


	};
}

#endif // !_Mesh_BoundarySizeMapControl_Header
