#pragma once
#ifndef _Cad3d_NModel_Header
#define _Cad3d_NModel_Header

#include <NModel_Entity.hxx>
#include <Cad3d_NModelManager.hxx>
#include <Entity3d_Box.hxx>
#include <OFstream.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class NModel_Shell;
	class Cad_Tools;

	class Cad3d_NModel
		: public NModel_Entity
		, public Cad3d_NModelManager
	{

		typedef std::vector<std::shared_ptr<NModel_Shell>> shellList;

		typedef std::shared_ptr<NModel_Shell> outer;
		typedef std::shared_ptr<shellList> inner;

		/*Private Data*/

		outer theOuter_;
		inner theInner_;

	public:

		Cad3d_NModel();

		Cad3d_NModel(const Standard_Integer theIndex);

		Cad3d_NModel(const Standard_Integer theIndex, const word& theName);


		const auto& Outer() const
		{
			return theOuter_;
		}

		const auto& Holes() const
		{
			return theInner_;
		}

		Standard_Integer NbHoles() const;

		auto HasHole() const
		{
			return (Standard_Boolean)NbHoles();
		}

		//- IO functions and operators

		void ExportCornersToPlt(OFstream& File) const;

		void ExportSegmentsToPlt(OFstream& File) const;

		void ExportFacesToPlt(OFstream& File) const;

		void ExportFreeSegmentsToPlt(OFstream& File) const;
	};
}

#endif // !_Cad3d_NModel_Header
