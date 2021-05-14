#pragma once
#ifndef _Cad3d_GModel_Header
#define _Cad3d_GModel_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>
#include <Global_Serialization.hxx>
#include <Cad_Module.hxx>

#include <TopoDS_Shape.hxx>

#include <memory>
#include <vector>

class TopoDS_Shape;

namespace tnbLib
{

	// Forward Declarations
	class GModel_Surface;

	class Cad3d_GModel
		: public Global_Indexed
		, public Global_Named
	{

		/*Private Data*/

		TopoDS_Shape theShape_;

		std::vector<std::shared_ptr<GModel_Surface>> theSurfaces_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbCad_EXPORT);


		//- default constructor

		Cad3d_GModel()
		{}

	public:


		//- constructors

		Cad3d_GModel(const std::vector<std::shared_ptr<GModel_Surface>>& theSurfaces);

		Cad3d_GModel(std::vector<std::shared_ptr<GModel_Surface>>&& theSurfaces);

		Cad3d_GModel(const Standard_Integer theIndex, const word& theName, const std::vector<std::shared_ptr<GModel_Surface>>& theSurfaces);

		Cad3d_GModel(const Standard_Integer theIndex, const word& theName, std::vector<std::shared_ptr<GModel_Surface>>&& theSurfaces);


		//- public functions and operators

		Standard_Integer NbSurfaces() const;


	};
}

#endif // !_Cad3d_GModel_Header
