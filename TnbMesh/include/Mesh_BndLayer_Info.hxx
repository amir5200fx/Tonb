#pragma once
#ifndef _Mesh_BndLayer_Info_Header
#define _Mesh_BndLayer_Info_Header

#include <Mesh_Module.hxx>
#include <Global_Serialization.hxx>
#include <Global_TypeDef.hxx>

namespace tnbLib
{

	class Mesh_BndLayer_Info
	{

		/*Private Data*/

		Standard_Integer theNbLayers_;

		Standard_Real theFirstLayerThick_;
		Standard_Real theOuterLayerThick_;
		Standard_Real theGrowthRate_;
		Standard_Real theChevAngle_;

		// Private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar& theNbLayers_;
			ar& theFirstLayerThick_;
			ar& theOuterLayerThick_;
			ar& theGrowthRate_;
			ar& theChevAngle_;
		}

	public:

		static TnbMesh_EXPORT Standard_Integer DEFAULT_NB_LAYERS;

		static TnbMesh_EXPORT Standard_Real DEFAULT_FIRST_LAYER_THICK;
		static TnbMesh_EXPORT Standard_Real DEFAULT_OUTER_LAYER_THICK;
		static TnbMesh_EXPORT Standard_Real DEFAULT_GROWTH_RATE;
		static TnbMesh_EXPORT Standard_Real DEFAULT_CHEV_ANGLE;

		// default constructor

		Mesh_BndLayer_Info()
			: theNbLayers_(DEFAULT_NB_LAYERS)

			, theFirstLayerThick_(DEFAULT_FIRST_LAYER_THICK)
			, theOuterLayerThick_(DEFAULT_OUTER_LAYER_THICK)
			, theGrowthRate_(DEFAULT_GROWTH_RATE)
			, theChevAngle_(DEFAULT_CHEV_ANGLE)
		{}

		// constructors

		// public functions and operators

		auto NbLayars() const { return theNbLayers_; }
		
		auto FirstLayerThick() const { return theFirstLayerThick_; }
		auto OuterLayerThick() const { return theOuterLayerThick_; }
		auto GrowthRate() const { return theGrowthRate_; }
		auto ChevAngle() const { return theChevAngle_; }

		void SetNbLayers(const Standard_Integer theSize) { theNbLayers_ = theSize; }

		void SetFirstLayerThick(const Standard_Real theThick) { theFirstLayerThick_ = theThick; }
		void SetOuterLayerThick(const Standard_Real theThick) { theOuterLayerThick_ = theThick; }
		void SetGrowthRate(const Standard_Real theRate) { theGrowthRate_ = theRate; }
		void SetChevAngle(const Standard_Real theAngle) { theChevAngle_ = theAngle; }

	};

}

#endif // !_Mesh_BndLayer_Info_Header
