#pragma once
#ifndef _Mesh_VolumetricSizeMapControl_Header
#define _Mesh_VolumetricSizeMapControl_Header

#include <Mesh_SizeMapControl.hxx>

namespace tnbLib
{

	template<class GeomType>
	class Mesh_VolumetricSizeMapControl
		: public Mesh_SizeMapControl<GeomType>
	{

	public:

		typedef Mesh_SizeMapControl<GeomType> base;
		using base::sizeMapTool;
		using base::meshRefValuesType;
		using base::boxType;
		using base::cloudType;

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


		//- default constructor
		Mesh_VolumetricSizeMapControl()
		{}


		//- constructors

		Mesh_VolumetricSizeMapControl
		(
			const std::shared_ptr<meshRefValuesType>& theRef,
			const std::shared_ptr<boxType>& theDomain,
			const std::shared_ptr<cloudType>& theCloud
		)
			: base(theRef, theDomain, theCloud)
		{}

	public:

		


		//- public functions and operators


	};
}

#endif // !_Mesh_VolumetricSizeMapControl_Header

