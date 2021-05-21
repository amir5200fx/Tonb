#pragma once
#ifndef _Mesh_SizeMapControl_Header
#define _Mesh_SizeMapControl_Header

#include <word.hxx>
#include <Global_Serialization.hxx>
#include <Mesh_SizeMapControl_Traits.hxx>
#include <Mesh_Module.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <memory>
#include <map>

namespace tnbLib
{

	// Forward Declarations
	class Mesh_ReferenceValues;

	template<class GeomType>
	class Mesh_SizeMapControl
	{

	public:

		typedef typename size_map_type<GeomType>::type sizeMapTool;

	private:

		/*Private Data*/

		std::shared_ptr<Mesh_SizeMapControl> theReference_;
		std::shared_ptr<GeomType> theGeometry_;

		std::map<word, std::shared_ptr<sizeMapTool>> theBoundaries_;


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			FatalErrorIn(FunctionSIG)
				<< "it's not supposed to be called!" << endl
				<< abort(FatalError);
		}

	protected:

		//- default constructor
		Mesh_SizeMapControl()
		{}

		//- constructors

		Mesh_SizeMapControl
		(
			const std::shared_ptr<GeomType>& theGeometry, 
			const std::shared_ptr<Mesh_SizeMapControl>& theRef
		)
			: theGeometry_(theGeometry)
			, theReference_(theRef)
		{}


		virtual ~Mesh_SizeMapControl()
		{}

		//- protected functions and operators

		void Import(const word& theName, const std::shared_ptr<sizeMapTool>& theSizeMap);

	public:

		//- public functions and operators

		const auto& References() const
		{
			return theReference_;
		}

		const auto& Geometry() const
		{
			return theGeometry_;
		}

		const auto& Maps() const
		{
			return theBoundaries_;
		}

		void LoadGeometry(const std::shared_ptr<GeomType>& theGeometry)
		{
			theGeometry_ = theGeometry;
		}

		void LoadReference(const std::shared_ptr<Mesh_SizeMapControl>& theRef)
		{
			theReference_ = theRef;
		}

	};
}

#include <Mesh_SizeMapControlI.hxx>

#endif // !_Mesh_SizeMapControl_Header
