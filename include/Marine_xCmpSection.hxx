#pragma once
#ifndef _Marine_xCmpSection_Header
#define _Marine_xCmpSection_Header

#include <Marine_CmpSection.hxx>

namespace tnbLib
{

	class Marine_xCmpSection
		: public Marine_CmpSection
	{

		/*Private Data*/


		/*private functions and operators*/

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive &ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<Marine_CmpSection>(*this);
		}

		TnbMarine_EXPORT void SetSystem();

	public:

		// - default constructor

		TnbMarine_EXPORT Marine_xCmpSection();


		//- constructors

		TnbMarine_EXPORT explicit Marine_xCmpSection
		(
			const Standard_Integer theIndex
		);

		TnbMarine_EXPORT Marine_xCmpSection
		(
			const Standard_Integer theIndex, 
			const word& theName
		);

		TnbMarine_EXPORT explicit Marine_xCmpSection
		(
			const std::shared_ptr<Marine_Section>& theSection
		);

		TnbMarine_EXPORT Marine_xCmpSection
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<Marine_Section>& theSection
		);

		TnbMarine_EXPORT Marine_xCmpSection
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<Marine_Section>& theSection
		);

		Standard_Boolean IsXsection() const override
		{
			return Standard_True;
		}

		TnbMarine_EXPORT Standard_Real X() const override;

		TnbMarine_EXPORT std::shared_ptr<Marine_CmpSection> Copy() const override;

		/*static std::shared_ptr<Marine_CmpSection>
			CreateCmpSection
			(
				const std::vector<std::shared_ptr<Pln_Curve>>& theCurves,
				const gp_Ax2& theSystem,
				const Standard_Real theMinTol,
				const Standard_Real theMaxTol
			);

		static std::shared_ptr<Marine_CmpSection>
			CreateCmpSection
			(
				const std::vector<Handle(Geom2d_Curve)>& theCurves,
				const gp_Ax2& theSystem,
				const Standard_Real theMinTol,
				const Standard_Real theMaxTol
			);

		static std::shared_ptr<Marine_CmpSection>
			CreateCmpSection
			(
				const TopoDS_Shape& theEdges,
				const gp_Ax2& theSystem,
				const Standard_Real theMinTol,
				const Standard_Real theMaxTol
			);*/

		
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Marine_xCmpSection);

#endif // !_Marine_xCmpSection_Header
